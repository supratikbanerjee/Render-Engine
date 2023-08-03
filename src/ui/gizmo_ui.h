#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "..\imgui\imgui.h"
#include "../application/scene_manager.h"
#include <ImGuizmo.h>

class GizmoUI
{
public:
	GizmoUI(SceneManager*);
	void Begin();
	void DrawGizmo(glm::vec2[]);
	int gizmoType = -1;
private:
	SceneManager* scene;
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::vec3 euler;
	glm::vec3 deltaRotation;
};