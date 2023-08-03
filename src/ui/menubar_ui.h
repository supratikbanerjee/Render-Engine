#pragma once
#include "../imgui/imgui.h"
#include "../RenderEngine.h"

class MenuBarUI
{
public:
	MenuBarUI(RenderParams*);

	void DrawUI();
private:
	RenderParams* param;
};