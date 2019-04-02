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
	void setActiveMeshId(int*);
	int* getActiveMeshId();
	int* getMeshCount();
	Mesh* getActiveMesh();

private:
	Model* models;
	int active_mesh_id = 0;
	glm::vec3 lightPos = glm::vec3(200.0f, 100.0f, 100.0f);
};
#endif

