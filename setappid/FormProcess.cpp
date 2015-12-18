#include "StdAfx.h"
#include "FormProcess.h"
#include "../../MyUtility/GetFileNameFromHwnd.h"

#pragma comment(lib, "Shell32.lib")
using namespace std;


EXTERN_C const PROPERTYKEY DECLSPEC_SELECTANY PKEY_AppUserModel_ID =
{ { 0x9F4C2855, 0x9F79, 0x4B39,
{ 0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3, } }, 5 };

namespace setappid {

	struct EnumData
	{
		EnumData(int p, const wstring& pa, const wstring& app) : pid(p),path(pa), appid(app){}
		EnumData(const EnumData& data) {
			pid=data.pid;
			path=data.path;
			appid=data.appid;
		}
		DWORD pid;
		wstring path;
		wstring appid;
	};

	BOOL CALLBACK ewp(HWND hwnd, LPARAM lParam)
	{
		DWORD pid=0;
		GetWindowThreadProcessId(hwnd, &pid);

		TCHAR szT[MAX_PATH]; szT[0]=0;
		if(!GetFileNameFromHwnd(hwnd, szT, sizeof(szT)))
			return TRUE;

		vector<EnumData>& vh = *( (vector<EnumData>*)lParam );

		IPropertyStore* pPS=NULL;
		if(SUCCEEDED(SHGetPropertyStoreForWindow(hwnd, IID_IPropertyStore, (void**)&pPS)))
		{
			PROPVARIANT pv;
			PropVariantInit(&pv);
			HRESULT hr = pPS->GetValue(PKEY_AppUserModel_ID, &pv);
			if(SUCCEEDED(hr))
			{
				if(pv.vt == VT_LPWSTR)
				{
					if(pv.pwszVal[0])
					{
						vh.push_back(EnumData(pid, szT, pv.pwszVal));
					}
				}
			
				PropVariantClear(&pv);
			}
			pPS->Release();
		}
		return TRUE;
	}

	System::Void FormProcess::FormProcess_Load(System::Object^  sender, System::EventArgs^  e)
	{
		vector<EnumData> vh;
		EnumWindows(ewp, (LPARAM)&vh);
	}

}