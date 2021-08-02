#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "model_loader.h"
#include "camera.h"

class SceneManager
{
public:
	SceneManager(Model*, Camera*);
	glm::vec4 getLighPosition();
	void setActiveModelId(int*);
	int* getActiveModelId();
	int* getModelCount();
	Model* getActiveModel();
	std::string* getModelName(int*);
	Camera* GetMainCamera();

private:
	Camera* camera;
	Model* models;
	int active_model_id = 0;
	glm::vec4 lightPos = glm::vec4(200.0f, 100.0f, 100.0f, 1.0f);
};
#endif

