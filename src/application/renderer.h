#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include "../utils/shader_manager.h"
#include "../global_variables.h"
#include "skybox.h"
#include "camera.h"
#include "scene_manager.h"
#include "mesh_manager.h"
#include "../utils/gizmo.h"
#include "../ui/shader_manager_ui.h"

class Renderer
{
public:

	Renderer();
	void Render(Shader* shader, Shader skybox_shader, Camera& camera, vfGizmo3DClass& getGizmo);
private:

	ShaderManagerUI ShaderManager;
	SceneManager scene;
	Models models;
	Skybox sky;
	vector<Mesh> meshes;
	vector<glm::mat4> global;
	glm::mat4 model = glm::mat4(1.0);
	int ModelCount;
	int temp_active_var = 0;
	int display_w = 1920;
	int display_h = 1080;

	float diffuseAdd = 0.0;
	float specularAdd = 0.0;
	float smoothness = 0.0;
	float occlusion = 0.0;
	float spec_def_mult = 0.0;

	float ref_ref = 0.0;
	float IOR = 1.5;
	bool fresn = false;

	bool normalMapping = true;

	float mipmap_level = 1.0;
	bool mipmap_auto = true;

	glm::vec3 diffuse_colorTone = glm::vec3(1.0f);

	void ShaderParameters(Shader* shader);
};
#endif

