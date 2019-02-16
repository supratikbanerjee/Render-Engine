#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include "../utils/shader_manager.h"
#include "../global_variables.h"
#include "skybox.h"
#include "camera.h"
#include "scene_manager.h"
#include "mesh_manager.h"

class Renderer
{
public:
	SceneManager scene;
	Models models;
	Skybox sky;
	vector<Mesh> meshes;
	vector<glm::mat4> global;
	glm::mat4 model = glm::mat4(1.0);
	int ModelCount;


	Renderer();
	void Render(Shader shader, Shader skybox_shader, Camera &camera);
private:
	int display_w = 1920;
	int display_h = 1080;
};
#endif

