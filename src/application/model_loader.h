#ifndef MODELLOADER_H
#define MODELLOADER_H
#include "model_manager.h"
#include "mesh_manager.h"
#include "metrics.h"
#include "../utils/texture_loader.h"
#include "../utils/OBJ_Loader.h"

class ModelLoader
{
public:
	
	ModelLoader(Metrics*);
	Model* LoadModel();

private:
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec3 > tangent;
	std::vector< glm::vec3 > bitangent;
	std::vector< unsigned int > vertIndices;

	vector<Vertex> vertexes;
	vector<Texture> textures;
	vector<unsigned int> indices;
	Vertex vertex;
	Texture texture;
	int model_count;
	Model root;
	std::string default_mat = "Assets/defaults/default_material.png";
	//vector<Mesh*> meshes;
	TextureLoader TexLoader;

	Metrics* metrics;
	int verts = 0;
	int tris = 0;

};
#endif;