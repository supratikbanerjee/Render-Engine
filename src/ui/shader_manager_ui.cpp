#include "shader_manager_ui.h"



ShaderManagerUI::ShaderManagerUI()
{
	diffuseAdd = 1.0f;
	specularAdd = 1.0f;
	smoothness = 1.0f;
	occlusion = 0.0f;
	spec_def_mult = 10.0f;
	diffuse_colorTone = glm::vec3(1.0f);
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

void ShaderManagerUI::DrawShaderManagerUI(bool* p_open)
{
	ImGui::SetNextWindowPos(ImVec2(1540, 0), ImGuiCond_FirstUseEver);
	ImGui::Begin("Shader", p_open, window_flags);
	ImGui::Text("PBR Shader\n");
	ImGui::Text("\n");
	ImGui::Text("Shader Parameters");
	ImGui::ColorEdit3("Diffuse color", (float*)&diffuse_colorTone); // Edit 3 floats representing a color
	ImGui::Checkbox("Normal Mapping", &normalMapping);
	ImGui::SliderFloat(" Intensity Multiplier", &spec_def_mult, 0.0f, 100.0f);
	ImGui::SliderFloat(" Diffuse", &diffuseAdd, 0.0f, 2.0f);
	ImGui::SliderFloat(" Specular", &specularAdd, 0.0f, 2.0f);
	ImGui::SliderFloat(" Smoothness", &smoothness, 0.0f, 2.0f);
	ImGui::SliderFloat(" Occlusion", &occlusion, 0.0f, 2.0f);
	ImGui::SliderFloat(" IOR", &IOR, 0.0f, 3.0f);
	ImGui::SliderFloat(" Reflection/Refraction", &ref_ref, 0.0f, 1.0f);
	ImGui::Checkbox("Frensel", &fresn);
	ImGui::SliderFloat(" Mipamap Level", &mipmap_level, 0.0f, 5.0f);
	ImGui::Checkbox("Mipamap Auto", &mipmap_auto);


	ImGui::End();
}

void ShaderManagerUI::getDiffuseAdd(float* out_diffuseAdd)
{
	*out_diffuseAdd = diffuseAdd;
}
void ShaderManagerUI::getSpecularAdd(float* out_specularAdd)
{
	*out_specularAdd = specularAdd;
}
void ShaderManagerUI::getSmoothness(float* out_smoothness)
{
	*out_smoothness = smoothness;
}
void ShaderManagerUI::getOcclusion(float* out_occlusion)
{
	*out_occlusion = occlusion;
}
void ShaderManagerUI::getSpecDefMult(float* out_spec_def_mult)
{
	*out_spec_def_mult = spec_def_mult;
}

void ShaderManagerUI::getRefRef(float* out_ref_ref)
{
	*out_ref_ref = ref_ref;
}
void ShaderManagerUI::getIOR(float* out_IOR)
{
	*out_IOR = IOR;
}

void ShaderManagerUI::getFresnel(bool* out_fresn)
{
	*out_fresn = fresn;
}

void ShaderManagerUI::getNormalMapping(bool* out_normalMapping)
{
	*out_normalMapping = normalMapping;
}

void ShaderManagerUI::getDiffuseColorTone(glm::vec3* out_diffuse_colorTone)
{
	*out_diffuse_colorTone = diffuse_colorTone;
}

void ShaderManagerUI::getMipMappingLevel(float* ou_mipmap_level)
{
	*ou_mipmap_level = mipmap_level;
}
void ShaderManagerUI::getMipMappingAuto(bool* out_mipmap_auto)
{
	*out_mipmap_auto = mipmap_auto;
}