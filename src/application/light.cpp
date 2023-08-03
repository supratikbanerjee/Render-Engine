#include "light.h"

Light::Light()
{
	printf("Light \n");
	Init();
}

void Light::Init()
{
	type = ENTITYTYPE::LIGHT;
	if (lightType == LightType::DIRECTIONAL)
	{
		LightVector = &getTransform()->rotation;
		lightFragValue = 0.0f;
	}
	else if (lightType == LightType::POINT)
	{
		LightVector = &getTransform()->translation;
		lightFragValue = 1.0f;
	}
}

glm::vec4* Light::GetLightVector()
{
	FragLightVector = glm::vec4(*LightVector, lightFragValue);
	return &FragLightVector;
}