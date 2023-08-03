#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <glad/glad.h>
#include <vector>
#include "../utils/shader_manager.h"

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};

struct Texture {
	unsigned int id;
	string type;
};

class Mesh 
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh();
	void CreateMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader* shader, string name);
	

private:
	

	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
#endif

