#include "model_manager.h"


Model::Model()
{
	printf("Model\n");
	shader.CompileShaders("shaders/PBR/PBR.vs.glsl", "shaders/PBR/P_BSDF.frag");
}

void Model::setId(int *id)
{
	this->id = *id;
}

void Model::setName(std::string* name)
{
	this->name = *name;
}

void Model::AddChild(Model *child)
{
	children.push_back(child);
}

void Model::setGlobalTransform(glm::mat4 *global)
{
	this->global = *global;
}

void Model::setLocalTransform(glm::mat4 *local)
{
	this->local = *local;
}

void Model::setMesh(Mesh *mesh)
{
	this->mesh = mesh;
}
glm::mat4* Model::getGlobalTransform()
{
	return &this->global;
}

glm::mat4* Model::getLocalTransform()
{
	return &this->local;
}

void Model::getChildren(std::vector<Model*> &children)
{
	children = this->children;
}

Mesh* Model::getMesh()
{
	return this->mesh;
}
	
Model* Model::getChild(int *idx)
{
	//printf("%d IDX\n", *idx);
	return this->children[*idx];
}

void Model::getId(int &id)
{
	id = this->id;
}

int* Model::getChildCount()
{
	childCount = children.size();
	return &childCount;
}

Shader* Model::getShader()
{
	return &shader;
}

std::string* Model::getName()
{
	return &name;
}