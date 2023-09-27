#ifndef SHADER_MANAGER_UI
#define SHADER_MANAGER_UI
#include <imgui.h>
#include <glm/glm.hpp>
#include "../application/scene_manager.h"

class ShaderManagerUI
{
public:
	ShaderManagerUI(SceneManager*);
	void DrawUI();

private:
	Material *mat;
	SceneManager* scene;
	//ImGuiWindowFlags window_flags = 0;
};
#endif

