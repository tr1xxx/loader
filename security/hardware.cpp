#include "hardware.h"

namespace hardware {

	/*static const char* cpuId(void)
	{
		unsigned long s1 = 0;
		unsigned long s2 = 0;
		unsigned long s3 = 0;
		unsigned long s4 = 0;
		__asm
		{
			mov eax, 00h
			xor edx, edx
			cpuid
			mov s1, edx
			mov s2, eax
		}
		__asm
		{
			mov eax, 01h
			xor ecx, ecx
			xor edx, edx
			cpuid
			mov s3, edx
			mov s4, ecx
		}

		static char buf[100];
		sprintf_s(buf, "%08X%08X%08X%08X", s1, s2, s3, s4);
		return buf;
	}*/

	std::string GetMachineGUID()
	{
		std::string ret;
		char value[64];
		DWORD size = _countof(value);
		DWORD type = REG_SZ;
		HKEY key;
		LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0, KEY_READ | KEY_WOW64_64KEY, &key);
		LONG retVal = ::RegQueryValueExA(key, "MachineGuid", nullptr, &type, (LPBYTE)value, &size);
		if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
			ret = value;
		}
		::RegCloseKey(key);
		return ret;
	}

	//std::string cpu_ID = cpuId();
	std::string guid = GetMachineGUID();

}
