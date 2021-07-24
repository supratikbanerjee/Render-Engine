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

	float light_energy = 5.0;
	// Shader Parameters
	glm::vec3 base_color = glm::vec3(1.0f);
	float subsurface = 0.0;
	glm::vec3 subsurface_radius = glm::vec3(1.0f);
	glm::vec3 subsurface_color = glm::vec3(1.0f);
	float metallic = 0.0;
	float specular = 0.5;
	float roughness = 0.5;



	float occlusion = 0.0;
	
	float reflection_refratoin_ratio = 0.0;
	float ior = 1.5;
	float mipmap_level = 1.0;
	bool dipole = false;
	bool paralax_map = false;
	bool fresnel = false;
	bool normal_mapping = true;
	bool mipmap_auto = true;
	bool z_buffer = false;


private:
	

	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
#endif

