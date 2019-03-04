#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include <vector>
#include <glm/glm.hpp>
#include "../utils/texture_loader.h"
#include "mesh_manager.h"
class Models
{
public:


	Models();
	void LoadModel();
	void getLocalModels(int indx, glm::mat4* out_local);
	void getGlobalModels(int indx, glm::mat4* out_global);
	void setLocalModels(int indx, glm::mat4* model);
	void setGlobalModels(int indx, glm::mat4* model);
	void setHierarchyModels(int indx_cur, int indx_prev);
	int getModelCount();
	void getMesh(vector<Mesh>* out_meshes);

private:
	std::vector < glm::mat4 > local;
	std::vector < glm::mat4 > global;

	int ModelCount;
	vector<Mesh> meshes;
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

