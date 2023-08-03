#pragma once
#include "../application/framebuffer.h"
#include "../imgui/imgui.h"
#include "gizmo_ui.h"

class ViewportUI
{
public:
	ViewportUI(Framebuffer*, GizmoUI*);
	void DrawUI();
private:
	Framebuffer* buffer;
	GizmoUI* gizmo;
	glm::ivec2* screenSize;
	glm::vec2 viewportBounds[2];
};