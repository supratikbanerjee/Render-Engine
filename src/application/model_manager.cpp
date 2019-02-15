#include "model_manager.h"
#include "../utils/OBJ_Loader.h"



Models::Models()
{}

void Models::LoadModel()
{
	const char *obj[] = { "../Assets/models/eye.obj","../Assets/models/cubet.obj" };
	const char *albedo[] = { "../Assets/textures/eye/eye_diffuse.png","" };
	const char *normal[] = { "../Assets/textures/eye/eye_normal.png","" };
	const char *metallic[] = { "../Assets/textures/eye/eye_metallic.png","" };
	const char *roughness[] = { "../Assets/textures/eye/eye_roughness.png","" };
	const char *ambient[] = { "../Assets/textures/eye/eye_ambient.png","" };

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


glm::mat4 Models::getGlobalModels(int indx)
{
	return global[indx];
}


glm::mat4 Models::getLocalModels(int indx)
{
	return local[indx];
}

void Models::setGlobalModels(int indx, glm::mat4 model)
{
	global[indx] = model;
}


void Models::setLocalModels(int indx, glm::mat4 model)
{
	local[indx] = model;
}

int Models::getModelCount()
{
	return ModelCount;
}

Mesh Models::getMesh(int indx)
{
	return meshes[indx];
}

