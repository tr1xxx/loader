#pragma once
#define NOMINMAX
#define _WINSOCKAPI_
#include <Windows.h>
#include <string>
#include <filesystem>
#include "intel_driver.hpp"

namespace service
{
	bool RegisterAndStart(const std::string& driver_path);
	bool StopAndRemove(const std::string& driver_name);
};