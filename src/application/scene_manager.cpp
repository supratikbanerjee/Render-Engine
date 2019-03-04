#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "scene_manager.h"
#include "../RenderEngine.h"

SceneManager::SceneManager()
{
	printf("sss\n");
	//ui.getTransformsObjects(&TransformsManager);
}

void SceneManager::manageScene(int active, Models &models, Camera& camera)
{
	model = glm::mat4(1.0f);
	
	TransformsManager.getAutoRotate(&AutoRotate);

	if (AutoRotate)
	{
		rotatez += 0.1f;
		model = glm::rotate(model, glm::radians(rotatez), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{

		TransformsManager.getRotateX(&rotateX);
		TransformsManager.getRotateY(&rotateY);
		TransformsManager.getRotateZ(&rotateZ);

		TransformsManager.getTranslateX(&translateX);
		TransformsManager.getTranslateY(&translateY);
		TransformsManager.getTranslateZ(&translateZ);

		TransformsManager.getTranslationScalingFactor(&translation_scaling_factor);

		model = glm::rotate(model, rotateX, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotateY, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	

	model = glm::translate(model, translation_scaling_factor*glm::vec3(translateX, translateY, translateZ));
	models.setLocalModels(0, &model);
	models.setGlobalModels(0, &model);

	//fpCamModel = glm::translate(model, glm::vec3(-0.000566f , 0.564291f , -0.339490 ));
	//glm::decompose(fpCamModel, scale, rotation, fpCamPos, skew, perspective);

	//tpCamModel = glm::translate(model, glm::vec3(-0.004864f, 2.337512f, -9.007556));
	//glm::decompose(tpCamModel, scale, rotation, tpCamPos, skew, perspective);
	//camera.setFirstPersonCamPosition(&fpCamPos);
	//cout << glm::to_string(fpCamPos) << endl;


	/*model = glm::mat4(1.0f);
	//model = glm::rotate(glm::radians(500 * rotatez), glm::vec3(0.0f, 0.0f, 1.0f));
	models.setLocalModels(active+1, &model);
	models.setGlobalModels(active+1 , &model);
	models.setHierarchyModels(active+1, active);*/

	/*model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));
	models.setLocalModels(3, &model);
	models.setGlobalModels(3, &model);*/
	//models.setHierarchyModels(3, active);

	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
	model = glm::translate(model, lightPos);
	models.setLocalModels(1, &model);
	models.setGlobalModels(1, &model);	
}

glm::vec3 SceneManager::getLighPosition()
{
	return lightPos;
}

void SceneManager::getFirstPersonCamPosition(glm::vec3* out_cam_pos)
{
	*out_cam_pos = fpCamPos;
}

void SceneManager::getThirdPersonCamPosition(glm::vec3* out_cam_pos)
{
	*out_cam_pos = tpCamPos;
}