#pragma once


#include <windows.h>
#include <sys\timeb.h>
#include <signal.h>

#include "adl_sdk.h"
#include "adl_structures.h"
#include "adl_defines.h"

#include <fmt/core.h>


// Definitions of the used function pointers. Add more if you use other ADL APIs
typedef int (*ADL_MAIN_CONTROL_CREATE)(ADL_MAIN_MALLOC_CALLBACK, int);
typedef int (*ADL_MAIN_CONTROL_DESTROY)();
typedef int (*ADL_FLUSH_DRIVER_DATA)(int);
typedef int (*ADL2_ADAPTER_ACTIVE_GET) (ADL_CONTEXT_HANDLE, int, int*);

typedef int (*ADL_ADAPTER_NUMBEROFADAPTERS_GET) (int*);
typedef int (*ADL_ADAPTER_ADAPTERINFO_GET) (LPAdapterInfo, int);
typedef int (*ADL2_ADAPTER_PMLOG_SUPPORT_GET) (ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLPMLogSupportInfo* pPMLogSupportInfo);
typedef int (*ADL2_ADAPTER_PMLOG_SUPPORT_START) (ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADLPMLogStartInput* pPMLogStartInput, ADLPMLogStartOutput* pPMLogStartOutput, ADL_D3DKMT_HANDLE pDevice);
typedef int (*ADL2_ADAPTER_PMLOG_SUPPORT_STOP) (ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_D3DKMT_HANDLE pDevice);
typedef int (*ADL2_DEVICE_PMLOG_DEVICE_CREATE) (ADL_CONTEXT_HANDLE context, int iAdapterIndex, ADL_D3DKMT_HANDLE* pDevice);
typedef int (*ADL2_DEVICE_PMLOG_DEVICE_DESTROY) (ADL_CONTEXT_HANDLE context, ADL_D3DKMT_HANDLE hDevice);


ADL_MAIN_CONTROL_CREATE				ADL_Main_Control_Create = NULL;
ADL_MAIN_CONTROL_DESTROY			ADL_Main_Control_Destroy = NULL;
ADL_ADAPTER_NUMBEROFADAPTERS_GET	ADL_Adapter_NumberOfAdapters_Get = NULL;
ADL_ADAPTER_ADAPTERINFO_GET			ADL_Adapter_AdapterInfo_Get = NULL;
ADL2_ADAPTER_ACTIVE_GET				ADL2_Adapter_Active_Get = NULL;
ADL2_ADAPTER_PMLOG_SUPPORT_GET		ADL2_Adapter_PMLog_Support_Get = NULL;
ADL2_ADAPTER_PMLOG_SUPPORT_START	ADL2_Adapter_PMLog_Support_Start = NULL;
ADL2_ADAPTER_PMLOG_SUPPORT_STOP		ADL2_Adapter_PMLog_Support_Stop = NULL;
ADL2_DEVICE_PMLOG_DEVICE_CREATE		ADL2_Device_PMLog_Device_Create = NULL;
ADL2_DEVICE_PMLOG_DEVICE_DESTROY	ADL2_Device_PMLog_Device_Destroy = NULL;

// Memory allocation function
void* __stdcall ADL_Main_Memory_Alloc(int iSize)
{
	void* lpBuffer = malloc(iSize);
	return lpBuffer;
}

// Optional Memory de-allocation function
void __stdcall ADL_Main_Memory_Free(void** lpBuffer)
{
	if (NULL != *lpBuffer)
	{
		free(*lpBuffer);
		*lpBuffer = NULL;
	}
}

ADL_CONTEXT_HANDLE context = NULL;
ADL_D3DKMT_HANDLE hDevice = 0;

// LPAdapterInfo   lpAdapterInfo = nullptr; // moved to main() scope
HINSTANCE hDLL;

// int  iNumberAdapters; // moved to main() scope

int initializeADL()
{

	// Load the ADL dll
	hDLL = LoadLibrary(TEXT("atiadlxx.dll"));
	if (hDLL == NULL)
	{
		// A 32 bit calling application on 64 bit OS will fail to LoadLibrary.
		// Try to load the 32 bit library (atiadlxy.dll) instead
		hDLL = LoadLibrary(TEXT("atiadlxy.dll"));
	}

	if (NULL == hDLL)
	{
		fmt::print(stderr, "Failed to load ADL library\n");
		return FALSE;
	}

	ADL_Main_Control_Create = (ADL_MAIN_CONTROL_CREATE)GetProcAddress(hDLL, "ADL_Main_Control_Create");
	ADL_Main_Control_Destroy = (ADL_MAIN_CONTROL_DESTROY)GetProcAddress(hDLL, "ADL_Main_Control_Destroy");
	ADL_Adapter_NumberOfAdapters_Get = (ADL_ADAPTER_NUMBEROFADAPTERS_GET)GetProcAddress(hDLL, "ADL_Adapter_NumberOfAdapters_Get");
	ADL_Adapter_AdapterInfo_Get = (ADL_ADAPTER_ADAPTERINFO_GET)GetProcAddress(hDLL, "ADL_Adapter_AdapterInfo_Get");
	ADL2_Adapter_Active_Get = (ADL2_ADAPTER_ACTIVE_GET)GetProcAddress(hDLL, "ADL2_Adapter_Active_Get");
	ADL2_Adapter_PMLog_Support_Get = (ADL2_ADAPTER_PMLOG_SUPPORT_GET)GetProcAddress(hDLL, "ADL2_Adapter_PMLog_Support_Get");
	ADL2_Adapter_PMLog_Support_Start = (ADL2_ADAPTER_PMLOG_SUPPORT_START)GetProcAddress(hDLL, "ADL2_Adapter_PMLog_Start");
	ADL2_Adapter_PMLog_Support_Stop = (ADL2_ADAPTER_PMLOG_SUPPORT_STOP)GetProcAddress(hDLL, "ADL2_Adapter_PMLog_Stop");
	ADL2_Device_PMLog_Device_Create = (ADL2_DEVICE_PMLOG_DEVICE_CREATE)GetProcAddress(hDLL, "ADL2_Device_PMLog_Device_Create");
	ADL2_Device_PMLog_Device_Destroy = (ADL2_DEVICE_PMLOG_DEVICE_DESTROY)GetProcAddress(hDLL, "ADL2_Device_PMLog_Device_Destroy");

	if ( ADL_Main_Control_Create			== nullptr ||
		 ADL_Main_Control_Destroy			== nullptr ||
		 ADL_Adapter_NumberOfAdapters_Get	== nullptr ||
		 ADL_Adapter_AdapterInfo_Get		== nullptr ||
		 ADL2_Adapter_Active_Get			== nullptr ||
		 ADL2_Adapter_PMLog_Support_Get		== nullptr ||
		 ADL2_Adapter_PMLog_Support_Start	== nullptr ||
		 ADL2_Adapter_PMLog_Support_Stop	== nullptr ||
		 ADL2_Device_PMLog_Device_Create	== nullptr ||
		 ADL2_Device_PMLog_Device_Destroy	== nullptr
		)
	{
		fmt::print(stderr, "Failed to get ADL function pointers\n");
		return FALSE;
	}

	if (ADL_OK != ADL_Main_Control_Create(ADL_Main_Memory_Alloc, 1))
	{
		fmt::print(stderr, "Failed to initialize nested ADL2 context");
		return ADL_ERR;
	}

	return TRUE;
}



void deinitializeADL()
{
	ADL_Main_Control_Destroy();
	FreeLibrary(hDLL);
}