#include <stdio.h>
#include <malloc.h>
#include "type.h"
#include "crc.h"

/*****************************************************************************
*explain: 8 bit数据 
******************************************************************************/
u8 data[] = {
	0x51, 0x51, 0x51, 0x51, 0x51, 0x51,
	0x51, 0x51, 0x51, 0x51, 0x51, 0x51,
	0x51, 0x51, 0x51, 0x51, 0x51, 0x51
};

int main() {
	int len = sizeof(data) / sizeof(data[0]);
	u32 crc = crc32(data, len, crc_32);
	printf("%x\n", crc);
	return 0;
}
