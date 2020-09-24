#include "security/includes.h"
#include "kdmapper/kdmapper.hpp"

int main()
{

	VMProtectBeginUltra(main_function);

	const std::string driver_path = "C:\\Users\\Trix\\Desktop\\Rust Build\\kernelmode.sys";

	/*if (!std::filesystem::exists(driver_path))
	{
		std::cout << "[-] File " << driver_path << " doesn't exist" << std::endl;
		return -1;
	}*/

	HANDLE iqvw64e_device_handle = intel_driver::Load();

	if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "[-] Failed to load driver iqvw64e.sys" << std::endl;
		return -1;
	}

	if (!kdmapper::MapDriver(iqvw64e_device_handle, driver_path))
	{
		std::cout << "[-] Failed to map " << driver_path << std::endl;
		intel_driver::Unload(iqvw64e_device_handle);
		return -1;
	}

	intel_driver::Unload(iqvw64e_device_handle);
	std::cout << "[+] success" << std::endl;

	std::thread antidbg_thread(app::antidbg_loop);
	std::thread random_thread(app::random_filename);
	//app::checksum_loop();
	std::thread login_thread(app::login_loop);
	std::thread menu_render_thread(app::render_menu);

	std::cin.get();

	VMProtectEnd();

	return 0;

}