#include "shader_manager_ui.h"
#include <iostream>



ShaderManagerUI::ShaderManagerUI(SceneManager* scene)
{
	printf("Shader Manager UI\n");
	this->scene = scene;
	/*window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;*/
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
void ShaderManagerUI::DrawUI()
{
	mat = scene->getActiveModel()->getMaterial();
	ImGui::Begin("Shader");
	ImGui::Text("PBR Shader\n");
	ImGui::Text("\n");
	const char* items[] = { "Both", "Front", "Back" };
	ImGui::Combo("Render Face", &mat->renderFace, items, IM_ARRAYSIZE(items));
	ImGui::SliderFloat("Light Energy", &mat->light_energy, 0.0f, 10.0f);
	ImGui::Text("Shader Parameters");
	ImGui::ColorEdit3(" Base color", (float*)&mat->base_color);
	ImGui::SliderFloat(" Subsurface", &mat->subsurface, 0.0f, 1.0f);
	ImGui::DragFloat3(" Subsurface Radius", &mat->subsurface_radius[0], 0.01f);
	ImGui::ColorEdit3(" Subsurface Color", (float*)&mat->subsurface_color);
	ImGui::SliderFloat(" Metallic", &mat->metallic, 0.0f, 1.0f);
	ImGui::SliderFloat(" Specular", &mat->specular, 0.0f, 1.0f);
	ImGui::SliderFloat(" Roughness", &mat->roughness, 0.0f, 1.0f);

	ImGui::SliderFloat(" Occlusion", &mat->occlusion, 0.0f, 1.0f);
	ImGui::SliderFloat(" IOR", &mat->ior, 0.0f, 3.0f);
	ImGui::SliderFloat(" Reflection/Refraction", &mat->reflection_refratoin_ratio, 0.0f, 1.0f);
	ImGui::Checkbox("Frensel", &mat->fresnel);
	ImGui::SliderFloat(" Mipamap Level", &mat->mipmap_level, 0.0f, 5.0f);
	ImGui::Checkbox("Dipole", &mat->dipole);
	ImGui::Checkbox("Paralax Mapping", &mat->paralax_map);
	ImGui::Checkbox("Normal Mapping", &mat->normal_mapping);
	ImGui::Checkbox("Mipamap Auto", &mat->mipmap_auto);
	ImGui::Checkbox("Z-Buffer", &mat->z_buffer);
	ImGui::Checkbox("Roughness Map", &mat->rough_tex);
	ImGui::Checkbox("Metallic Map", &mat->metallic_tex);
	ImGui::End();
}
