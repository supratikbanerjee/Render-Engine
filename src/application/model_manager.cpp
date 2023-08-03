#include "model_manager.h"


Model::Model()
{
	printf("Model\n");
	type = ENTITYTYPE::MODEL;
	mat = new Material();
}


Mesh* Model::getMesh()
{
	return this->mesh;
}
	
void Model::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}


Shader* Model::getShader()
{
	return mat->getShader();
}

Material* Model::getMaterial()
{
	return mat;
}

void Model::Draw(PASS RENDERPASS)
{
	mat->ShaderParameters(RENDERPASS);
	mesh->Draw(mat->getShader(), *getName());
}