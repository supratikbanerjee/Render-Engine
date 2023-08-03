#include "entity.h"

Entity::Entity()
{
	transform = new Transforms();

}


Transforms* Entity::getTransform()
{
	return transform;
}

void Entity::setId(int* id)
{
	this->id = *id;
}

void Entity::setName(std::string name)
{
	this->name = name;
}

void Entity::AddChild(Entity* child)
{
	children.push_back(child);
}

void Entity::getChildren(std::vector<Entity*>& children)
{
	children = this->children;
}

Entity* Entity::getChild(int* idx)
{
	//printf("%d IDX\n", *idx);
	return this->children[*idx];
}

void Entity::getId(int& id)
{
	id = this->id;
}


int* Entity::getChildCount()
{
	childCount = children.size();
	return &childCount;
}

std::string* Entity::getName()
{
	return &name;
}