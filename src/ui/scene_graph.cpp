#include "scene_graph.h"
#include <iostream>


SceneGraph::SceneGraph()
{
	printf("Scene Graph\n");
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
}

void SceneGraph::DrawSceneGraphUI(SceneManager* scene, bool* p_open)
{
	ImGui::Begin("Scene Graph", p_open, ImVec2(0, 0), window_flags);
	ImGui::SetWindowSize(ImVec2(335, 335), ImGuiCond_FirstUseEver);
	int id = 0;
	if (ImGui::TreeNode("Root"))
	{
		for (int i = 0; i < *scene->getMeshCount(); i++)
		{

			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected : 0);

			bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Child Node %d", i);
			if (ImGui::IsItemClicked())
			{
				node_clicked = i;
				scene->setActiveMeshId(&i);
			}
			if (node_open)
			{
				ImGui::Text("No Submesh!");
				ImGui::TreePop();
			}
			if (node_clicked != -1)
			{
				selection_mask = (1 << node_clicked);
			}

		}
	}
	ImGui::End();
}