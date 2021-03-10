#pragma once
#include "../app.h"

namespace app {

	class Checksum_WebRequest {

	public:
		Checksum_WebRequest(std::string hash);
		~Checksum_WebRequest() { std::cout << "Destroyed" << std::endl; }

		auto check_hash()-> void;

	private:
		std::string hash;

	};

	class Login_WebRequest {

	public:
		Login_WebRequest(char username[], char password[], std::string hwid);
		~Login_WebRequest() { std::cout << "Destroyed" << std::endl; }

		auto login()-> void;

	private:
		std::string username;
		std::string password;
		std::string hwid;

	};

}