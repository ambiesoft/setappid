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
using namespace System::IO;

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
		if (!link)
			throw gcnew Exception(I18N(L"No IShellLinkWPtr"));

		IPersistFilePtr persitFile(link);
		if (!persitFile)
			throw gcnew Exception(I18N(L"No IPersistFile"));

		pin_ptr<const wchar_t> pIn = PtrToStringChars(shortcutfile);
		hr = persitFile->Load(pIn, bSet ? STGM_READWRITE : (STGM_READ | STGM_SHARE_DENY_NONE));
		if (FAILED(hr))
		{
			throw gcnew Win32Exception(hr);
		}

		IPropertyStorePtr propStore(link);
		if (!propStore)
			throw gcnew Exception(I18N(L"No IPropertyStore"));

		if (!bSet)
		{
			PROPVARIANT pv;
			hr = propStore->GetValue(PKEY_AppUserModel_ID, &pv);
			if (FAILED(hr))
				throw gcnew Win32Exception(hr);

			if (pv.vt != VT_LPWSTR)
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
		if (FAILED(hr))
		{
			throw gcnew Win32Exception(hr);
		}
		hr = propStore->Commit();
		if (FAILED(hr))
			throw gcnew Win32Exception(hr);

		hr = persitFile->Save(NULL, TRUE);
		if (FAILED(hr))
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
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;

		return;
	}

	void FormMain::AddToList(String^ fullpath)
	{
		ListViewItem lvi;
		lvi.Text = fullpath;

		ListViewItem::ListViewSubItem sub;
		sub.Text = GetAppID(fullpath);

		lvi.SubItems->Add(%sub);
		listMain->Items->Add(%lvi);
	}

	System::Void FormMain::listMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
		{
			array<Object^>^ obs = (array<Object^>^)e->Data->GetData(DataFormats::FileDrop, true);
			for each(Object^ o in obs)
			{
				try
				{
					String^ file = o->ToString();
					System::IO::FileInfo fi(file);
					if (0 != String::Compare(fi.Extension, L".lnk", true))
						continue;

					AddToList(file);
				}
				catch (Exception^ ex)
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
	String^ FormMain::GetAppIDFromList(int index)
	{
		return listMain->Items[index]->SubItems[1]->Text;
	}
	System::Void FormMain::copyCuurentAppIDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (listMain->SelectedItems->Count == 0)
		{
			MessageBox::Show(I18N(L"No Selection Item"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}

		try
		{
			System::Windows::Forms::Clipboard::SetText(GetAppIDFromList(0));
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}
	}
	System::Void FormMain::ctxList_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		if (listMain->SelectedIndices->Count == 0)
		{
			ctxList->Enabled = false;
		}
		else
		{
			ctxList->Enabled = true;

			int currentIndex = listMain->SelectedIndices[0];
			copyAppIDToolStripMenuItem->Enabled = !String::IsNullOrEmpty(GetAppIDFromList(currentIndex));
		}
	}
	System::Void FormMain::setNewAppIDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^)
	{
		if (listMain->SelectedItems->Count == 0)
		{
			MessageBox::Show(I18N(L"No Selection Item"),
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return;
		}

		String^ ret = listMain->SelectedItems[0]->SubItems[1]->Text;
		if (!Ambiesoft::GetTextDialog::DoModalDialog(this,
			I18N(L"Enter New AppID"),
			I18N(L"AppID:"),
			ret))
		{
			return;
		}


		try
		{
			SetAppID(listMain->SelectedItems[0]->Text, ret);
			listMain->SelectedItems[0]->SubItems[1]->Text = GetAppID(listMain->SelectedItems[0]->Text);
		}
		catch (Exception^ ex)
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

	int mycomp(FileInfo^ f1, FileInfo^ f2)
	{
		return f1->Name->CompareTo(f2->Name);
	}
	System::Void FormMain::OnUPItemClick(System::Object^  sender, System::EventArgs^  e)
	{
		ToolStripMenuItem^ tsm = (ToolStripMenuItem^)sender;
		FileInfo^ fi = (FileInfo^)tsm->Tag;
		AddToList(fi->FullName);
	}
	System::Void FormMain::loadUserPinnedItemToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e)
	{
		try
		{
			String^ dir = Environment::GetFolderPath(Environment::SpecialFolder::ApplicationData)
				+ "\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar";

			DirectoryInfo^ di = gcnew DirectoryInfo(dir);
			array<FileInfo^>^ fis = di->GetFiles("*.lnk");

			Comparison<FileInfo^>^ c = gcnew Comparison<FileInfo^>(mycomp);
			Array::Sort(fis, c);

			loadUserPinnedItemToolStripMenuItem->DropDownItems->Clear();
			for each(FileInfo^ fi in fis)
			{
				ToolStripMenuItem^ tsm = gcnew ToolStripMenuItem();
				tsm->Text = fi->Name;
				tsm->Tag = fi;
				tsm->Click += gcnew System::EventHandler(this, &FormMain::OnUPItemClick);
				loadUserPinnedItemToolStripMenuItem->DropDownItems->Add(tsm);
			}
		}
		catch (System::Exception^ ex)
		{
			MessageBox::Show(ex->Message,
				Application::ProductName,
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
	System::Void FormMain::aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		System::Text::StringBuilder message;
		message.Append(Application::ProductName);
		message.Append(" ver");
		message.Append(Ambiesoft::AmbLib::GetSimpleVersion(System::Reflection::Assembly::GetExecutingAssembly()));

		Ambiesoft::CppUtils::CenteredMessageBox(this,
			message.ToString(),
			Application::ProductName,
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	System::Void FormMain::listMain_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		setNewAppIDToolStripMenuItem_Click(sender, e);
	}
}





