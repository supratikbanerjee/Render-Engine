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
	ImGui_ImplGlfwGL3_NewFrame();

	TransformsManager->DrawTransformsManagerUI(&p_open);
	ShaderManager->DrawShaderManagerUI(&p_open);
	graph->DrawSceneGraphUI(&p_open);
	stats->DrawStatsUI(&p_open);

	//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
	//ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}