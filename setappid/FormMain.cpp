#include "stdafx.h"

#include "FormMain.h"
#include "FormProcess.h"

#pragma comment(lib, "shlwapi.lib")

_COM_SMARTPTR_TYPEDEF(IPropertyStore, __uuidof(IPropertyStore));

EXTERN_C const PROPERTYKEY DECLSPEC_SELECTANY PKEY_AppUserModel_ID =
{ { 0x9F4C2855, 0x9F79, 0x4B39,
{ 0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3, } }, 5 };

using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;

namespace setappid
{
	String^ FormMain::getI18NString(String^ sIn)
	{
		String^ ret = theResource_->GetString(sIn);
		return String::IsNullOrEmpty(ret) ? sIn : ret;
	}
	String^ AppIDCommon(String^ shortcutfile, bool bSet, String^ appID)
	{
		HRESULT hr;
		IShellLinkWPtr link;
		CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&link));
		if(!link)
			throw gcnew Exception(I18N(L"No IShellLinkWPtr"));

		IPersistFilePtr persitFile(link);
		if(!persitFile)
			throw gcnew Exception(I18N(L"No IPersistFile"));

		pin_ptr<const wchar_t> pIn = PtrToStringChars(shortcutfile);
		hr = persitFile->Load(pIn, bSet ? STGM_READWRITE:(STGM_READ | STGM_SHARE_DENY_NONE));
		if(FAILED(hr))
		{
			throw gcnew Win32Exception(hr);
		}

		IPropertyStorePtr propStore(link);
		if(!propStore)
			throw gcnew Exception(I18N(L"No IPropertyStore"));

		if(!bSet)
		{
			PROPVARIANT pv;
			hr = propStore->GetValue(PKEY_AppUserModel_ID, &pv);
			if(FAILED(hr))
				throw gcnew Win32Exception(hr);

			if(pv.vt != VT_LPWSTR)
				return String::Empty;

			String^ ret = gcnew String(pv.pwszVal);
			PropVariantClear(&pv);
			return ret;
		}

		PROPVARIANT pvSet;
		pIn = PtrToStringChars(appID);
		InitPropVariantFromString(pIn, &pvSet);
		hr = propStore->SetValue(PKEY_AppUserModel_ID, pvSet);
		PropVariantClear(&pvSet);
		if(FAILED(hr))
		{
			throw gcnew Win32Exception(hr);
		}
		hr=propStore->Commit();
		if(FAILED(hr))
			throw gcnew Win32Exception(hr);

		hr=persitFile->Save(NULL, TRUE);
		if(FAILED(hr))
			throw gcnew Win32Exception(hr);

		return appID;
	}
	String^ GetAppID(String^ shortcutfile)
	{
		return AppIDCommon(shortcutfile, false, nullptr);
	}
	String^ SetAppID(String^ shortcutfile, String^ appID)
	{
		return AppIDCommon(shortcutfile, true, appID);
	}

	System::Void FormMain::listMain_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) 
	{
		if(e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;

		return;
	}

	System::Void FormMain::listMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if(e->Data->GetDataPresent(DataFormats::FileDrop))
		{
			array<Object^>^ obs = (array<Object^>^)e->Data->GetData(DataFormats::FileDrop, true);
			for each(Object^ o in obs)
			{
				try
				{
					String^ file = o->ToString();
					System::IO::FileInfo fi(file);
					if(0 != String::Compare(fi.Extension, L".lnk", true))
						continue;

					ListViewItem lvi;
					lvi.Text = o->ToString();

					ListViewItem::ListViewSubItem sub;
					sub.Text = GetAppID(file);

					lvi.SubItems->Add(%sub);
					listMain->Items->Add(%lvi);
				}
				catch(Exception^ ex)
				{
					MessageBox::Show(o->ToString() + L"\r\n\r\n" + ex->Message,
						Application::ProductName,
						MessageBoxButtons::OK,
						MessageBoxIcon::Warning);
					continue;
				}
			}
		}
	}

	System::Void FormMain::copyCuurentAppIDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(listMain->SelectedItems->Count==0)
		{
			MessageBox::Show(I18N(L"No Selection Item"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}

		try
		{
			System::Windows::Forms::Clipboard::SetText(listMain->SelectedItems[0]->SubItems[1]->Text);
		}
		catch(Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}
	}
	System::Void FormMain::setNewAppIDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(listMain->SelectedItems->Count==0)
		{
			MessageBox::Show(I18N(L"No Selection Item"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}

		String^ ret = listMain->SelectedItems[0]->SubItems[1]->Text;
		if(!Ambiesoft::GetTextDialog::DoModalDialog(this,
			I18N(L"Enter New AppID"),
			I18N(L"AppID:"),
			ret) || String::IsNullOrEmpty(ret))
		{
			return;
		}


		try
		{
			SetAppID(listMain->SelectedItems[0]->Text, ret);
			listMain->SelectedItems[0]->SubItems[1]->Text = GetAppID(listMain->SelectedItems[0]->Text);
		}
		catch(Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}
	}


	System::Void FormMain::btnProcess_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (formProcess_ == nullptr || formProcess_->IsDisposed)
			formProcess_ = gcnew FormProcess();
		
		formProcess_->Show();
	}
}


#if 0
//
// Win7AppId
// Author: David Roe (didroe)
// The code's a bit rough and ready but it does the job
//
// Compile with VS 2010 express using command:
//     cl /EHsc /D _UNICODE Win7AppId.cpp /link ole32.lib

#include <windows.h>
#include <shobjidl.h>
#include <propkey.h>
#include <tchar.h>

#include <iostream>

using namespace std;

EXTERN_C const PROPERTYKEY DECLSPEC_SELECTANY PKEY_AppUserModel_ID =
{ { 0x9F4C2855, 0x9F79, 0x4B39,
{ 0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3, } }, 5 };

void die(string message) {
	cout << "Error: " << message.c_str() << endl;
	exit(1);
}

void doOrDie(HRESULT hr, string message) {
	if (!SUCCEEDED(hr)) {
		die(message);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	doOrDie(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED),
		"Failed to initialise COM");

	IShellLink *link;
	doOrDie(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&link)),
		"Failed to create ShellLink object");

	IPersistFile* file; 
	doOrDie(link->QueryInterface(IID_PPV_ARGS(&file)),
		"Failed to obtain PersistFile interface"); 

	if (argc > 2) {
		doOrDie(file->Load(argv[1], STGM_READWRITE),
			"Failed to load shortcut file");
	} else {
		doOrDie(file->Load(argv[1], STGM_READ | STGM_SHARE_DENY_NONE),
			"Failed to load shortcut file");
	}

	IPropertyStore* store; 
	doOrDie(link->QueryInterface(IID_PPV_ARGS(&store)),
		"Failed to obtain PropertyStore interface"); 

	PROPVARIANT pv;
	doOrDie(store->GetValue(PKEY_AppUserModel_ID, &pv),
		"Failed to retrieve AppId");

	if (pv.vt != VT_EMPTY) {
		if (pv.vt != VT_LPWSTR) {
			cout << "Type: " << pv.vt << endl;
			die("Unexpected property value type");
		}

		wcout << "Current AppId: " << pv.pwszVal << endl;
	} else {
		cout << "No current AppId" << endl;
	}
	PropVariantClear(&pv);

	if (argc > 2) {
		wcout << "New AppId: " << argv[2] << endl;

		pv.vt = VT_LPWSTR;
		pv.pwszVal = argv[2];

		doOrDie(store->SetValue(PKEY_AppUserModel_ID, pv),
			"Failed to set AppId");

		// Not sure if we need to do this
		pv.pwszVal = NULL;
		PropVariantClear(&pv);

		doOrDie(store->Commit(),
			"Failed to commit AppId property");

		doOrDie(file->Save(NULL, TRUE),
			"Failed to save shortcut");
	}

	store->Release();
	file->Release();
	link->Release();	

	return 0;
}
#endif