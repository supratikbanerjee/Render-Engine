#define GLM_ENABLE_EXPERIMENTAL

#include "scene_manager.h"

SceneManager::SceneManager(Model* models)
{
	printf("Scene Manager\n");
	this->models = models;
}

void SceneManager::setActiveMeshId(int* id)
{
	active_mesh_id = *id;
}

int* SceneManager::getActiveMeshId()
{
	return &active_mesh_id;
}

int* SceneManager::getMeshCount()
{
	return models->getChildCount();
}

Mesh* SceneManager::getActiveMesh()
{
	return models->getChild(&active_mesh_id)->getMesh();
}

glm::vec3 SceneManager::getLighPosition()
{
	return lightPos;
}
