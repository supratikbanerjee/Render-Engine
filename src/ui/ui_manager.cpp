#include "ui_manager.h"
#include <iostream>


UIManager::UIManager(SceneManager* scene, Transforms *transform)
{
	printf("UI Manager\n");
	this->transform = transform;
	this->scene = scene;
	//printf("UIManager %d", transform);
}

void UIManager::DrawUI()
{
	ImGui_ImplGlfwGL3_NewFrame();

	TransformsManager.DrawTransformsManagerUI(transform, &p_open);
	ShaderManager.DrawShaderManagerUI(scene, &p_open);
	graph.DrawSceneGraphUI(scene, &p_open);

	//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
	//ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}