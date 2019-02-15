#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <glad/glad.h>
#include <vector>

#include "../utils/shader_manager.h"

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	void Draw(Shader shader);

private:

	unsigned int VBO, EBO;
	void setupMesh();
};
#endif

