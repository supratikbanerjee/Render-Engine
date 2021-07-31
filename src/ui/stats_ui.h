#pragma once
#include "..\imgui\imgui.h"
#include "../application/metrics.h"

class StatsUI
{
public:
	StatsUI(Metrics*);
	void DrawUI();
private:
	//ImGuiWindowFlags window_flags = 0;
	Metrics* metrics;
};
