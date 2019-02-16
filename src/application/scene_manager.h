#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "model_manager.h"

class SceneManager
{
public:
	glm::vec3 lightPos = glm::vec3(200.0f, 100.0f, 100.0f);

	SceneManager();
	void manageScene(Models &models);
	glm::vec3 getLighPosition();

private:
	float rotatez = 0.0;

};
#endif

