#ifndef TRANSFORMS_MANAGER_UI_H
#define TRANSFORMS_MANAGER_UI_H
#include <imgui.h>
#include "../application/scene_manager.h"
#include <glm/glm.hpp>




class TransformsManagerUI
{
public:

	TransformsManagerUI(SceneManager*);
	void DrawUI();

private:
	Entity* model;
	SceneManager* scene;
	bool auto_rotate_x = false;
	bool auto_rotate_y = false;
	bool auto_rotate_z = false;
	float auto_rotate_speed = 1.0f;
	//ImGuiWindowFlags window_flags = 0;
};
#endif