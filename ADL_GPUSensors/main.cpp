#include <tchar.h>

#include <algorithm>
#include <cstdio>
#include <iostream>

#include "Sensor.h"

int main(int argc, char* argv[])
{
	int result = 0;
	LPAdapterInfo   lpAdapterInfo = nullptr;

	if (initializeADL())
	{
		// Obtain the number of adapters for the system
		int iNumberAdapters = 0;
		if (ADL_OK != ADL_Adapter_NumberOfAdapters_Get(&iNumberAdapters))
		{
			PRINTF("Cannot get the number of adapters!\n");
			return 0;
		}

		// Get the AdapterInfo structure for all adapters in the system
		if (iNumberAdapters > 0)
		{
			lpAdapterInfo = (LPAdapterInfo)malloc(sizeof(AdapterInfo) * iNumberAdapters);
			if (lpAdapterInfo)
			{
				memset(lpAdapterInfo, '\0', sizeof(AdapterInfo) * iNumberAdapters);
				ADL_Adapter_AdapterInfo_Get(lpAdapterInfo, sizeof(AdapterInfo) * iNumberAdapters);
			}
			else
			{
				PRINTF("Failed to alloc AdapterInfo");
				return 0;
			}			

		}

		result = PrintAllSupportedSensors(iNumberAdapters, lpAdapterInfo);

		
		// cleanup
		ADL_Main_Memory_Free((void**)&lpAdapterInfo);

		deinitializeADL();
	}

	return result;
}
