#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <GLFW\glfw3.h>
#include "transforms_manager_ui.h"
#include "shader_manager_ui.h"
#include "scene_graph.h"
#include "stats_ui.h"
#include "viewport_ui.h"

#include "..\imgui\imgui.h"
#include "..\imgui\imgui_impl_glfw.h"
#include "..\imgui\imgui_impl_opengl3.h"

#include "../application/transforms.h"
#include "../application/scene_manager.h"

class UIManager
{
public:
	UIManager(SceneManager*, Metrics*, Framebuffer*);
	void Init(GLFWwindow*);
	void Begin();
	void DrawUI();
	void End();
	void ShutDown();
private:
	void DockingFromHazel();
	TransformsManagerUI* TransformsManager;
	ShaderManagerUI* ShaderManager;
	SceneGraph* graph;
	StatsUI* stats;
	ViewportUI* viewport;
};
#endif

