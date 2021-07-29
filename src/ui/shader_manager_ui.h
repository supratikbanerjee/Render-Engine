#ifndef SHADER_MANAGER_UI
#define SHADER_MANAGER_UI
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include <glm/glm.hpp>
#include "../application/scene_manager.h"

class ShaderManagerUI
{
public:
	ShaderManagerUI(SceneManager*);

	void DrawShaderManagerUI(bool*);

private:
	int item_current = 0;
	Material *mat;
	SceneManager* scene;
	ImGuiWindowFlags window_flags = 0;
};
#endif

