#include <glm/glm.hpp>
#include "renderer.h"


Renderer::Renderer(Metrics *metrics, Model *models, SceneManager* scene, Framebuffer* buffer)
{
	printf("Renderer\n");
	//printf("Renderer %d", transform);
	this->models = models;
	this->scene = scene;
	this->metrics = metrics;
	this->buffer = buffer;
}

void Renderer::Render(Skybox *skybox)
{
	buffer->Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glm::mat4 view = *scene->GetMainCamera()->GetViewMatrix();
	glm::mat4 projection = *scene->GetMainCamera()->GetProjectionMatrix();
	RenderQueryBegin();
	//Draw stuff
		
	// TODO
	// CHANGE RENDER MESH TO RENDER MODEL
	// CHANGE TO CALL RENDER MESH RECURSIVELY

	UpdateTransform(models);
	for (int i = 0; i < *models->getChildCount(); i++)
	{
		object = models->getChild(&i);
		UpdateTransform(object);

		shader = object->getShader();
		shader->use();
		setPassCalls++;

		shader->setVec3("viewPos", *scene->GetMainCamera()->GetCameraPosition());
		shader->setVec4("lightVector", scene->getLighPosition());
		
		model = &object->getTransform()->model;
		shader->setMat4("model", *model);
		shader->setMat4("MVP", projection*view* *model);

		object->Draw();
		drawcalls++;
	}

	RenderQUeryEnd();
	WriteRenderingMetrics();
	skybox->Draw(&view, &projection);
	buffer->Unbind();
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

	drawcalls = 0;
	setPassCalls = 0;
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
