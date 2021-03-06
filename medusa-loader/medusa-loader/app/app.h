#pragma once
#include "../security/includes.h"
#include "WebRequests/web.h"

namespace app {

	size_t write_to_string(void* ptr, size_t size, size_t count, void* stream);
	std::string random_string();

	auto login_loop()-> void;
	auto render_loop()-> void;
	auto antidbg_loop()-> void;
	auto checksum_loop()-> void;
	auto random_filename()-> void;
	auto load_driver()-> int;

}