#define GLM_ENABLE_EXPERIMENTAL

#include "scene_manager.h"

SceneManager::SceneManager(Entity* entities, Camera* camera)
{
	printf("Scene Manager\n");
	this->entities = entities;
	this->camera = camera;
	this->mainLight = new Light();
	mainLight->setName("Light");
	this->entities->AddChild(mainLight);
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
	return entities->getChildCount();
}

Entity* SceneManager::getActiveModel()
{
	return entities->getChild(&active_model_id);
}

glm::vec4* SceneManager::getLightVector()
{
	return mainLight->GetLightVector();
}

std::string* SceneManager::getModelName(int* id)
{
	return entities->getChild(id)->getName();
}

Camera* SceneManager::GetMainCamera()
{
	return camera;
}

Entity* SceneManager::GetModels()
{
	return entities;
}