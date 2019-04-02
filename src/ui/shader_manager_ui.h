#ifndef SHADER_MANAGER_UI
#define SHADER_MANAGER_UI
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw_gl3.h"
#include <glm/glm.hpp>
#include "../application/scene_manager.h"

class ShaderManagerUI
{
public:
	ShaderManagerUI();

	void DrawShaderManagerUI(SceneManager*, bool*);

private:
	Mesh *mesh;
	ImGuiWindowFlags window_flags = 0;
};
#endif

