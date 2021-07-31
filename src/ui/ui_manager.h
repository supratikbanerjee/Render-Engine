#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "transforms_manager_ui.h"
#include "shader_manager_ui.h"
#include "scene_graph.h"
#include "stats_ui.h"

#include "../application/transforms.h"
#include "../application/scene_manager.h"

class UIManager
{
public:
	UIManager(SceneManager*, Metrics*);
	void DrawUI();
	//bool p_open = false;
private:
	TransformsManagerUI* TransformsManager;
	ShaderManagerUI* ShaderManager;
	SceneGraph* graph;
	StatsUI* stats;
};
#endif

