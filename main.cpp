#include "security/includes.h"

int main()
{

	VMProtectBeginUltra(main_function);

	std::string test = VMProtectDecryptStringA("test");

	std::cout << test << std::endl;

	std::thread antidbg_thread(app::antidbg_loop);
	//app::checksum_loop();
	std::thread login_thread(app::login_loop);
	std::thread menu_render_thread(app::render_menu);

	std::cin.get();

	VMProtectEnd();

	return 0;

}