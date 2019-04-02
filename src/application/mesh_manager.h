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
	void Draw(Shader* shader);
	void ShaderParameters(Shader*);

	// Shader Parameters
	float diffuseAdd = 1.0;
	float specularAdd = 1.0;
	float smoothness = 1.0;
	float occlusion = 0.0;
	float specular_default_multiplier = 10.0;
	float reflection_refratoin_ratio = 0.0;
	float ior = 1.5;
	float mipmap_level = 1.0;

	bool fresnel = false;
	bool normal_mapping = true;
	bool mipmap_auto = true;

	glm::vec3 diffuse_color_tone = glm::vec3(1.0f);

private:
	

	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
#endif

