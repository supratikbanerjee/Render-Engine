#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "utils/stb_image.h"
#include "application/camera.h"

//#include "global_variables.h"
#include "application/renderer.h"
#include "events/keyboard_events.h"
#include "events/system_events.h"
//#include "events/mouse_events.h"
#include "ui/ui_manager.h"
#include "application/scene_manager.h"
#include "application/metrics.h"
#include "application/framebuffer.h"
#include "RenderEngine.h"
/*

TODO

NEED TO CREATE A CLASS FOR COMMON OBJECT SHARING!

VERY VERY IMPORTANT

*/

#ifdef _WIN32
extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

GLFWwindow* window;

glm::ivec2 viewportSize = glm::ivec2(1920, 1080);

int width = 1920;
int height = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = width / 2.0f;
float lastY = height / 2.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
SystemEvents sysEvent = SystemEvents();

//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	if (sysEvent.getProcessMouseMovementStatus())
		camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	printf("clicked \n");
}

int WindowInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, "Xtreme Render Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Xtreme Render Engine Error" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

int main()
{
	WindowInit();
	glEnable(GL_DEPTH_TEST);

	RenderParams param;

	camera.SetViewportSize(&viewportSize);
	Framebuffer *buffer = new Framebuffer(&viewportSize);	
	
	Metrics metrics;
	ModelLoader Loader = ModelLoader(&metrics);
	Skybox sky;
	
	Model *models;
	// TODO
	// CHANGE LOADING SYSTEM TO MAKE IT MODULAR
	models = Loader.LoadModel();
	SceneManager scene = SceneManager(models, &camera);
	Renderer renderer = Renderer(&metrics, models, &scene, buffer, &param);

	KeyboardEvents keyboard = KeyboardEvents();
	UIManager ui = UIManager(&scene, &metrics, buffer, &param);

	ui.Init(window);
	while (!glfwWindowShouldClose(window))
	{
		keyboard.processInput(window, &camera, &deltaTime, &sysEvent, &ui);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		metrics.deltaTime = &deltaTime;

		renderer.Render(&sky);

		if (sysEvent.getRenderEngineUIStatus())
		{
			ui.Begin();
			ui.DrawUI();
			ui.End();
		}

		glfwSwapInterval(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ui.ShutDown();
	glfwTerminate();

	return 0;
}