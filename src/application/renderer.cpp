#include <glm/glm.hpp>
#include "renderer.h"



Renderer::Renderer()
{
	printf("rrr\n");
	//scene.getSceneModelsObject(models);
	models.LoadModel();
	ModelCount = models.getModelCount();
	models.getMesh(&meshes);
}

void Renderer::Render(Shader shader, Shader skybox_shader, Camera &camera)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)display_w / (float)display_h, 0.1f, 100.0f);
	scene.manageScene(models);
	for (unsigned int i = 0; i < ModelCount; i++)
	{
		shader.use();
		shader.setVec3("viewPos", camera.GetCameraPosition());
		shader.setVec3("objColor", glm::vec3(0.95, 0.45, 0.25));
		shader.setVec3("lightPos", scene.getLighPosition());
		model = models.getGlobalModels(i);
		shader.setMat4("model", model);
		shader.setMat4("MVP", projection*view*model);
		meshes[i].Draw(shader);
	}

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	skybox_shader.use();
	view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	skybox_shader.setMat4("view", view);
	skybox_shader.setMat4("projection", projection);

	// skybox cube
	glBindVertexArray(sky.getSkyboxVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky.getCubemapTexture());
	//glBindTexture(GL_TEXTURE_2D, sky.getCubemapTexture());

	skybox_shader.setInt("skybox", 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS); // set depth function back to default
}
