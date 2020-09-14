#include "app.h"

using json = nlohmann::json;
using namespace std::chrono_literals;

namespace app {

	size_t write_to_string(void* ptr, size_t size, size_t count, void* stream) {
		((std::string*)stream)->append((char*)ptr, 0, size * count);
		return size * count;
	}

	auto login_loop()->void {

		VMProtectBeginUltra(login_function);

		do {

			if (settings::login_pressed) {

				int length_user = sprintf(settings::userBuffer, "%s", settings::userBuffer);
				int length_pass = sprintf(settings::passBuffer, "%s", settings::passBuffer);

				char request[512];
				std::string response;

				CURL* curl;
				CURLcode res;

				curl_global_init(CURL_GLOBAL_ALL);

				curl = curl_easy_init();

				if (curl) {

					sprintf(request, VMProtectDecryptStringA("username=%s&password=%s&hwid=%s"), curl_easy_escape(curl, settings::userBuffer, length_user), curl_easy_escape(curl, settings::passBuffer, length_pass), hardware::guid);

					curl_easy_setopt(curl, CURLOPT_URL, VMProtectDecryptStringA("http://localhost/loader/check.php"));
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, VMProtectDecryptStringA(request));

					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

					res = curl_easy_perform(curl);

					if (res != CURLE_OK)
						fprintf(stderr, VMProtectDecryptStringA("curl_easy_perform() failed: %s\n"),
							curl_easy_strerror(res));

					curl_easy_cleanup(curl);

				}
				curl_global_cleanup();

				json j = json::parse(response);

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

		} while (settings::login_passed == false);

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

		VMProtectBeginUltra(debug_function);

		while (true) {
			// -------------------------------------------------------------------
			// -- Memory Checks --------------------------------------------------
			// -------------------------------------------------------------------
			adbg_IsDebuggerPresent();
			adbg_CheckRemoteDebuggerPresent();
			adbg_CheckWindowName();
			adbg_NtQueryInformationProcess();
			adbg_BeingDebuggedPEB();
			adbg_NtGlobalFlagPEB();
			adbg_NtSetInformationThread();
			//adbg_DebugActiveProcess(argv[1]);

			// -------------------------------------------------------------------
			// -- CPU Checks -----------------------------------------------------
			// -------------------------------------------------------------------
			adbg_HardwareDebugRegisters();
			adbg_MovSS();

			// -------------------------------------------------------------------
			// -- Timing Checks --------------------------------------------------
			// -------------------------------------------------------------------
			adbg_RDTSC();
			adbg_QueryPerformanceCounter();
			adbg_GetTickCount();

			// -------------------------------------------------------------------
			// -- Exception Checks -----------------------------------------------
			// -------------------------------------------------------------------
			adbg_CloseHandleException();
			adbg_SingleStepException();
			adbg_Int3();
			adbg_Int2D();
			adbg_PrefixHop();

			std::this_thread::sleep_for(2s);
		}

		VMProtectEnd();

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

		char request[512];
		std::string response;

		CURL* curl;
		CURLcode res;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();

		if (curl) {

			sprintf(request, VMProtectDecryptStringA("hash=%s"), strHash);

			curl_easy_setopt(curl, CURLOPT_URL, VMProtectDecryptStringA("http://localhost/loader/checksum.php"));
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, VMProtectDecryptStringA(request));

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			res = curl_easy_perform(curl);

			if (res != CURLE_OK)
				fprintf(stderr, VMProtectDecryptStringA("curl_easy_perform() failed: %s\n"),
					curl_easy_strerror(res));

			curl_easy_cleanup(curl);

		}
		curl_global_cleanup();

		json j = json::parse(response);

		std::cout << j << std::endl;

		if (j[VMProtectDecryptStringA("success")] == false) {
			MessageBox(NULL, VMProtectDecryptStringA("Outdated Version, Please download the newest version on the website!"), VMProtectDecryptStringA("checksum error"), MB_OK);
			exit(0);
		}

		VMProtectEnd();

	}

}