#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <glm/glm.hpp>
#include "mesh_manager.h"
#include "materials.h"
#include "../RenderEngine.h"
#include "ecs/entity.h"

class Model : public Entity
{
public:
	Model();

	void setMesh(Mesh*);
	void Draw(PASS);
	Shader* getShader();
	Material* getMaterial();
	Mesh* getMesh();
	

private:
	Mesh* mesh;
	Material* mat;

};
#endif