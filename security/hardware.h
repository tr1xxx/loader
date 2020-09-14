#pragma once
#include "includes.h"

namespace hardware {

	static const char* cpuId(void);
	std::string GetMachineGUID();

	extern std::string cpu_ID;
	extern std::string guid;

}
