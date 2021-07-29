#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "mesh_manager.h"
#include "transforms.h"

class Model
{
public:
	Model();
	void AddChild(Model*);
	
	void setMesh(Mesh*);
	void setId(int*);
	void setName(std::string*);

	void getId(int&);
	void getChildren(std::vector<Model*>&);
	void Init();
	int* getChildCount();

	std::string* getName();
	
	Model* getChild(int*);
	Mesh* getMesh();
	Shader* getShader();
	Transforms* getTransform();

private:
	int id;
	int childCount;
	std::string name;

	std::vector<Model*> children;
	Shader shader;
	Transforms transform;
	Model* parent;
	Mesh* mesh;

};
#endif