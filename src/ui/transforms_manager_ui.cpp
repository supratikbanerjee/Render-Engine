#include "transforms_manager_ui.h"
#include <iostream>


TransformsManagerUI::TransformsManagerUI()
{
	printf("Transform Manager\n");
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	//window_flags |= ImGuiWindowFlags_NoScrollbar;
	//window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//window_flags |= ImGuiWindowFlags_NoResize;
	//window_flags |= ImGuiWindowFlags_NoCollapse;
	//window_flags |= ImGuiWindowFlags_NoNav;

}

void TransformsManagerUI::DrawTransformsManagerUI(Transforms* transform, bool* p_open)
{
	//printf("TransformManager %d", transform);

	//ImGui::SetWindowSize(ImVec2(400, 400));
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Transforms", p_open, window_flags);

	ImGui::DragFloat3("Position", &transform->translation[0], 0.01f);
	ImGui::DragFloat3("Rotation", &transform->rotation[0], 0.01f);
	ImGui::DragFloat3("Scale", &transform->scale[0], 0.01f);
	//ImGui::RadioButton("Euler-Angle", &rotation_mode, 0);
	//ImGui::RadioButton(" Quaternion", &rotation_mode, 1);
	ImGui::Text("Auto Rotate");
	ImGui::Checkbox("X", &auto_rotate_x);
	ImGui::SameLine();
	ImGui::Checkbox("Y", &auto_rotate_y);
	ImGui::SameLine();
	ImGui::Checkbox("Z", &auto_rotate_z);
	ImGui::SliderFloat("Rotation Speed", &auto_rotate_speed, 0.0f, 5.0f);

	if (ImGui::TreeNode("Trees"))
	{
		if (ImGui::TreeNode("Basic trees"))
		{
			for (int i = 0; i < 5; i++)
				if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
				{
					ImGui::Text("blah blah");
					ImGui::SameLine();
					if (ImGui::SmallButton("button")) {};
					ImGui::TreePop();
				}
			ImGui::TreePop();
		}
	}

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	if (auto_rotate_x)
		transform->rotation.x += 0.01f * auto_rotate_speed;
	if (auto_rotate_y)
		transform->rotation.y += 0.01f * auto_rotate_speed;
	if (auto_rotate_z)
		transform->rotation.z += 0.01f * auto_rotate_speed;
}