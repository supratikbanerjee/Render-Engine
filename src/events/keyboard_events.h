#ifndef KEYBOARD_EVENTS_H
#define KEYBAORD_EVENTS_H

#include <GLFW/glfw3.h>

#include "../application/camera.h"
#include "system_events.h"
#include "../ui/ui_manager.h"



class KeyboardEvents
{
public:
	KeyboardEvents();
	void processInput(GLFWwindow*, Camera*, float*, SystemEvents*, UIManager*);
private:
	bool fpc = false;
	glm::vec3 fpCamPos;
};
#endif

