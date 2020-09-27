#include "security/includes.h"

int main()
{

	VMProtectBeginUltra(main_function);

	//std::thread antidbg_thread(app::antidbg_loop);
	//std::thread random_thread(app::random_filename);
	//app::checksum_loop();
	std::thread login_thread(app::login_loop);
	std::thread menu_render_thread(app::render_menu);

	std::cin.get();

	VMProtectEnd();

	return 0;

}