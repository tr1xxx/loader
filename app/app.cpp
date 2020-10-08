#include "app.h"

using namespace std::chrono_literals;

namespace app {

	size_t write_to_string(void* ptr, size_t size, size_t count, void* stream) {
		((std::string*)stream)->append((char*)ptr, 0, size * count);
		return size * count;
	}

	std::string random_string()
	{
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		std::random_device rd;
		std::mt19937 generator(rd());

		std::shuffle(str.begin(), str.end(), generator);

		return str.substr(0, 32);
	}

	auto login_loop()->void {

		VMProtectBeginUltra("login_loop");

		do {

			if (settings::login_pressed) {

				try {

					std::unique_ptr<Login_WebRequest> res{ new Login_WebRequest(settings::userBuffer, settings::passBuffer, hardware::guid) };

					res->login();

				}
				catch (const std::exception& e) {				
					std::cerr << e.what() << std::endl;
				}

			}

		} while (!settings::login_passed);

		VMProtectEnd();
	}

	auto render_loop()->void {

		VMProtectBeginUltra("render_loop");

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		menu::setup_menu();
		while (true)
		{
			if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
				continue;
			}

			menu::begin_draw();
			menu::render_menu();
			if (settings::login_passed)
				menu::inject_tab();
			menu::end_draw();

			if (settings::exit_pressed)
				break;

		}
		menu::menu_shutdown();

		VMProtectEnd();

		exit(0);

	}

	auto antidbg_loop()->void {

		while (true) {

			VMProtectIsProtected();
			VMProtectIsVirtualMachinePresent();
			VMProtectIsDebuggerPresent(settings::CheckKernelMode);
			VMProtectIsValidImageCRC();

			std::this_thread::sleep_for(1s);
		}

	}

	auto checksum_loop()-> void {

		VMProtectBeginUltra("checksum_loop");

		try {

			TCHAR szExeFileName[MAX_PATH];
			GetModuleFileName(NULL, szExeFileName, MAX_PATH);

			CryptoPP::SHA512 sha512;
			const size_t size = CryptoPP::SHA512::DIGESTSIZE * 2;
			byte buf[size] = { 0 };
			std::string strPath = VMProtectDecryptStringA(szExeFileName);
			CryptoPP::FileSource(
				strPath.c_str(), true,
				new CryptoPP::HashFilter(
					sha512, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf, size))));
			std::string strHash = std::string(reinterpret_cast<const char*>(buf), size);

			std::cout << strHash << std::endl;

			std::unique_ptr<Checksum_WebRequest> res{ new Checksum_WebRequest(strHash) };

			res->check_hash();

		}
		catch (const std::exception& e) {		
			std::cerr << e.what() << std::endl;
		}

		VMProtectEnd();

	}

	auto random_filename()-> void {

		VMProtectBeginUltra("random_filename");

		TCHAR szExeFileName[MAX_PATH];
		GetModuleFileName(NULL, szExeFileName, MAX_PATH);

		std::string newname = random_string() + ".exe";

		if (rename(szExeFileName, newname.c_str()) != 0)
			exit(0);

		VMProtectEnd();

	}

	auto load_driver()-> int {

		VMProtectBeginUltra("load_driver");

		const std::string driver_path = "C:\\Users\\Trix\\Desktop\\Rust Build\\kernelmode.sys";

		if (!std::filesystem::exists(driver_path))
		{
			std::cout << "[-] File " << driver_path << " doesn't exist" << std::endl;
			return -1;
		}

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

		VMProtectEnd();
	}

}