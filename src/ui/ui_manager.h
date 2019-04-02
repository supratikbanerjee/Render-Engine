#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "transforms_manager_ui.h"
#include "shader_manager_ui.h"
#include "scene_graph.h"
#include "../application/transforms.h"
#include "../application/scene_manager.h"

class UIManager
{
public:
	UIManager(SceneManager*, Transforms*);
	void DrawUI();
	bool p_open = false;
private:
	Transforms *transform;
	SceneManager *scene;
	TransformsManagerUI TransformsManager;
	ShaderManagerUI ShaderManager;
	SceneGraph graph;
};
#endif

