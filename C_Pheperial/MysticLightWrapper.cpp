#include <windows.h>
#include <iostream>
#include "MysticLight_SDK.h"
#define MYSTICLIGHTDLL "MysticLight_SDK_x64.dll"


class MysticLight {
private:
	typedef int (*LPMLAPI_Initialize)();
	typedef int (*LPMLAPI_GetDeviceInfo)(SAFEARRAY** pDevType, SAFEARRAY** pLedCount);
	typedef int (*LPMLAPI_GetDeviceName)(BSTR type, SAFEARRAY** pDevName);
	typedef int (*LPMLAPI_GetDeviceNameEx)(BSTR type, DWORD index, BSTR* pDevName);
	typedef int (*LPMLAPI_GetErrorMessage)(int ErrorCode, BSTR* pDesc);
	typedef int (*LPMLAPI_GetLedName)(BSTR type, SAFEARRAY** pLedName);
	typedef int (*LPMLAPI_GetLedInfo)(BSTR type, DWORD index, BSTR* pName, SAFEARRAY** pLedStyles);
	typedef int (*LPMLAPI_GetLedColor)(BSTR type, DWORD index, DWORD* R, DWORD* G, DWORD* B);
	typedef int (*LPMLAPI_GetLedStyle)(BSTR type, DWORD index, BSTR* style);
	typedef int (*LPMLAPI_GetLedMaxBright)(BSTR type, DWORD index, DWORD* maxLevel);
	typedef int (*LPMLAPI_GetLedBright)(BSTR type, DWORD index, DWORD* currentLevel);
	typedef int (*LPMLAPI_GetLedMaxSpeed)(BSTR type, DWORD index, DWORD* maxLevel);
	typedef int (*LPMLAPI_GetLedSpeed)(BSTR type, DWORD index, DWORD* currentLevel);
	typedef int (*LPMLAPI_SetLedColor)(BSTR type, DWORD index, DWORD R, DWORD G, DWORD B);
	typedef int (*LPMLAPI_SetLedColors)(BSTR type, DWORD AreaIndex, SAFEARRAY** pLedName, DWORD* R, DWORD* G, DWORD* B);
	typedef int (*LPMLAPI_SetLedColorEx)(BSTR type, DWORD AreaIndex, BSTR pLedName, DWORD R, DWORD G, DWORD B, DWORD);
	typedef int (*LPMLAPI_SetLedColorSync)(BSTR type, DWORD AreaIndex, BSTR pLedName, DWORD R, DWORD G, DWORD B, DWORD);
	typedef int (*LPMLAPI_SetLedStyle)(BSTR type, DWORD index, BSTR style);
	typedef int (*LPMLAPI_SetLedBright)(BSTR type, DWORD index, DWORD level);
	typedef int (*LPMLAPI_SetLedSpeed)(BSTR type, DWORD index, DWORD level);

	LPMLAPI_Initialize Initialize = nullptr;
	LPMLAPI_GetDeviceName GetDeviceName = nullptr;
	HMODULE m_MysticLightSDKModule = NULL;

public:
	MysticLight() {
		
		m_MysticLightSDKModule = LoadLibrary("C:\\Users\\FlagShipPC\\source\\repos\\C_Pheperial\\Library\\MysticLightSDK\\MysticLight_SDK_x64.dll");
		Initialize = reinterpret_cast<LPMLAPI_Initialize>(GetProcAddress(m_MysticLightSDKModule, "MLAPI_Initialize"));
		GetDeviceName = reinterpret_cast<LPMLAPI_GetDeviceName>(GetProcAddress(m_MysticLightSDKModule, "MLAPI_GetDeviceNameEx"));

	}

	void init(void) {
		std::cout << (int)Initialize() <<  std::endl;;
	}
	
	void get_device_name(void) {
		BSTR type = NULL;
		SAFEARRAY* pDevName;

		std::cout << GetDeviceName(type, &pDevName) << std::endl;
	}

};
