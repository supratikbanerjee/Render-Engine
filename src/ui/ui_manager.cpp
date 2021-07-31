#include "ui_manager.h"
#include <iostream>


UIManager::UIManager(SceneManager *scene , Metrics *metrics)
{
	printf("UI Manager\n");
	TransformsManager = new TransformsManagerUI(scene);
	ShaderManager = new ShaderManagerUI(scene);
	graph = new SceneGraph(scene);
	stats = new StatsUI(metrics);
	//printf("UIManager %d", transform);
}

void UIManager::DrawUI()
{
	
	TransformsManager->DrawUI();
	ShaderManager->DrawUI();
	graph->DrawUI();
	stats->DrawUI();

	//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
	//ImGui::ShowDemoWindow();

}