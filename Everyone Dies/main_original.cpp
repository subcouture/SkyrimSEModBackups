#include "Windows.h"
#include "../skse64/skse64/PluginAPI.h"
#include "../skse64/skse64_common/skse_version.h"

#include "Tools.h"

#define PLUGIN_VERSION 1
const char * PluginName = "EveryoneDiesPlugin";

extern "C"
{
	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
	{
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = PluginName;
		info->version = PLUGIN_VERSION;

		if (skse->isEditor || skse->runtimeVersion != RUNTIME_VERSION_1_5_62)
			return false;
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)
	{
		char jmp = (char)0xEB;

		// Patch function: 0x6AADF0
		// This is something like: bool Actor::IsKillableByX(Actor * this, Actor * attacker)
		{
			WriteMemory(0x6AAE00, &jmp, 1);
		};

		// More patch.
		WriteMemory(0x6D2C1D, &jmp, 1);

		// Patch uses of function: 0x6AAD20
		// This is something like: bool Actor::IsEssential(Actor * this, bool allowProtected)
		// Patch uses of function only and not the function itself! There may be scripts that rely on actor being essential.
		{
			static int _addrFunc = 0x6AAD20;
			{
				static int _addr1 = 0x6DFBDC;
				static int _addr2 = 0x6DFBE1;
				{
					START_ASM1(IE1)
						START_ASM2(IE1)
						START_ASM3(IE1)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE1, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x6E42E2;
				static int _addr2 = 0x6E42E7;
				{
					START_ASM1(IE2)
						START_ASM2(IE2)
						START_ASM3(IE2)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE2, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x6E4ADF;
				static int _addr2 = 0x6E4AE4;
				{
					START_ASM1(IE3)
						START_ASM2(IE3)
						START_ASM3(IE3)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE3, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x6E4D17;
				static int _addr2 = 0x6E4D1C;
				{
					START_ASM1(IE4)
						START_ASM2(IE4)
						START_ASM3(IE4)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE4, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x6E568F;
				static int _addr2 = 0x6E5694;
				{
					START_ASM1(IE5)
						START_ASM2(IE5)
						START_ASM3(IE5)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE5, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x6E99E8;
				static int _addr2 = 0x6E99ED;
				{
					START_ASM1(IE6)
						START_ASM2(IE6)
						START_ASM3(IE6)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE6, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x756C62;
				static int _addr2 = 0x756C67;
				{
					START_ASM1(IE7)
						START_ASM2(IE7)
						START_ASM3(IE7)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE7, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x7A73EF;
				static int _addr2 = 0x7A73F4;
				{
					START_ASM1(IE8)
						START_ASM2(IE8)
						START_ASM3(IE8)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE8, _addr1, _addr2)
				}
			};
			{
				static int _addr1 = 0x90DA0E;
				static int _addr2 = 0x90DA13;
				{
					START_ASM1(IE9)
						START_ASM2(IE9)
						START_ASM3(IE9)

						call _addrFunc
						xor eax, eax
						jmp _addr2

						END_ASM(IE9, _addr1, _addr2)
				}
			};
		};

		// Allow kill children, evil.
		{
			static int _addr1 = 0x6A9296;
			static int _addr2 = 0x6A92A2;
			{
				START_ASM1(IE10)
					START_ASM2(IE10)
					START_ASM3(IE10)

					xor eax, eax
					jmp _addr2

					END_ASM(IE10, _addr1, _addr2)
			};

			char xor[2];
			xor[0] = (char)0x31;
			xor[1] = (char)0xC0;
			WriteMemory(0x79F51A, xor, 2);

			WriteMemory(0x6D6B8F, &jmp, 1);
		};

		static char nop[8];
		for (int i = 0; i < 8; i++)
			nop[i] = (char)0x90;

		// Another essential check when dying.
		WriteMemory(0x6B10D3, nop, 2);
		WriteMemory(0x6AC302, nop, 2);
		WriteMemory(0x6D3E9C, nop, 6);
		WriteMemory(0x6AC02D, nop, 2);
		return true;
	}
}
