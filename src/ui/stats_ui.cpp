#include "stats_ui.h"
#include <iostream>

StatsUI::StatsUI(Metrics *metrics)
{
	this->metrics = metrics;
	printf("Stats UI\n");
	/*window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;*/
}

void StatsUI::DrawUI()
{
	ImGui::Begin("Stats");
	ImGui::Text("Graphics:  %.1f FPS (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time: %.3f s", *metrics->deltaTime);
	ImGui::Text("Draw Calls: %d   SetPass Calls: %d", *metrics->drawCalls, *metrics->setPassCalls);
	ImGui::Text("Tris: %d   Verts: %d", *metrics->tris, *metrics->verts);
	ImGui::Text("VS count: %d   FS Count: %d", *metrics->vsOut, *metrics->fragOut);
	ImGui::End();
}