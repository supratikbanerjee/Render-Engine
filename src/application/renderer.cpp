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

void Renderer::Render(Shader* shader, Shader skybox_shader, Camera &camera, vfGizmo3DClass& getGizmo)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)display_w / (float)display_h, 0.1f, 100.0f);
	scene.manageScene(temp_active_var, models, camera);
	for (unsigned int i = 0; i < ModelCount; i++)
	{
		//printf("%f %f %f\n", camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);
		shader->use();
		shader->setVec3("viewPos", camera.GetCameraPosition());
		shader->setVec3("objColor", glm::vec3(0.95, 0.45, 0.25));
		shader->setVec3("lightPos", scene.getLighPosition());
		ShaderParameters(shader);
		models.getGlobalModels(i, &model);
		//getGizmo.applyTransform(model);
		shader->setMat4("model", model);
		shader->setMat4("MVP", projection*view*model);
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

void Renderer::ShaderParameters(Shader* shader)
{
	ShaderManager.getDiffuseAdd(&diffuseAdd);
	ShaderManager.getSpecularAdd(&specularAdd);
	ShaderManager.getSmoothness(&smoothness);
	ShaderManager.getOcclusion(&occlusion);
	ShaderManager.getSpecDefMult(&spec_def_mult);
	ShaderManager.getDiffuseColorTone(&diffuse_colorTone);

	shader->setFloat("smoothness", smoothness);
	shader->setFloat("occlusion", occlusion);
	shader->setFloat("specularAdd", specularAdd);
	shader->setFloat("diffuseAdd", diffuseAdd);
	shader->setFloat("spec_def_mult", spec_def_mult);
	shader->setVec3("diffuse_colorTone", diffuse_colorTone);

	ShaderManager.getIOR(&IOR);
	ShaderManager.getRefRef(&ref_ref);
	ShaderManager.getFresnel(&fresn);

	shader->setFloat("IOR", IOR);
	shader->setFloat("ref", ref_ref);
	shader->setBool("fresn", fresn);

	ShaderManager.getNormalMapping(&normalMapping);
	shader->setBool("normalMapping", normalMapping);

	ShaderManager.getMipMappingAuto(&mipmap_auto);
	ShaderManager.getMipMappingLevel(&mipmap_level);

	shader->setFloat("mipmap_level", mipmap_level);
	shader->setBool("mipmap_auto", mipmap_auto);


}
