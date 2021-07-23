#include "stats_ui.h"
#include <iostream>

StatsUI::StatsUI()
{
	printf("Transform Manager\n");
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}

void StatsUI::DrawStatsUI(float* deltaTime, bool* p_open)
{
	ImGui::Begin("Stats", p_open, window_flags);
	ImGui::SetNextWindowPos(ImVec2(0, 10), ImGuiCond_FirstUseEver);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time %.3f ms/frame", *deltaTime);
	ImGui::End();
}