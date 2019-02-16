#include "keyboard_events.h"



KeyboardEvents::KeyboardEvents()
{
}


void KeyboardEvents::processInput(GLFWwindow *window, Camera &camera, float deltaTime, SystemEvents &sysEvents)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(camera.RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		sysEvents.setProcessMouseMovementStatus(true);
	}
	else if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		sysEvents.setProcessMouseMovementStatus(false);
	}

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		sysEvents.setRenderEngineUIStatus(false);
	else if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		sysEvents.setRenderEngineUIStatus(true);
}