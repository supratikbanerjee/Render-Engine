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
	ImGui::Text("Graphics:  %.1f FPS (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time: %.3f s", *deltaTime);
	ImGui::Text("Tris: %d   Verts: %d", 1,2);
	ImGui::End();
}