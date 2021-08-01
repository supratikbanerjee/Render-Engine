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
#include "RenderEngine.h"
#include "application/scene_manager.h"
#include "application/metrics.h"
#include <ImGuizmo.h>
#include "application/framebuffer.h"
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

Camera camera(glm::vec3(0.0f,0.0f, 3.0f));
SystemEvents sysEvent = SystemEvents();

int viewPortWidth = 1280;
int viewPortHeight = 720;
int width = 1920;
int height = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = width / 2.0f;
float lastY = height / 2.0f;

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



void TempGizmoUI(SceneManager* scene)
{

	ImGuizmo::BeginFrame();
	ImGuizmo::SetOrthographic(false);
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::Begin("ViewPort");
	ImGuizmo::SetDrawlist();

	ImGuizmo::SetRect(0, 0, width, height);
	glm::mat4* cameraProjection = camera.GetProjectionMatrix();
	glm::mat4* cameraView = camera.GetViewMatrix();

	Model* selected = scene->getActiveModel();
	glm::mat4 transform = selected->getTransform()->model;
	ImGuizmo::Manipulate(glm::value_ptr(*cameraView), glm::value_ptr(*cameraProjection),
		ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform));

	if (ImGuizmo::IsUsing())
	{
		selected->getTransform()->translation = glm::vec3(transform[3]);
	}
	ImGui::End();
	// Camera
}

void TempViewPort(Framebuffer* buffer)
{
	ImGui::Begin("ViewPort");
	unsigned int textureID = *buffer->GetColorAttachment();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ (float)viewPortWidth, (float)viewPortHeight }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	//unsigned int* textureID = buffer->GetColorAttachment();
	//ImGui::Image(textureID, ImVec2{ (float)viewPortWidth, (float)viewPortHeight });
	ImGui::End();
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Xtreme Render Engine", NULL, NULL);
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

	glEnable(GL_DEPTH_TEST);
	Framebuffer *buffer = new Framebuffer(&width, &height);
	buffer->Init();
	
	
	//Shader shader("../Shaders/cubemap.vs", "../Shaders/cubemap.fs");
	//Shader shader;
	//shader.CompileShaders("../Shaders/PBR/PBR.vs.glsl", "../Shaders/PBR/PBR3.fs");
	Metrics metrics;
	ModelLoader Loader = ModelLoader(&metrics);
	Skybox sky;
	
	Model *models;
	// TODO
	// CHANGE LOADING SYSTEM TO MAKE IT MODULAR
	models = Loader.LoadModel();
	SceneManager scene = SceneManager(models);
	Renderer renderer = Renderer(&metrics, models, &scene, buffer);

	KeyboardEvents keyboard = KeyboardEvents();
	UIManager ui = UIManager(&scene, &metrics);

	ui.Init(window);
	while (!glfwWindowShouldClose(window))
	{
		

		keyboard.processInput(window, &camera, &deltaTime, &sysEvent);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		metrics.deltaTime = &deltaTime;

		renderer.Render(&sky, &camera);

		if (sysEvent.getRenderEngineUIStatus())
		{
			ui.Begin();
			TempViewPort(buffer);
			//TempGizmoUI(&scene);
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