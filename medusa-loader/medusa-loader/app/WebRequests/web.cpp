#include "web.h"
#include "../http/http.hpp"

using json = nlohmann::json;

namespace app {

	Checksum_WebRequest::Checksum_WebRequest(std::string hash) {

		VMProtectBeginUltra("Checksum_constructor");

		try {

			std::cout << "Created" << std::endl;

			this->hash = hash;

		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}

		VMProtectEnd();

	}

	auto Checksum_WebRequest::check_hash()-> void {

		VMProtectBeginUltra("check_hash");

		try
		{

			http::Request request(VMProtectDecryptStringA("http://localhost/loader/checksum.php"));
			// pass parameters as a map
			std::map<std::string, std::string> parameters = { {VMProtectDecryptStringA("hash"), VMProtectDecryptStringA(this->hash.c_str())} };
			http::Response response = request.send("POST", parameters, {
				"Content-Type: application/x-www-form-urlencoded"
				});

			json j = json::parse(response.body.begin(), response.body.end());

			std::cout << j << std::endl;

			if (j[VMProtectDecryptStringA("success")] == false) {
				MessageBox(NULL, VMProtectDecryptStringA("Outdated Version, Please download the newest version on the website!"), VMProtectDecryptStringA("checksum error"), MB_OK);
				exit(0);
			}

		}
		catch (const std::exception& e) {
			std::cerr << "Request failed, error: " << e.what() << '\n';
		}
		catch (const json::exception& j) {
			std::cerr << j.what() << std::endl;
		}

		VMProtectEnd();
	}

	Login_WebRequest::Login_WebRequest(char username[], char password[], std::string hwid) {

		VMProtectBeginUltra("login_constructor");

		try {

			std::cout << "Created" << std::endl;

			this->username = username;
			this->password = password;
			this->hwid = hwid;

		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}

		VMProtectEnd();

	}

	auto Login_WebRequest::login()-> void {

		VMProtectBeginUltra("login");

		try
		{

			http::Request request(VMProtectDecryptStringA("http://localhost/loader/check.php"));
			// pass parameters as a map
			std::map<std::string, std::string> parameters = { {VMProtectDecryptStringA("username"), VMProtectDecryptStringA(this->username.c_str())}, {VMProtectDecryptStringA("password"), VMProtectDecryptStringA(this->password.c_str())}, {VMProtectDecryptStringA("hwid"), VMProtectDecryptStringA(this->hwid.c_str())} };
			http::Response response = request.send("POST", parameters, {
				"Content-Type: application/x-www-form-urlencoded"
				});

			json j = json::parse(response.body.begin(), response.body.end());

			std::cout << j << std::endl;

			if (j[VMProtectDecryptStringA("success")] == true) {

				MessageBox(NULL, VMProtectDecryptStringA("successful!"), VMProtectDecryptStringA("login"), MB_OK);

				if (j[VMProtectDecryptStringA("hwid")] == true) {
					app::load_driver();
					settings::login_passed = true;
				}
				else if (j[VMProtectDecryptStringA("new_hwid")] == true) {
					MessageBox(NULL, VMProtectDecryptStringA("hwid set!"), VMProtectDecryptStringA("login"), MB_OK);
					app::load_driver();
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
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		catch (const json::exception& j) {
			std::cerr << j.what() << std::endl;
		}

		VMProtectEnd();
	}

}