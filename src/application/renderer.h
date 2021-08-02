#ifndef RENDERER_H
#define RENDERER_H
#include <windows.h>
#include <glad/glad.h>
#include "../utils/shader_manager.h"
#include "model_loader.h"
#include "skybox.h"
#include "camera.h"
#include "scene_manager.h"
#include "mesh_manager.h"
#include "transforms.h"
#include "metrics.h"
#include "framebuffer.h"
#include "shadows.h"
#include "../RenderEngine.h"
class Renderer
{
public:
	Renderer(Metrics*, SceneManager*, Framebuffer*, RenderParams*, ShadowMaps*);
	void Render(Skybox*);
	
private:

	enum PASS {SHADOW, GEOMETRY};
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	ShadowMaps* shadow;
	RenderParams* param;
	Framebuffer* buffer;
	Metrics* metrics;
	Shader* shader;
	Shader* shadowShader;
	SceneManager *scene;
	Skybox sky;
	//Model *models;
	Model *object;
	glm::mat4* model;
	GLuint query1;
	GLuint query2;
	
	int active_mesh_id;

	void PreRender();
	void RenderScene(PASS);
	void ShadowPass();
	void UpdateTransform(Model*);
	void WriteRenderingMetrics();
	void RenderQueryBegin();
	void RenderQUeryEnd();

	unsigned int frag;
	unsigned int vert;

	int setPassCalls = 0;
	int drawcalls = 0;

	int shadowMapRes = 1024;
};
#endif