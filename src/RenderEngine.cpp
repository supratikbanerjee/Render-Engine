#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "utils/stb_image.h"
#include "application/camera.h"
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
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

int width = 1920;
int height = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = width / 2.0f;
float lastY = height / 2.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


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

void init(GLFWwindow *window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui::StyleColorsDark();
	ImGui_ImplGlfwGL3_Init(window, true);
	// Setup Dear ImGui style
	//ImGui::StyleColorsClassic();
}

void TempGizmoUI(SceneManager* scene)
{
	ImGuizmo::BeginFrame();
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawlist();

	ImGuizmo::SetRect(0, 0, width, height);
	glm::mat4* cameraProjection = camera.GetProjectionMatrix();
	glm::mat4* cameraView = camera.GetViewMatrix();

	Model* selected = scene->getActiveModel();
	glm::mat4* transform = &selected->getTransform()->model;
	ImGuizmo::Manipulate(glm::value_ptr(*cameraView), glm::value_ptr(*cameraProjection),
		ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(*transform));
	// Camera
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

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	//Shader shader("../Shaders/cubemap.vs", "../Shaders/cubemap.fs");
	//Shader shader;
	//shader.CompileShaders("../Shaders/PBR/PBR.vs.glsl", "../Shaders/PBR/PBR3.fs");
	Metrics metrics;
	Shader skybox_shader;
	skybox_shader.CompileShaders("shaders/skybox.vs", "shaders/skybox.fs");
	init(window);
	ModelLoader Loader = ModelLoader(&metrics);
	Skybox sky;
	
	Model *models;
	// TODO
	// CHANGE LOADING SYSTEM TO MAKE IT MODULAR
	models = Loader.LoadModel();
	//Transforms transform;
	SceneManager scene = SceneManager(models);
	Renderer renderer = Renderer(&metrics, models, &scene);

	KeyboardEvents keyboard = KeyboardEvents();
	UIManager ui = UIManager(&scene, &metrics);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		keyboard.processInput(window, &camera, &deltaTime, &sysEvent);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		metrics.deltaTime = &deltaTime;

		renderer.Render(&skybox_shader, &camera);

		

		if (sysEvent.getRenderEngineUIStatus())
		{
			ImGui_ImplGlfwGL3_NewFrame();
			ui.DrawUI();
			TempGizmoUI(&scene);
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapInterval(0);
		glfwSwapBuffers(window);
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}