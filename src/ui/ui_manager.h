#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include "transforms_manager_ui.h"
#include "shader_manager_ui.h"

class UIManager
{
public:
	UIManager();
	void DrawUI();
	bool p_open = false;
	void getTransformsObjects(TransformsManagerUI*);
private:
	TransformsManagerUI TransformsManager;
	ShaderManagerUI ShaderManager;
};
#endif

