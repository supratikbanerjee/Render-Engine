#include <glm/gtc/matrix_transform.hpp>

#include "scene_manager.h"

SceneManager::SceneManager()
{
	models = Models();
	models.LoadModel();
}

void SceneManager::manageScene()
{
	rotatez += 0.1f;
	for (int i = 0; i < models.getModelCount(); i++)
	{
		models.setGlobalModels(i, models.getLocalModels(i));
	}

	models.setLocalModels(0, glm::mat4(1.0f));
	models.setLocalModels(0, glm::translate(models.getLocalModels(0), glm::vec3(0.0f, 0.0f, 0.0f)));
	models.setLocalModels(0, glm::rotate(models.getLocalModels(0), glm::radians(5 * rotatez), glm::vec3(0.0f, 1.0f, 0.0f)));

	models.setLocalModels(1, glm::mat4(1.0f));
	models.setLocalModels(1, glm::scale(models.getLocalModels(1), glm::vec3(0.01f, 0.01f, 0.01f)));
	models.setLocalModels(1, glm::translate(models.getLocalModels(1), glm::vec3(0.0f, 0.0f, 0.0f)));

	models.setGlobalModels(0, models.getLocalModels(0));
	models.setGlobalModels(1, models.getLocalModels(1));
}

glm::vec3 SceneManager::getLighPosition()
{
	return lightPos;
}

Models SceneManager::getSceneModelsObject()
{
	return models;
}
