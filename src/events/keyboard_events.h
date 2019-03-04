#ifndef KEYBOARD_EVENTS_H
#define KEYBAORD_EVENTS_H

#include <GLFW/glfw3.h>

#include "../application/camera.h"
#include "system_events.h"



class KeyboardEvents
{
public:
	KeyboardEvents();
	void processInput(GLFWwindow *window, Camera &camera, float deltaTime, SystemEvents &sysEvent);
private:
	bool fpc = false;
	glm::vec3 fpCamPos;
};
#endif

