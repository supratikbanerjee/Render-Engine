#include "stats_ui.h"
#include <iostream>

StatsUI::StatsUI(Metrics *metrics)
{
	this->metrics = metrics;
	printf("Stats UI\n");
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}

void StatsUI::DrawStatsUI(bool* p_open)
{
	ImGui::Begin("Stats", p_open, window_flags);
	ImGui::SetNextWindowPos(ImVec2(0, 10), ImGuiCond_FirstUseEver);
	ImGui::Text("Graphics:  %.1f FPS (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time: %.3f s", *metrics->deltaTime);
	ImGui::Text("Draw Calls: %d   SetPass Calls: %d", *metrics->drawCalls, *metrics->setPassCalls);
	ImGui::Text("Tris: %d   Verts: %d", *metrics->tris, *metrics->verts);
	ImGui::Text("VS count: %d   FS Count: %d", *metrics->vsOut, *metrics->fragOut);
	ImGui::End();
}