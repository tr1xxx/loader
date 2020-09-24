#include "app.h"
#include "http/http.hpp"

using json = nlohmann::json;
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

		VMProtectBeginUltra(login_function);

		do {

			if (settings::login_pressed) {

				http::Response response;

				try
				{

					http::Request request(VMProtectDecryptStringA("http://localhost/loader/check.php"));
					// pass parameters as a map
					std::map<std::string, std::string> parameters = { {VMProtectDecryptStringA("username"), VMProtectDecryptStringA(settings::userBuffer)}, {VMProtectDecryptStringA("password"), VMProtectDecryptStringA(settings::passBuffer)}, {VMProtectDecryptStringA("hwid"), VMProtectDecryptStringA(hardware::guid.c_str())} };
					response = request.send("POST", parameters, {
						"Content-Type: application/x-www-form-urlencoded"
						});

				}
				catch (const std::exception& e)
				{
					std::cerr << "Request failed, error: " << e.what() << '\n';
				}

				json j = json::parse(response.body.begin(), response.body.end());

				std::cout << j << std::endl;

				if (j[VMProtectDecryptStringA("success")] == true) {

					MessageBox(NULL, VMProtectDecryptStringA("successful!"), VMProtectDecryptStringA("login"), MB_OK);

					if (j[VMProtectDecryptStringA("hwid")] == true) {
						settings::login_passed = true;
					}
					else if (j[VMProtectDecryptStringA("new_hwid")] == true) {
						MessageBox(NULL, VMProtectDecryptStringA("hwid set!"), VMProtectDecryptStringA("login"), MB_OK);
						settings::login_passed = true;
					}
					else if (j[VMProtectDecryptStringA("hwid")] == false && j[VMProtectDecryptStringA("new_hwid")] == false) {
						MessageBox(NULL, VMProtectDecryptStringA("incorrect hwid!"), VMProtectDecryptStringA("login"), MB_OK);
						exit(0);
					}

				}
				else if (j[VMProtectDecryptStringA("success")] == false) {
					MessageBox(NULL, VMProtectDecryptStringA("incorrect credentials!"), VMProtectDecryptStringA("login"), MB_OK);
					exit(0);
				}

			}

		} while (!settings::login_passed);
		VMProtectEnd();
	}

	auto render_menu()->void {

		VMProtectBeginUltra(menu_function);

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

		VMProtectBeginUltra(checksum_function);

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

		http::Response response;

		try
		{

			http::Request request(VMProtectDecryptStringA("http://localhost/loader/checksum.php"));
			// pass parameters as a map
			std::map<std::string, std::string> parameters = { {VMProtectDecryptStringA("hash"), VMProtectDecryptStringA(strHash.c_str())} };
			response = request.send("POST", parameters, {
				"Content-Type: application/x-www-form-urlencoded"
				});

		}
		catch (const std::exception& e)
		{
			std::cerr << "Request failed, error: " << e.what() << '\n';
		}

		json j = json::parse(response.body.begin(), response.body.end());

		std::cout << j << std::endl;

		if (j[VMProtectDecryptStringA("success")] == false) {
			MessageBox(NULL, VMProtectDecryptStringA("Outdated Version, Please download the newest version on the website!"), VMProtectDecryptStringA("checksum error"), MB_OK);
			exit(0);
		}

		VMProtectEnd();

	}

	auto random_filename()-> void {

		VMProtectBeginUltra(rename_filename);
	
		TCHAR szExeFileName[MAX_PATH];
		GetModuleFileName(NULL, szExeFileName, MAX_PATH);

		std::string newname = random_string() + ".exe";

		if (rename(szExeFileName, newname.c_str()) != 0)
			exit(0);

		VMProtectEnd();

	}

}