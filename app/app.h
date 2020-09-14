#pragma once
#include "../security/includes.h"

namespace app {

	size_t write_to_string(void* ptr, size_t size, size_t count, void* stream);

	auto login_loop()-> void;
	auto render_menu()-> void;
	auto antidbg_loop()-> void;
	auto checksum_loop()-> void;

}