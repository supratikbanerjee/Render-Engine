#ifndef RENDERER_H
#define RENDERER_H
#include <windows.h>
#include <glad/glad.h>
#include "../utils/shader_manager.h"
//#include "../global_variables.h"
#include "model_loader.h"
#include "skybox.h"
#include "camera.h"
#include "scene_manager.h"
#include "mesh_manager.h"
#include "../utils/gizmo.h"
#include "transforms.h"
#include "metrics.h"

class Renderer
{
public:
	Renderer(Metrics*, Model*, SceneManager*, Transforms*);
	void Render(Shader *skybox_shader, Camera *camera);
private:
	Metrics* metrics;
	Shader *shader;
	Transforms *transform;
	SceneManager *scene;
	Skybox sky;
	Model *models;
	Model *object;
	Mesh *mesh;
	glm::mat4 *model;
	GLuint query1;
	GLuint query2;
	
	int active_mesh_id;
	int display_w = 1920;
	int display_h = 1080;

	void UpdateTransform(Model*);
	void WriteRenderingMetrics();
	void RenderQueryBegin();
	void RenderQUeryEnd();

	unsigned int frag;
	unsigned int vert;

	int setPassCalls = 0;
	int drawcalls = 0;
};
#endif