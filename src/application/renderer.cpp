#include <glm/glm.hpp>
#include "renderer.h"


Renderer::Renderer(Metrics *metrics, SceneManager* scene, Framebuffer* buffer, RenderParams* param, ShadowMaps* shadow)
{
	printf("Renderer\n");
	//printf("Renderer %d", transform);
	this->param = param;
	this->scene = scene;
	this->metrics = metrics;
	this->buffer = buffer;
	this->shadow = shadow;
}

void Renderer::Render(Skybox *skybox)
{
	PreRender();

	RenderQueryBegin();

	ShadowPass();

	buffer->Bind();
	
	RenderScene(GEOMETRY);
	
	if(param->skybox)
		skybox->Draw(&view, &projection);

	buffer->Unbind();

	RenderQUeryEnd();
	WriteRenderingMetrics();
}

void Renderer::PreRender()
{
	drawcalls = 0;
	setPassCalls = 0;

	if (param->wireframe && !param->shaded)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (!param->wireframe && param->shaded)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


void Renderer::RenderScene(PASS RENDERPASS)
{
	view = *scene->GetMainCamera()->GetViewMatrix();
	projection = *scene->GetMainCamera()->GetProjectionMatrix();
	for (int i = 0; i < *scene->GetModels()->getChildCount(); i++)
	{
		object = scene->GetModels()->getChild(&i);
		UpdateTransform(object);

		if(RENDERPASS == GEOMETRY)
			shader = object->getShader();
		if(RENDERPASS == SHADOW)
			shader = shadow->GetShader();
		shader->use();
		setPassCalls++;

		shader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

		model = &object->getTransform()->model;
		shader->setMat4("model", *model);

		if (RENDERPASS == GEOMETRY)
		{
			shader->setVec3("viewPos", *scene->GetMainCamera()->GetCameraPosition());
			shader->setVec4("lightVector", scene->getLighPosition());
			shader->setMat4("MVP", projection * view * *model);
		}
		object->Draw();
		drawcalls++;
	}
}

void Renderer::ShadowPass()
{

	float near_plane = 1.0f, far_plane = 7.5f;
	//lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(scene->getLighPosition()), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	shadow->Bind();
	RenderScene(SHADOW);
	shadow->Unbind();
}

void Renderer::RenderQueryBegin()
{
	glGenQueries(1, &query1);
	glBeginQuery(GL_SAMPLES_PASSED, query1);

	glGenQueries(1, &query2);
	glBeginQuery(GL_PRIMITIVES_GENERATED, query2);
}

void Renderer::RenderQUeryEnd()
{
	glEndQuery(GL_SAMPLES_PASSED);
	glGetQueryObjectuiv(query1, GL_QUERY_RESULT, &frag);

	glEndQuery(GL_PRIMITIVES_GENERATED);
	glGetQueryObjectuiv(query2, GL_QUERY_RESULT, &vert);
}

void Renderer::WriteRenderingMetrics()
{
	metrics->drawCalls = &drawcalls;
	metrics->fragOut = &frag;
	metrics->setPassCalls = &setPassCalls;
	metrics->vsOut = &vert;
}

void Renderer::UpdateTransform(Model* model)
{
	glm::mat4 global = model->getTransform()->model;
	global = glm::scale(glm::mat4(1.0f), model->getTransform()->scale);
	global = glm::translate(global, model->getTransform()->translation);
	global = glm::rotate(global, model->getTransform()->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	global = glm::rotate(global, model->getTransform()->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	global = glm::rotate(global, model->getTransform()->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model->getTransform()->model = global;
}
