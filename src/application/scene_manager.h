#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "model_loader.h"
#include "camera.h"
#include "light.h"

class SceneManager
{
public:
	SceneManager(Entity*, Camera*);
	
	void setActiveModelId(int*);
	int* getActiveModelId();
	int* getModelCount();
	Entity* getActiveModel();
	std::string* getModelName(int*);
	Camera* GetMainCamera();
	Entity* GetModels();


	glm::vec4* getLightVector();
private:
	Camera* camera;
	Entity* entities;
	int active_model_id = 0;
	//glm::vec4 lightPos = glm::vec4(2.0f, 1.0f, 1.0f, 0.0f);
	Light* mainLight;
};
#endif

