#include "shader_manager_ui.h"
#include <iostream>



ShaderManagerUI::ShaderManagerUI()
{
	printf("Shader Manager UI\n");
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}
/*
	color BaseColor = color(0.8, 0.8, 0.8),
	float Subsurface = 0.0,
	vector SubsurfaceRadius = vector(1.0, 1.0, 1.0),
	color SubsurfaceColor = color(0.7, 0.1, 0.1),
	float Metallic = 0.0,
	float Specular = 0.5,
	float SpecularTint = 0.0,
	float Roughness = 0.5,
	float Anisotropic = 0.0,
	float AnisotropicRotation = 0.0,
	float Sheen = 0.0,
	float SheenTint = 0.5,
	float Clearcoat = 0.0,
	float ClearcoatRoughness = 0.03,
	float IOR = 1.45,
	float Transmission = 0.0,
	float TransmissionRoughness = 0.0,
*/
void ShaderManagerUI::DrawShaderManagerUI(SceneManager* scene, bool* p_open)
{
	mesh = scene->getActiveMesh();
	ImGui::SetNextWindowPos(ImVec2(1540, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Shader", p_open, window_flags);
	ImGui::Text("PBR Shader\n");
	ImGui::Text("\n");
	ImGui::SliderFloat("Light Energy", &mesh->light_energy, 0.0f, 10.0f);
	ImGui::Text("Shader Parameters");
	ImGui::ColorEdit3(" Base color", (float*)&mesh->base_color);
	ImGui::SliderFloat(" Subsurface", &mesh->subsurface, 0.0f, 1.0f);
	ImGui::DragFloat3(" Subsurface Radius", &mesh->subsurface_radius[0], 0.01f);
	ImGui::ColorEdit3(" Subsurface Color", (float*)&mesh->subsurface_color);
	ImGui::SliderFloat(" Metallic", &mesh->metallic, 0.0f, 1.0f);
	ImGui::SliderFloat(" Specular", &mesh->specular, 0.0f, 1.0f);
	ImGui::SliderFloat(" Roughness", &mesh->roughness, 0.0f, 1.0f);

	ImGui::SliderFloat(" Occlusion", &mesh->occlusion, 0.0f, 2.0f);
	ImGui::SliderFloat(" IOR", &mesh->ior, 0.0f, 3.0f);
	ImGui::SliderFloat(" Reflection/Refraction", &mesh->reflection_refratoin_ratio, 0.0f, 1.0f);
	ImGui::Checkbox("Frensel", &mesh->fresnel);
	ImGui::SliderFloat(" Mipamap Level", &mesh->mipmap_level, 0.0f, 5.0f);
	ImGui::Checkbox("Dipole", &mesh->dipole);
	ImGui::Checkbox("Paralax Mapping", &mesh->paralax_map);
	ImGui::Checkbox("Normal Mapping", &mesh->normal_mapping);
	ImGui::Checkbox("Mipamap Auto", &mesh->mipmap_auto);
	ImGui::Checkbox("Z-Buffer", &mesh->z_buffer);
	ImGui::End();
}
