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
	Renderer(Metrics*, Model*, SceneManager*);
	void Render(Shader*, Camera*);
private:
	Metrics* metrics;
	Shader *shader;
	SceneManager *scene;
	Skybox sky;
	Model *models;
	Model *object;
	glm::mat4* model;
	GLuint query1;
	GLuint query2;
	
	int active_mesh_id;


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