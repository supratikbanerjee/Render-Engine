#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "mesh_manager.h"
#include "transforms.h"
#include "materials.h"

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
	void Draw();
	int* getChildCount();
	Shader* getShader();

	std::string* getName();
	
	Material* getMaterial();
	Model* getChild(int*);
	Mesh* getMesh();
	Transforms* getTransform();

private:
	int id;
	int childCount;
	std::string name;

	std::vector<Model*> children;
	Model* parent;

	Transforms transform;
	Mesh* mesh;
	Material* mat;

};
#endif