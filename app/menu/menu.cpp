#include <Lmcons.h>
#include <time.h>
#include "menu.h"
#include "imgui/imgui_internal.h"
#include "settings.h"

void menu::render_buttons()
{
	
}

void menu::render_menu()
{

	VMProtectBeginUltra(menu_gui);

	// Style
	auto& style = GetStyle();

	// Menu
	SetNextWindowPos(ImVec2(0, 0));
	SetNextWindowSize(ImVec2(600 - 16, 400 - 39));
	static const auto dwFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	Begin(VMProtectDecryptStringA("Login"), 0, dwFlags);
	{

		ImGui::PushFont(font_menu);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));

		menu_helpers::apply_padding(menu_helpers::padding);
		ImGui::BeginChild(VMProtectDecryptStringA("Main"), ImVec2(574, 394 - 39 - 4));
		{

			ImGui::Separator();

			ImGui::InputText(VMProtectDecryptStringA("Username"), settings::userBuffer, IM_ARRAYSIZE(settings::userBuffer));
			ImGui::InputText(VMProtectDecryptStringA("Password"), settings::passBuffer, IM_ARRAYSIZE(settings::passBuffer), ImGuiInputTextFlags_Password);
			if (ImGui::Button(VMProtectDecryptStringA("Login"))) {
				settings::login_pressed = true;
			}
			ImGui::SameLine();
			if (ImGui::Button(VMProtectDecryptStringA("Exit")))
				settings::exit_pressed = true;

		}
		ImGui::EndChild();

		ImGui::PopFont();
		ImGui::PopStyleColor();
	}
	End();

	VMProtectEnd();

	return;

}