#ifndef SHADER_MANAGER_UI
#define SHADER_MANAGER_UI
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include <glm/glm.hpp>

static float diffuseAdd;
static float specularAdd;
static float smoothness;
static float occlusion;
static float spec_def_mult;
static float ref_ref = 0.0;
static float IOR = 1.5;
static float mipmap_level = 0.0;
static bool mipmap_auto = true;
static bool fresn = false;
static bool normalMapping = true;
static glm::vec3 diffuse_colorTone;



class ShaderManagerUI
{
public:
	ShaderManagerUI();

	void DrawShaderManagerUI(bool*);
	void getDiffuseAdd(float*);
	void getSpecularAdd(float*);
	void getSmoothness(float*);
	void getOcclusion(float*);
	void getSpecDefMult(float*);

	void getRefRef(float*);
	void getIOR(float*);
	void getFresnel(bool*);

	void getNormalMapping(bool*);

	void getMipMappingLevel(float*);
	void getMipMappingAuto(bool*);


	void getDiffuseColorTone(glm::vec3*);


private:
	ImGuiWindowFlags window_flags = 0;
};
#endif

