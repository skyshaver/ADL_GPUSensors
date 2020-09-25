#pragma once

#include "ADL_setup.h"

int PMLogDestroyD3DDevice(int adapterNumber, ADL_D3DKMT_HANDLE hDevice)
{
	if (ADL_OK != ADL2_Device_PMLog_Device_Destroy(context, hDevice))
	{
		PRINTF("Err: Failed to destory D3D device\n");
		return ADL_ERR;
	}

	return ADL_OK;
}

int PMLogCreateD3DDevice(int adapterNumber, ADL_D3DKMT_HANDLE* hDevice, LPAdapterInfo lpAdapterInfo)
{
	if (ADL_OK != ADL2_Device_PMLog_Device_Create(context, lpAdapterInfo[adapterNumber].iAdapterIndex, hDevice))
	{
		PRINTF("Err: Failed to create D3D device\n");
		return ADL_ERR;
	}

	return ADL_OK;
}

int GetPMLogSupport(int adapterNumber, ADLPMLogSupportInfo* adlPMLogSupportInfo, LPAdapterInfo lpAdapterInfo)
{

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Get(context, lpAdapterInfo[adapterNumber].iAdapterIndex, adlPMLogSupportInfo))
	{
		PRINTF("Err: Failed to get PMLog Support for adapter number: %d\n", adapterNumber);
		return ADL_ERR;
	}

	return ADL_OK;
}



int PrintAllSupportedSensors(int iNumberAdapters, LPAdapterInfo lpAdapterInfo)
{
	ADLPMLogSupportInfo adlPMLogSupportInfo;
	int  i = 0, j = 0;

	// Repeat for all available adapters in the system
	for (i = 0; i < iNumberAdapters; i++)
	{
		if (lpAdapterInfo[i].iBusNumber > -1)
		{
			if (GetPMLogSupport(i, &adlPMLogSupportInfo, lpAdapterInfo) == ADL_ERR)
				return ADL_ERR;

			PRINTF("Adapter number %d supported sensors:\n", i);
			while (adlPMLogSupportInfo.usSensors[j] != ADL_SENSOR_MAXTYPES)
			{

				switch (adlPMLogSupportInfo.usSensors[j])
				{
				case ADL_PMLOG_CLK_GFXCLK:
					PRINTF("Graphics Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_MEMCLK:
					PRINTF("Memory Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_SOCCLK:
					PRINTF("SOC Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_UVDCLK1:
					PRINTF("UVD1 Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_UVDCLK2:
					PRINTF("UVD2 Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_VCECLK:
					PRINTF("VCE Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_VCNCLK:
					PRINTF("VCN Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_EDGE:
					PRINTF("EDGE Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_MEM:
					PRINTF("Memory Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_VRVDDC:
					PRINTF("VDDC VR Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_VRSOC:
					PRINTF("SOC VR Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_VRMVDD:
					PRINTF("MVDD VR Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_VRMVDD0:
					PRINTF("MVDD0 VR Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_VRMVDD1:
					PRINTF("MVDD1 VR Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_LIQUID:
					PRINTF("Liquid Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_PLX:
					PRINTF("PLX Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_FAN_RPM:
					PRINTF("Fan RPM Sensor Detected\n");
					break;
				case ADL_PMLOG_FAN_PERCENTAGE:
					PRINTF("Fan Percentage Sensor Detected\n");
					break;
				case ADL_PMLOG_SOC_VOLTAGE:
					PRINTF("SOC Voltage Sensor Detected\n");
					break;
				case ADL_PMLOG_SOC_POWER:
					PRINTF("SOC Power Sensor Detected\n");
					break;
				case ADL_PMLOG_SOC_CURRENT:
					PRINTF("SOC Current Sensor Detected\n");
					break;
				case ADL_PMLOG_INFO_ACTIVITY_GFX:
					PRINTF("GFX Activity Sensor Detected\n");
					break;
				case ADL_PMLOG_INFO_ACTIVITY_MEM:
					PRINTF("MEM Activity Sensor Detected\n");
					break;
				case ADL_PMLOG_GFX_VOLTAGE:
					PRINTF("GFX Voltage Sensor Detected\n");
					break;
				case ADL_PMLOG_MEM_VOLTAGE:
					PRINTF("MEM Voltage Sensor Detected\n");
					break;
				case ADL_PMLOG_ASIC_POWER:
					PRINTF("Asic Power Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_HOTSPOT:
					PRINTF("HOTSPOT Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_GFX:
					PRINTF("GFX Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_SOC:
					PRINTF("SOC Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_TEMPERATURE_CPU:
					PRINTF("CPU Temperature Sensor Detected\n");
					break;
				case ADL_PMLOG_GFX_POWER:
					PRINTF("GFX Power Sensor Detected\n");
					break;
				case ADL_PMLOG_GFX_CURRENT:
					PRINTF("GFX Current Sensor Detected\n");
					break;
				case ADL_PMLOG_CPU_POWER:
					PRINTF("CPU Power Sensor Detected\n");
					break;
				case ADL_PMLOG_CLK_CPUCLK:
					PRINTF("CPU Clock Sensor Detected\n");
					break;
				case ADL_PMLOG_THROTTLER_STATUS:
					PRINTF("Throttler Status Sensor Detected\n");
					break;
				case ADL_SENSOR_MAXTYPES:
					PRINTF("End of Sensor Detected\n");
					break;
				default:
					PRINTF("ER: Uknown sensor detected\n");
					break;
				}
				PRINTF("ID: %d\n", adlPMLogSupportInfo.usSensors[j]);
				j++;
			}


		}

	}

	return ADL_OK;
}

void DisplayPMLogOutput(ADLPMLogData* PMLogOutput, int Duration)
{
	struct timeb startTime, currentTime;
	int diff;
	int i;

	ftime(&startTime);
	system("cls");
	do {
		i = 0;
		while (PMLogOutput->ulValues[i][0] != ADL_SENSOR_MAXTYPES)
		{

			switch (PMLogOutput->ulValues[i][0])
			{
			case ADL_PMLOG_CLK_GFXCLK:
				PRINTF("Graphics Clock Sensor: ");
				break;
			case ADL_PMLOG_CLK_MEMCLK:
				PRINTF("Memory Clock Sensor: ");
				break;
			case ADL_PMLOG_CLK_SOCCLK:
				PRINTF("SOC Clock Sensor: ");
				break;
			case ADL_PMLOG_CLK_UVDCLK1:
				PRINTF("UVD1 Clock Sensor: ");
				break;
			case ADL_PMLOG_CLK_UVDCLK2:
				PRINTF("UVD2 Clock Sensor: ");
				break;
			case ADL_PMLOG_CLK_VCECLK:
				PRINTF("VCE Clock Sensor: ");
				break;
			case ADL_PMLOG_CLK_VCNCLK:
				PRINTF("VCN Clock Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_EDGE:
				PRINTF("EDGE Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_MEM:
				PRINTF("Memory Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_VRVDDC:
				PRINTF("VDDC VR Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_VRSOC:
				PRINTF("SOC VR Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_VRMVDD:
				PRINTF("MVDD VR Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_VRMVDD0:
				PRINTF("MVDD0 VR Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_VRMVDD1:
				PRINTF("MVDD1 VR Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_LIQUID:
				PRINTF("Liquid Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_PLX:
				PRINTF("PLX Temperature Sensor: ");
				break;
			case ADL_PMLOG_FAN_RPM:
				PRINTF("Fan RPM Sensor: ");
				break;
			case ADL_PMLOG_FAN_PERCENTAGE:
				PRINTF("Fan Percentage Sensor: ");
				break;
			case ADL_PMLOG_SOC_VOLTAGE:
				PRINTF("SOC Voltage Sensor: ");
				break;
			case ADL_PMLOG_SOC_POWER:
				PRINTF("SOC Power Sensor: ");
				break;
			case ADL_PMLOG_SOC_CURRENT:
				PRINTF("SOC Current Sensor: ");
				break;
			case ADL_PMLOG_INFO_ACTIVITY_GFX:
				PRINTF("GFX Activity Sensor: ");
				break;
			case ADL_PMLOG_INFO_ACTIVITY_MEM:
				PRINTF("MEM Activity Sensor: ");
				break;
			case ADL_PMLOG_GFX_VOLTAGE:
				PRINTF("GFX Voltage Sensor: ");
				break;
			case ADL_PMLOG_MEM_VOLTAGE:
				PRINTF("MEM Voltage Sensor: ");
				break;
			case ADL_PMLOG_ASIC_POWER:
				PRINTF("Asic Power Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_HOTSPOT:
				PRINTF("HOTSPOT Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_GFX:
				PRINTF("GFX Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_SOC:
				PRINTF("SOC Temperature Sensor: ");
				break;
			case ADL_PMLOG_TEMPERATURE_CPU:
				PRINTF("CPU Temperature Sensor: ");
				break;
			case ADL_PMLOG_GFX_POWER:
				PRINTF("GFX Power Sensor: ");
				break;
			case ADL_PMLOG_GFX_CURRENT:
				PRINTF("GFX Current Sensor: ");
				break;
			case ADL_PMLOG_CPU_POWER:
				PRINTF("CPU Power Sensor: ");
				break;
			case ADL_PMLOG_CLK_CPUCLK:
				PRINTF("CPU Clock Sensor: ");
				break;
			case ADL_PMLOG_THROTTLER_STATUS:
				PRINTF("Throttler Status Sensor: ");
				break;
			case ADL_SENSOR_MAXTYPES:
				break;
			default:
				PRINTF("Unknown Sensor Value: ");
				break;
			}

			PRINTF("%d\n", PMLogOutput->ulValues[i][1]);
			i++;
		}

		Sleep(500);
		system("cls");
		ftime(&currentTime);
		diff = (int)(currentTime.time - startTime.time);
	} while (diff < Duration);
}


int PMLogAllSensorStart(int adapterNumber, int sampleRate, int Duration, LPAdapterInfo lpAdapterInfo)
{
	ADLPMLogSupportInfo adlPMLogSupportInfo;
	ADLPMLogStartInput adlPMLogStartInput;
	ADLPMLogStartOutput adlPMLogStartOutput;
	ADLPMLogData* PMLogOutput;
	int i = 0;

	if (hDevice == 0)
	{
		if (ADL_OK != PMLogCreateD3DDevice(lpAdapterInfo[adapterNumber].iAdapterIndex, &hDevice, lpAdapterInfo))
		{
			PRINTF("Err: Failed to create D3D Device, can not start PMLOG\n");
			return ADL_ERR;
		}
	}

	if (ADL_OK != GetPMLogSupport(lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogSupportInfo, lpAdapterInfo))
	{
		PRINTF("Err: Failed to get supported sensors, can not start PMLOG\n");
		return ADL_ERR;
	}


	while (adlPMLogSupportInfo.usSensors[i] != ADL_SENSOR_MAXTYPES)
	{
		adlPMLogStartInput.usSensors[i] = adlPMLogSupportInfo.usSensors[i];
		i++;
	}

	adlPMLogStartInput.usSensors[i] = ADL_SENSOR_MAXTYPES;
	adlPMLogStartInput.ulSampleRate = sampleRate;
	if (ADL_OK != ADL2_Adapter_PMLog_Support_Start(context, lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogStartInput, &adlPMLogStartOutput, hDevice))
	{
		PRINTF("Failed to start PMLOG\n");
		return ADL_ERR;
	}


	PMLogOutput = (ADLPMLogData*)(adlPMLogStartOutput.pLoggingAddress);

	DisplayPMLogOutput(PMLogOutput, Duration);

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Stop(context, lpAdapterInfo[adapterNumber].iAdapterIndex, hDevice))
	{
		PRINTF("Failed to get PMLog Support\n");
		return ADL_ERR;
	}

	return ADL_OK;
}

int PMLogMclkStart(int adapterNumber, int sampleRate, int Duration, LPAdapterInfo lpAdapterInfo)
{
	ADLPMLogSupportInfo adlPMLogSupportInfo;
	ADLPMLogStartInput adlPMLogStartInput;
	ADLPMLogStartOutput adlPMLogStartOutput;
	ADLPMLogData* PMLogOutput;
	int i = 0;

	if (hDevice == 0)
	{
		if (ADL_OK != PMLogCreateD3DDevice(lpAdapterInfo[adapterNumber].iAdapterIndex, &hDevice, lpAdapterInfo))
		{
			PRINTF("Err: Failed to create D3D Device, can not start PMLOG\n");
			return ADL_ERR;
		}
	}

	if (ADL_OK != GetPMLogSupport(lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogSupportInfo, lpAdapterInfo))
	{
		PRINTF("Err: Failed to get supported sensors, can not start PMLOG\n");
		return ADL_ERR;
	}


	adlPMLogStartInput.usSensors[0] = ADL_PMLOG_CLK_MEMCLK;


	adlPMLogStartInput.usSensors[1] = ADL_SENSOR_MAXTYPES;
	adlPMLogStartInput.ulSampleRate = sampleRate;

	PRINTF("Start MCLK PMGLOG\n");

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Start(context, lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogStartInput, &adlPMLogStartOutput, hDevice))
	{
		PRINTF("Failed to start MCLK PMGLOG\n");
		return ADL_ERR;
	}


	PMLogOutput = (ADLPMLogData*)(adlPMLogStartOutput.pLoggingAddress);

	DisplayPMLogOutput(PMLogOutput, Duration);

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Stop(context, lpAdapterInfo[adapterNumber].iAdapterIndex, hDevice))
	{
		PRINTF("Failed to get PMLog Support\n");
		return ADL_ERR;
	}

	return ADL_OK;
}

int PMLogFanStart(int adapterNumber, int sampleRate, int Duration, LPAdapterInfo lpAdapterInfo)
{
	ADLPMLogSupportInfo adlPMLogSupportInfo;
	ADLPMLogStartInput adlPMLogStartInput;
	ADLPMLogStartOutput adlPMLogStartOutput;
	ADLPMLogData* PMLogOutput;
	int i = 0;

	if (hDevice == 0)
	{
		if (ADL_OK != PMLogCreateD3DDevice(lpAdapterInfo[adapterNumber].iAdapterIndex, &hDevice, lpAdapterInfo))
		{
			PRINTF("Err: Failed to create D3D Device, can not start PMLOG\n");
			return ADL_ERR;
		}
	}

	if (ADL_OK != GetPMLogSupport(lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogSupportInfo, lpAdapterInfo))
	{
		PRINTF("Err: Failed to get supported sensors, can not start PMLOG\n");
		return ADL_ERR;
	}


	//adlPMLogStartInput.usSensors[0] = ADL_PMLOG_CLK_MEMCLK;
	adlPMLogStartInput.usSensors[0] = ADL_PMLOG_FAN_RPM;

	adlPMLogStartInput.usSensors[1] = ADL_SENSOR_MAXTYPES;
	adlPMLogStartInput.ulSampleRate = sampleRate;

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Start(context, lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogStartInput, &adlPMLogStartOutput, hDevice))
	{
		PRINTF("Failed to start MCLK PMGLOG\n");
		return ADL_ERR;
	}


	PMLogOutput = (ADLPMLogData*)(adlPMLogStartOutput.pLoggingAddress);

	DisplayPMLogOutput(PMLogOutput, Duration);

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Stop(context, lpAdapterInfo[adapterNumber].iAdapterIndex, hDevice))
	{
		PRINTF("Failed to get PMLog Support\n");
		return ADL_ERR;
	}

	return ADL_OK;
}

int PMLogGfxClkStart(int adapterNumber, int sampleRate, int Duration, LPAdapterInfo lpAdapterInfo)
{
	ADLPMLogSupportInfo adlPMLogSupportInfo;
	ADLPMLogStartInput adlPMLogStartInput;
	ADLPMLogStartOutput adlPMLogStartOutput;
	ADLPMLogData* PMLogOutput;
	int i = 0;

	if (hDevice == 0)
	{
		if (ADL_OK != PMLogCreateD3DDevice(lpAdapterInfo[adapterNumber].iAdapterIndex, &hDevice, lpAdapterInfo))
		{
			PRINTF("Err: Failed to create D3D Device, can not start PMLOG\n");
			return ADL_ERR;
		}
	}

	if (ADL_OK != GetPMLogSupport(lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogSupportInfo, lpAdapterInfo))
	{
		PRINTF("Err: Failed to get supported sensors, can not start PMLOG\n");
		return ADL_ERR;
	}

	adlPMLogStartInput.usSensors[0] = ADL_PMLOG_CLK_GFXCLK;

	adlPMLogStartInput.usSensors[1] = ADL_SENSOR_MAXTYPES;
	adlPMLogStartInput.ulSampleRate = sampleRate;

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Start(context, lpAdapterInfo[adapterNumber].iAdapterIndex, &adlPMLogStartInput, &adlPMLogStartOutput, hDevice))
	{
		PRINTF("Failed to start MCLK PMGLOG\n");
		return ADL_ERR;
	}


	PMLogOutput = (ADLPMLogData*)(adlPMLogStartOutput.pLoggingAddress);

	DisplayPMLogOutput(PMLogOutput, Duration);

	if (ADL_OK != ADL2_Adapter_PMLog_Support_Stop(context, lpAdapterInfo[adapterNumber].iAdapterIndex, hDevice))
	{
		PRINTF("Failed to get PMLog Support\n");
		return ADL_ERR;
	}

	return ADL_OK;
}


int parseCLArgs(int argc, char** argv, int iNumberAdapters, LPAdapterInfo lpAdapterInfo)
{
	int result = 0;
	if (argc >= 1)
	{



		switch (*(argv[1]))
		{
		case 'l':
			result = PrintAllSupportedSensors(iNumberAdapters, lpAdapterInfo);
			break;
		case 's':
			if (argc == 5)
				PMLogAllSensorStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), lpAdapterInfo);
			else
				printf("signature of PMLog all sensors (PMLog.exe s X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
			break;
		case 'm':
			if (argc == 5)
				PMLogMclkStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), lpAdapterInfo);
			else
				printf("signature of PMLog MCLK sensor (PMLog.exe m X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
			break;
		case 'f':
			if (argc == 5)
				PMLogFanStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), lpAdapterInfo);
			else
				printf("signature of PMLog fan sensor (PMLog.exe f X Y Z); X - Adapter Number, Y - Sample Rate (ms), Z - Duration to Log");
			break;
		case 'g':
			if (argc == 5)
				PMLogGfxClkStart(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), lpAdapterInfo);
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

	return result;
}