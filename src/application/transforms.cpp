#include "transforms.h"
#include <iostream>


Transforms::Transforms()
{
	printf("Transforms\n");

}

glm::vec3* Transforms::getRotation()
{
	return &rotation;
}

glm::vec3* Transforms::getTranslation()
{
	return &translation;
}

void Transforms::setRotation(glm::vec3* in_rotation)
{
	rotation = *in_rotation;
}

void Transforms::setTranslation(glm::vec3* in_translation)
{
	translation = *in_translation;
}



