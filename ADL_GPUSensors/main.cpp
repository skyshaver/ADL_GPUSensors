#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include "Sensor.h"

int main(int argc, char* argv[])
{
	int result = 0;

	if (initializeADL())
	{

		if (argc >= 1)
		{
			// Obtain the number of adapters for the system
			int iNumberAdapters = 0;
			if (ADL_OK != ADL_Adapter_NumberOfAdapters_Get(&iNumberAdapters))
			{
				PRINTF("Cannot get the number of adapters!\n");
				return 0;
			}

			if (0 < iNumberAdapters)
			{
				lpAdapterInfo = (LPAdapterInfo)malloc(sizeof(AdapterInfo) * iNumberAdapters);
				memset(lpAdapterInfo, '\0', sizeof(AdapterInfo) * iNumberAdapters);

				// Get the AdapterInfo structure for all adapters in the system
				ADL_Adapter_AdapterInfo_Get(lpAdapterInfo, sizeof(AdapterInfo) * iNumberAdapters);
			}

			result = PrintAllSupportedSensors(iNumberAdapters);


			switch (*(argv[1]))
			{
			case 'l':
				result = PrintAllSupportedSensors(iNumberAdapters);
				break;
			case 's':
				if (argc == 5)
					PMLogAllSensorStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
				else
					printf("signature of PMLog all sensors (PMLog.exe s X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
				break;
			case 'm':
				if (argc == 5)
					PMLogMclkStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
				else
					printf("signature of PMLog MCLK sensor (PMLog.exe m X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
				break;
			case 'f':
				if (argc == 5)
					PMLogFanStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
				else
					printf("signature of PMLog fan sensor (PMLog.exe f X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
				break;
			case 'g':
				if (argc == 5)
					PMLogGfxClkStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
				else
					printf("signature of PMLog GFX clock sensor (PMLog.exe g X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
				break;

			default:
				printf("Available command line parameters: l- List All sensors, s-start log all sensors, m-start log MCLK sensor, f-start fan sensor, g-start GFX clock sensor\n");

				break;
			}
		}
		else
		{
			printf("Available command line parameters: l- List All sensors, s-start log all sensors, m-start log MCLK sensor, f-start fan sensor, g-start GFX clock sensor\n");
		}

		ADL_Main_Memory_Free((void**)&lpAdapterInfo);

		deinitializeADL();
	}

	return result;
}
