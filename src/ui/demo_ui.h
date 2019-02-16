#ifndef DEMO_UI_H
#define DEMO_UI_H
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

class DemoUI
{
public:
	DemoUI();
	void DrawUI();
private:
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
#endif

