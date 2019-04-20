#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "mesh_manager.h"
class Model
{
public:
	Model();
	void AddChild(Model*);
	void setLocalTransform(glm::mat4*);
	void setGlobalTransform(glm::mat4*);
	void setMesh(Mesh*);
	void setId(int*);
	void setName(std::string*);

	glm::mat4* getLocalTransform();
	glm::mat4* getGlobalTransform();
	void getChildren(std::vector<Model*>&);
	int* getChildCount();
	Model* getChild(int*);
	Mesh* getMesh();
	void getId(int&);
	Shader* getShader();
	std::string* getName();

private:
	Shader shader;
	int id;
	int childCount;
	std::string name;
	Model *parent;
	std::vector<Model*> children;
	Mesh *mesh;
	glm::mat4 local;
	glm::mat4 global;
};
#endif