#if defined(WIN32)
#include "interface.h"
#include <Windows.h>

using namespace HookInterface;

struct HookInterface::_HOOK {
	HWND hWnd;
	HINSTANCE hInst;
};

struct HookInterface::_DEVICE {
	std::string deviceName;
	HANDLE hDevice;
};

struct HookInterface::_DEVICELIST {
	PDEVICE deviceList;
	size_t count;
};

PHOOK HookInterface::hookInit(PDEVICE pDev)
{
	return NULL;
}

void HookInterface::hookDestroy(PHOOK * ppHook)
{
}

PDEVICELIST HookInterface::deviceListGet()
{
	uint32_t numDevices;
	PRAWINPUTDEVICELIST devList = NULL;
	uint32_t numActualDevices = 0;
	PDEVICE devices = NULL;

	RID_DEVICE_INFO devInfo = { 0 };
	uint32_t devInfoSize = sizeof(devInfo);

	char nameBuffer[256] = "";
	uint32_t nameBufferSize = 255;
	int keyboardDeviceCounter = 0;

	PDEVICELIST result = (PDEVICELIST)malloc(sizeof(DEVICELIST));
	if (!result) return NULL;

	GetRawInputDeviceList(NULL, &numDevices, sizeof(RAWINPUTDEVICELIST));

	devList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * numDevices);
	if (!devList) {
		goto onerr1;
		return 0;
	}

	numActualDevices = GetRawInputDeviceList(devList, &numDevices, sizeof(RAWINPUTDEVICELIST));

	devices = new DEVICE[numActualDevices];
	if (!devices) {
		goto onerr2;
	}

	for (size_t i = 0; i < numActualDevices; i++) {
		GetRawInputDeviceInfo(devList[i].hDevice, RIDI_DEVICEINFO, &devInfo, &devInfoSize);

		if (devInfo.dwType != RIM_TYPEKEYBOARD) continue;

		GetRawInputDeviceInfo(devList[i].hDevice, RIDI_DEVICENAME, nameBuffer, &nameBufferSize);
		devices[keyboardDeviceCounter].deviceName = std::string(nameBuffer);
		devices[keyboardDeviceCounter].hDevice = devList[i].hDevice;
		keyboardDeviceCounter++;
	}

	result->count = keyboardDeviceCounter;
	result->deviceList = devices;

	free(devList); devList = NULL;
	return result;

onerr2:
	free(devList);
onerr1:
	free(result);

	return NULL;
}

void HookInterface::deviceListFree(PDEVICELIST * ppDevices)
{
	if (*ppDevices) {
		if ((*ppDevices)->deviceList) {
			free((*ppDevices)->deviceList);
			(*ppDevices)->deviceList = NULL;
		}
		delete[] (*ppDevices);
		*ppDevices = NULL;
	}
}

size_t HookInterface::deviceListSize(PDEVICELIST pDevices)
{
	if (pDevices)
		return pDevices->count;
	else
		return 0;
}

std::string HookInterface::deviceListDeviceName(PDEVICELIST pDevices, size_t index)
{
	return (pDevices && pDevices->count > index) ? pDevices->deviceList[index].deviceName : "";
}

#endif