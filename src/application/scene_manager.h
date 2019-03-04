#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "model_manager.h"
#include "../utils/gizmo.h"
#include "../ui/transforms_manager_ui.h"
#include "camera.h"


static glm::vec3 scale;
static glm::quat rotation;
static glm::vec3 fpCamPos;
static glm::vec3 tpCamPos;
static glm::vec3 skew;
static glm::vec4 perspective;
static glm::mat4 fpCamModel;
static glm::mat4 tpCamModel;

class SceneManager
{
public:
	SceneManager();
	void manageScene(int active, Models &models, Camera& getGizmo);
	glm::vec3 getLighPosition();
	void getFirstPersonCamPosition(glm::vec3*);
	void getThirdPersonCamPosition(glm::vec3*);


private:
	TransformsManagerUI TransformsManager;

	float rotateX;
	float rotateY;
	float rotateZ;

	float translateX;
	float translateY;
	float translateZ;

	float translation_scaling_factor;

	float rotateAngle;
	glm::vec3 direction;
	glm::vec3 lightPos = glm::vec3(200.0f, 100.0f, 100.0f);
	glm::mat4 model;
	glm::mat4 model_temp;
	float rotatez = 0.0;

	bool AutoRotate = false;

};
#endif

