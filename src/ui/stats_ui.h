#pragma once
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include "../application/metrics.h"

class StatsUI
{
public:
	StatsUI(Metrics*);
	void DrawStatsUI(bool*);
private:
	ImGuiWindowFlags window_flags = 0;
	Metrics* metrics;
};
