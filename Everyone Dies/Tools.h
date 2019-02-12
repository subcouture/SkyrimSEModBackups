#ifndef _Tools_H
#define _Tools_H

#define START_ASM1(b) void * jumpAddress = NULL; _asm { mov jumpAddress, offset b##CodeStart
#define START_ASM2(b) jmp b##CodeEnd
#define START_ASM3(b) b##CodeStart:

#define END_ASM(b, addr1, addr2) b##CodeEnd: \
} \
	WriteJump(addr1, addr2, (int)jumpAddress);

bool WriteJump(int addressFrom1, int addressFrom2, int addressTo)
{
	DWORD oldProtect = 0;

	int len1 = addressFrom2 - addressFrom1;
	if (VirtualProtect((void *)addressFrom1, len1, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		*((unsigned char *)addressFrom1) = (unsigned char)0xE9;
		*((int *)(addressFrom1 + 1)) = (int)addressTo - addressFrom1 - 5;
		for (int i = 5; i < len1; i++)
			*((unsigned char *)(i + addressFrom1)) = (unsigned char)0x90;
		if (VirtualProtect((void *)addressFrom1, len1, oldProtect, &oldProtect))
			return true;
	}

	return false;
}

bool WriteMemory(int address, char * data, int length)
{
	DWORD oldProtect = 0;

	if (VirtualProtect((void *)address, length, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		memcpy((void*)address, data, length);
		if (VirtualProtect((void *)address, length, oldProtect, &oldProtect))
			return true;
	}

	return false;
}

#endif

