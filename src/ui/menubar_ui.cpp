#include "menubar_ui.h"
#include "../imgui//imgui_internal.h"
MenuBarUI::MenuBarUI(RenderParams* param)
{
	this->param = param;
}

void MenuBarUI::DrawUI()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Shading"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows, 
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
			ImGui::Checkbox("Shaded", &param->shaded);
			if (param->shaded)
				param->wireframe = false;

			ImGui::Checkbox("Wireframe", &param->wireframe);
			if (param->wireframe)
				param->shaded = false;

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Environment"))
		{
			//ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
			//ImGui::MenuItem("Skybox", NULL, &param->skybox);
			//ImGui::PopItemFlag();
			ImGui::Checkbox("Skybox", &param->skybox);
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}


}