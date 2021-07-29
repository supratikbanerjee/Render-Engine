#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "model_loader.h"

class SceneManager
{
public:
	SceneManager(Model*);
	glm::vec3 getLighPosition();
	void setActiveModelId(int*);
	int* getActiveModelId();
	int* getModelCount();
	Model* getActiveModel();
	std::string* getModelName(int*);

private:
	Model* models;
	int active_model_id = 0;
	glm::vec3 lightPos = glm::vec3(200.0f, 100.0f, 100.0f);
};
#endif

