#pragma once
#include <string>
#include "color.h"
#include <vector>
#include <map>
#include <mutex>

namespace settings
{

	extern char userBuffer[255];
	extern char passBuffer[255];

	extern std::string username_saved;
	extern std::string password_saved;

	extern bool login_pressed;
	extern bool exit_pressed;

	extern bool login_passed;

	extern bool CheckKernelMode;

}