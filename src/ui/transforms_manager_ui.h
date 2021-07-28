#ifndef TRANSFORMS_MANAGER_UI_H
#define TRANSFORMS_MANAGER_UI_H
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include "../application/transforms.h"
#include <glm/glm.hpp>




class TransformsManagerUI
{
public:

	TransformsManagerUI(Transforms*);
	void DrawTransformsManagerUI(bool*);

private:
	Transforms* transform;
	bool auto_rotate_x = false;
	bool auto_rotate_y = false;
	bool auto_rotate_z = false;
	float auto_rotate_speed = 1.0f;
	ImGuiWindowFlags window_flags = 0;
};
#endif