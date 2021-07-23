#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"

class StatsUI
{
public:
	StatsUI();
	void DrawStatsUI(float*, bool*);
private:
	ImGuiWindowFlags window_flags = 0;
};
