#include "settings.h"

namespace settings
{

	char userBuffer[255];
	char passBuffer[255];

	std::string username_saved = "";
	std::string password_saved = "";

	bool login_pressed = false;
	bool exit_pressed = false;

	bool login_passed = false;

}