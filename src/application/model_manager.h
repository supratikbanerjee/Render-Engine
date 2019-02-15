#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "../utils/texture_loader.h"
#include "mesh_manager.h"
class Models
{
public:
	std::vector < glm::mat4 > local;
	std::vector < glm::mat4 > global;

	int ModelCount;
	vector<Mesh> meshes;

	Models();
	void LoadModel();
	glm::mat4 getLocalModels(int indx);
	glm::mat4 getGlobalModels(int indx);
	void setLocalModels(int indx, glm::mat4 model);
	void setGlobalModels(int indx, glm::mat4 model);
	int getModelCount();
	Mesh getMesh(int indx);

private:
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec3 > tangent;
	std::vector< glm::vec3 > bitangent;

	vector<Vertex> vertexes;
	vector<Texture> textures;
	vector<unsigned int> indices;
	Vertex vertex;
	Texture texture;

	TextureLoader TexLoad;
};
#endif

