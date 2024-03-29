#include <glm/glm.hpp>
#include "renderer.h"


Renderer::Renderer(Metrics *metrics, Model *models, SceneManager* scene, Transforms* transform)
{
	printf("Renderer\n");
	this->transform = transform;
	//printf("Renderer %d", transform);
	this->models = models;
	this->scene = scene;
	this->metrics = metrics;
}

void Renderer::Render(Shader *skybox_shader, Camera *camera)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)display_w / (float)display_h, 0.1f, 100.0f);

	RenderQueryBegin();
	//Draw stuff
		
	// TODO
	// CHANGE RENDER MESH TO RENDER MODEL
	// CHANGE TO CALL RENDER MESH RECURSIVELY

	UpdateTransform(models);
	for (int i = 0; i < *models->getChildCount(); i++)
	{
		//printf("%f %f %f\n", camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
		object = models->getChild(&i);
		shader = object->getShader();
		shader->use();
		setPassCalls++;
		shader->setVec3("viewPos", camera->GetCameraPosition());
		shader->setVec3("lightPos", scene->getLighPosition());
		
		model = models->getGlobalTransform();
		shader->setMat4("model", *model);
		shader->setMat4("MVP", projection*view* *model);

		mesh = object->getMesh();
		mesh->Draw(shader);
		drawcalls++;
		mesh->ShaderParameters(shader);
	}

	RenderQUeryEnd();
	WriteRenderingMetrics();

	glDepthFunc(GL_LEQUAL);
	skybox_shader->use();
	view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
	skybox_shader->setMat4("view", view);
	skybox_shader->setMat4("projection", projection);

	// skybox cube
	glBindVertexArray(sky.getSkyboxVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky.getCubemapTexture());
	//glBindTexture(GL_TEXTURE_2D, sky.getCubemapTexture());

	skybox_shader->setInt("skybox", 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
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
	glm::mat4 global = *model->getGlobalTransform();
	global = glm::scale(glm::mat4(1.0f), transform->scale);
	global = glm::translate(global, transform->translation);
	global = glm::rotate(global, transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	global = glm::rotate(global, transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	global = glm::rotate(global, transform->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model->setGlobalTransform(&global);
}
