#pragma once
#include <vector>
#include <string>
#include "../transforms.h"

enum class ENTITYTYPE {MODEL, LIGHT};
class Entity
{
public:
	ENTITYTYPE type;
	Entity();
	Entity* getChild(int*);
	void getChildren(std::vector<Entity*>&);
	void AddChild(Entity*);

	void setId(int*);
	void setName(std::string);
	void getId(int&);
	int* getChildCount();
	std::string* getName();

	Transforms* getTransform();

private:
	int id;
	int childCount;
	std::string name;
	std::vector<Entity*> children;
	Entity* parent;

	Transforms* transform;

};