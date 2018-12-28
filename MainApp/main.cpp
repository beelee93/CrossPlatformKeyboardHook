#include "interface.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	using namespace HookInterface;

	PDEVICELIST devList = deviceListGet();
	size_t count = deviceListSize(devList);
	printf("Found %d devices\n", count);

	for (size_t i = 0; i < count; i++) {
		printf("%2d : %s\n",i, deviceListDeviceName(devList, i).c_str());
	}

	getchar();

	return 0;
}