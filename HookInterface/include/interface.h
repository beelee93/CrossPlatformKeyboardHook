#ifndef _HI_INTERFACE_H
#define _HI_INTERFACE_H

#if !defined(__unix__) && !defined(WIN32)
#error "Unknown OS"
#endif

#if !defined(NULL) 
#define NULL 0
#endif

#include <string>
#include <vector>

namespace HookInterface {
	struct _HOOK;

	typedef struct _HOOK HOOK;
	typedef struct _HOOK* PHOOK;

	struct _DEVICE;

	typedef struct _DEVICE DEVICE;
	typedef struct _DEVICE* PDEVICE;

	struct _DEVICELIST;

	typedef struct _DEVICELIST DEVICELIST;
	typedef struct _DEVICELIST* PDEVICELIST;

	// -- HOOK --

	/* Create a hook for the given device */
	PHOOK hookInit(PDEVICE pDev);

	/* Clean up */
	void hookDestroy(PHOOK* ppHook);

	// -- DEVICE LIST --

	/* Get a list of devices available for hooking and store the array to the 
	given pointer. Needs to be freed by deviceListFree() */
	PDEVICELIST deviceListGet();

	/* Frees the device list */
	void deviceListFree(PDEVICELIST* ppDevices);

	/* Gets the size of the device list */
	size_t deviceListSize(PDEVICELIST pDevices);

	/* Gets the name of the specified device */
	std::string deviceListDeviceName(PDEVICELIST pDevices, size_t index);
}

#endif