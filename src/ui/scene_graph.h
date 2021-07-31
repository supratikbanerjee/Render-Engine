#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H
#include "..\imgui\imgui.h"
#include <glm/glm.hpp>
#include "../application/scene_manager.h"


class SceneGraph
{
public:

	SceneGraph(SceneManager*);
	void DrawUI();

private:
	int node_clicked = -1;
	int selection_mask = (1 << 2);
	SceneManager* scene;
	//ImGuiWindowFlags window_flags = 0;
};
#endif