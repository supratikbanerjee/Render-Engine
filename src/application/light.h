#pragma once
#include "../utils/shader_manager.h"
#include "ecs/entity.h"

enum class LightType {DIRECTIONAL, POINT};
class Light : public Entity
{
public:
	LightType lightType;
	
	Light();
	void Init();
	glm::vec4* GetLightVector();
private:
	glm::vec3* LightVector;
	float lightFragValue;
	glm::vec4 FragLightVector;
};