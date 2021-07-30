#define GLM_ENABLE_EXPERIMENTAL

#include "scene_manager.h"

SceneManager::SceneManager(Model* models)
{
	printf("Scene Manager\n");
	this->models = models;
}

void SceneManager::setActiveModelId(int* id)
{
	active_model_id = *id;
}

int* SceneManager::getActiveModelId()
{
	return &active_model_id;
}

int* SceneManager::getModelCount()
{
	return models->getChildCount();
}

Model* SceneManager::getActiveModel()
{
	return models->getChild(&active_model_id);
}

glm::vec4 SceneManager::getLighPosition()
{
	return lightPos;
}

std::string* SceneManager::getModelName(int* id)
{
	return models->getChild(id)->getName();
}