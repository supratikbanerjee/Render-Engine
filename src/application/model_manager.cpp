#include "model_manager.h"
#include "../utils/OBJ_Loader.h"



Models::Models()
{
	printf("mmm\n");
}

void Models::LoadModel()
{
	/*const char *obj[] = { "../Assets/models/spitfire.obj","../Assets/models/prop.obj", "../Assets/models/cubet.obj",  "../Assets/models/cubet.obj" };
	const char *albedo[] = { "../Assets/textures/spitfire/spitfire_diffuse.png","../Assets/textures/prop/prop_diffuse.jpg","", ""};
	const char *normal[] = { "../Assets/textures/spitfire/spitfire_normal.png","../Assets/textures/prop/prop_normal.jpg","",""};
	const char *metallic[] = { "../Assets/textures/spitfire/spitfire_metallic.png","../Assets/textures/prop/prop_metallic.jpg","",""};
	const char *roughness[] = { "../Assets/textures/spitfire/spitfire_roughness.png","../Assets/textures/prop/prop_roughness.jpg","",""};
	const char *ambient[] = { "../Assets/textures/spitfire/spitfire_ambient.png","../Assets/textures/prop/prop_ambient.jpg","",""};*/

	const char *obj[] = { "../Assets/models/axe.obj","../Assets/models/cubet.obj" };
	const char *albedo[] = { "../Assets/textures/Axe/Axe_diffuse.png","" };
	const char *normal[] = { "../Assets/textures/Axe/Axe_normal.png","" };
	const char *metallic[] = { "../Assets/textures/Axe/Axe_metallic.png","" };
	const char *roughness[] = { "../Assets/textures/Axe/Axe_roughness.png","" };
	const char *ambient[] = { "../Assets/textures/Axe/Axe_ambient.png","" };
	ModelCount = (sizeof(obj) / sizeof(obj[0]));

	for (int i = 0; i < ModelCount; i++)
	{
		global.push_back(glm::mat4(1.0f));
		local.push_back(glm::mat4(1.0f));
		bool res = loadOBJ(obj[i], vertices, uvs, normals, tangent, bitangent);

		for (int j = 0; j < vertices.size(); j++)
		{
			vertex.Position = vertices[j];
			vertex.Normal = normals[j];
			vertex.TexCoords = uvs[j];
			//vertex.Tangent = tangent[j];
			//vertex.Bitangent = bitangent[j];
			vertexes.push_back(vertex);
			indices.push_back(j);
		}

		// TODO: refactor texture importing

		texture.id = TexLoad.TextureFromFile(albedo[i]);
		texture.type = "texture_diffuse";
		textures.push_back(texture);
		texture.id = TexLoad.TextureFromFile(normal[i]);
		texture.type = "texture_normal";
		textures.push_back(texture);
		texture.id = TexLoad.TextureFromFile(metallic[i]);
		texture.type = "texture_metallic";
		textures.push_back(texture);
		texture.id = TexLoad.TextureFromFile(roughness[i]);
		texture.type = "texture_roughness";
		textures.push_back(texture);
		texture.id = TexLoad.TextureFromFile(ambient[i]);
		texture.type = "texture_ambient";
		textures.push_back(texture);
		meshes.push_back(Mesh(vertexes, indices, textures));
		vertexes.clear();
		vertices.clear();
		uvs.clear();
		tangent.clear();
		bitangent.clear();
		normals.clear();
		textures.clear();
		indices.clear();
	}
}


void Models::getGlobalModels(int indx, glm::mat4* out_global)
{
	*out_global = global[indx];
}


void Models::getLocalModels(int indx, glm::mat4* out_local)
{
	*out_local = local[indx];
}

void Models::setGlobalModels(int indx, glm::mat4* model)
{
	global[indx] = *model;
}


void Models::setLocalModels(int indx, glm::mat4* model)
{
	local[indx] = *model;
}

int Models::getModelCount()
{
	return ModelCount;
}

void Models::getMesh(vector<Mesh>* out_meshes)
{
	*out_meshes = meshes;
}

void Models::setHierarchyModels(int indx_cur, int indx_prev)
{
	global[indx_cur] = global[indx_prev] * local[indx_cur];
}


