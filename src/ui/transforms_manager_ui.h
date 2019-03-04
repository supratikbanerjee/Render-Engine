#ifndef TRANSFORMS_MANAGER_UI_H
#define TRANSFORMS_MANAGER_UI_H
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include <glm/glm.hpp>

static float angleX;
static float angleY;
static float angleZ;

static float translateX;
static float translateY;
static float translateZ;
static float translation_scaling_factor;
static int rotation_mode;

static float rotateAngel;

static bool AutoRotate = false;
static glm::vec3 rotate;

class TransformsManagerUI
{
public:

	TransformsManagerUI();
	void DrawTransformsManagerUI(bool*);

	void getTranslateX(float*);
	void getTranslateY(float*);
	void getTranslateZ(float*);

	void getRotateX(float*);
	void getRotateY(float*);
	void getRotateZ(float*);

	void getQuatRotate(float*, glm::vec3*);

	void getAutoRotate(bool*);

	void getTranslationScalingFactor(float*);


private:
	ImGuiWindowFlags window_flags = 0;
	
};
#endif