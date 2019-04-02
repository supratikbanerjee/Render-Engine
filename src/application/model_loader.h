#ifndef MODELLOADER_H
#define MODELLOADER_H
#include "model_manager.h"
#include "mesh_manager.h"
#include "../utils/texture_loader.h"
#include "../utils/OBJ_Loader.h"

class ModelLoader
{
public:
	
	ModelLoader();
	Model* LoadModel();
	int getModelCount();

private:
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec3 > tangent;
	std::vector< glm::vec3 > bitangent;

	glm::mat4 global;
	glm::mat4 local;

	glm::mat4 identity = glm::mat4(1.0f);

	vector<Vertex> vertexes;
	vector<Texture> textures;
	vector<unsigned int> indices;
	Vertex vertex;
	Texture texture;
	int mesh_count;
	Model root;
	//vector<Mesh*> meshes;
	TextureLoader TexLoader;

};
#endif;