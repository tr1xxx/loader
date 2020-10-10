#include "../menu.h"

void menu::inject_tab() {

	VMProtectBeginUltra("inject_menu");

	// Style
	auto& style = GetStyle();

	// Menu
	SetNextWindowPos(ImVec2(0, 0));
	SetNextWindowSize(ImVec2(600 - 16, 400 - 39));
	static const auto dwFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	Begin(VMProtectDecryptStringA("Inject"), 0, dwFlags);
	{
		ImGui::PushFont(font_menu);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));

		menu_helpers::apply_padding(menu_helpers::padding);
		ImGui::BeginChild(VMProtectDecryptStringA("Child"), ImVec2(574, 394 - 39 - 4));
		{


				
		}
		ImGui::EndChild();

		ImGui::PopFont();
		ImGui::PopStyleColor();
	}
	End();

	VMProtectEnd();

	return;

}