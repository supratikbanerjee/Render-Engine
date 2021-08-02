#pragma once
#include "../application/framebuffer.h"
#include "../imgui/imgui.h"

class ViewportUI
{
public:
	ViewportUI(Framebuffer*);
	void DrawUI();
private:
	Framebuffer* buffer;
	glm::ivec2* screenSize;
};