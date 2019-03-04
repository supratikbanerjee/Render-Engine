#include "transforms_manager_ui.h"
#include <iostream>


TransformsManagerUI::TransformsManagerUI()
{
	printf("TTT\n");
	translation_scaling_factor = 0.1;
	angleX = 0.0f;
	angleY = 0.0f;
	angleZ = 0.0f;

	translateX = 0.0f;
	translateY = 0.0f;
	translateZ = 0.0f;

	rotation_mode = 0;
	rotateAngel = 0.0f;
	rotate = glm::vec3(0.0f);
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

void TransformsManagerUI::DrawTransformsManagerUI(bool* p_open)
{
	//ImGui::SetWindowSize(ImVec2(400, 400));
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Transforms", p_open, window_flags);
	ImGui::Text("Transforms\n");
	ImGui::Text("\n");
	ImGui::Text("Translation\n");
	ImGui::Text("\n");
	ImGui::Text("Translation Scaling Factor");
	ImGui::SliderFloat(" ", &translation_scaling_factor, 0.0, 1.0f);
	ImGui::Text("\n");
	ImGui::SliderFloat(" Translate X", &translateX, -100.0f, 100.0f);
	ImGui::SliderFloat(" Translate Y", &translateY, -100.0f, 100.0f);
	ImGui::SliderFloat(" Translate Z", &translateZ, -100.0f, 100.0f);
	ImGui::Text("\n");
	ImGui::InputFloat(" T-X", &translateX);
	ImGui::InputFloat(" T-Y", &translateY);
	ImGui::InputFloat(" T-Z", &translateZ);
	ImGui::Text("\n");
	ImGui::Text("Rotation\n");
	ImGui::Text("\n");
	ImGui::RadioButton("Euler-Angle", &rotation_mode, 0); ImGui::SameLine();
	ImGui::RadioButton(" Quaternion", &rotation_mode, 1);
	ImGui::Text("\n");
	ImGui::SliderAngle(" Rotate X", &angleX);
	if (ImGui::IsItemActive())
	{
		rotateAngel = angleX;
		rotate = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	ImGui::SliderAngle(" Rotate Y", &angleY);
	if (ImGui::IsItemActive())
	{
		rotateAngel = angleY;
		rotate = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	ImGui::SliderAngle(" Rotate Z", &angleZ);
	if (ImGui::IsItemActive())
	{
		rotateAngel = angleZ;
		rotate = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	ImGui::Text("\n");
	ImGui::InputFloat(" R-X", &angleX);
	ImGui::InputFloat(" R-Y", &angleY);
	ImGui::InputFloat(" R-Z", &angleZ);
	ImGui::Text("\n");
	ImGui::Checkbox("Auto Rotate", &AutoRotate);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

}


void TransformsManagerUI::getRotateX(float* out_angle)
{
	*out_angle = angleX;
}
void TransformsManagerUI::getRotateY(float* out_angle)
{
	*out_angle = angleY;
}
void TransformsManagerUI::getRotateZ(float* out_angle)
{
	*out_angle = angleZ;
}

void TransformsManagerUI::getTranslateX(float* out_translate)
{
	*out_translate = translateX;
}
void TransformsManagerUI::getTranslateY(float* out_translate)
{
	*out_translate = translateY;
}
void TransformsManagerUI::getTranslateZ(float* out_translate)
{
	*out_translate = translateZ;
}

void TransformsManagerUI::getTranslationScalingFactor(float* scale)
{
	*scale = translation_scaling_factor;
}

void TransformsManagerUI::getQuatRotate(float* angle, glm::vec3* direction)
{
	*angle = rotateAngel;
	*direction = rotate;
}

void TransformsManagerUI::getAutoRotate(bool* out_AutoRotate)
{
	*out_AutoRotate = AutoRotate;
}
