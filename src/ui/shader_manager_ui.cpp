#include "shader_manager_ui.h"
#include <iostream>



ShaderManagerUI::ShaderManagerUI()
{
	printf("Shader Manager UI\n");
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

void ShaderManagerUI::DrawShaderManagerUI(SceneManager* scene, bool* p_open)
{
	mesh = scene->getActiveMesh();
	ImGui::SetNextWindowPos(ImVec2(1540, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Shader", p_open, window_flags);
	ImGui::Text("PBR Shader\n");
	ImGui::Text("\n");
	ImGui::Text("Shader Parameters");
	ImGui::ColorEdit3("Diffuse color", (float*)&mesh->diffuse_color_tone); // Edit 3 floats representing a color
	ImGui::Checkbox("Normal Mapping", &mesh->normal_mapping);
	ImGui::SliderFloat(" Intensity Multiplier", &mesh->specular_default_multiplier, 0.0f, 100.0f);
	ImGui::SliderFloat(" Diffuse", &mesh->diffuseAdd, 0.0f, 2.0f);
	ImGui::SliderFloat(" Specular", &mesh->specularAdd, 0.0f, 2.0f);
	ImGui::SliderFloat(" Smoothness", &mesh->smoothness, 0.0f, 2.0f);
	ImGui::SliderFloat(" Occlusion", &mesh->occlusion, 0.0f, 2.0f);
	ImGui::SliderFloat(" IOR", &mesh->ior, 0.0f, 3.0f);
	ImGui::SliderFloat(" Reflection/Refraction", &mesh->reflection_refratoin_ratio, 0.0f, 1.0f);
	ImGui::Checkbox("Frensel", &mesh->fresnel);
	ImGui::SliderFloat(" Mipamap Level", &mesh->mipmap_level, 0.0f, 5.0f);
	ImGui::Checkbox("Mipamap Auto", &mesh->mipmap_auto);
	ImGui::End();
}
