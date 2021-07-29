#include "model_manager.h"


Model::Model()
{
	printf("Model\n");
	shader.CompileShaders("shaders/PBR/PBR.vs.glsl", "shaders/PBR/P_BSDF.frag");
}

void Model::Init()
{
	transform.model = glm::mat4(1.0f);
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

void Model::setMesh(Mesh *mesh)
{
	this->mesh = mesh;
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

Transforms* Model::getTransform()
{
	return &transform;
}