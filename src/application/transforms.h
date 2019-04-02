#ifndef TRANSFORMS_H
#define TRANSFORMS_H
#include <glm/glm.hpp>
class Transforms
{


public:
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 translation = glm::vec3(0.0f);;
	glm::vec3 scale = glm::vec3(1.0f);;

	Transforms();

	void setRotation(glm::vec3*);
	void setTranslation(glm::vec3*);

	glm::vec3* getRotation();
	glm::vec3* getTranslation();
};
#endif;
