#include "model_loader.h"



ModelLoader::ModelLoader(Metrics* metrics)
{
	printf("Model Loader\n");
	this->metrics = metrics;
}

void ModelLoader::LoadTexture(const char* textureType, const char* typeName)
{
	if (textureType != "")
	{
		temp = base + texture_dir + model;
		temp.append(textureType);
	}
	else
		temp = default_mat;
	dir = temp.c_str();
	texture.id = TexLoader.TextureFromFile(dir);
	texture.type = typeName;
	textures.push_back(texture);
}

Model* ModelLoader::LoadModel()
{
	const char* obj[] = { "plane_f.obj", "dragonbody.obj", "dragonchain.obj" };
	const char* albedo[] = {"", "dragonbody_diffuse.png", "dragonchain_diffuse.png" };
	const char* normal[] = {"", "dragonbody_normal.png", "dragonchain_normal.png" };
	const char* metallic[] = {"", "dragonbody_metallic.png", "dragonchain_metallic.png" };
	const char* roughness[] = {"", "dragonbody_roughness.png", "dragonchain_roughness.png" };
	const char* ambient[] = {"", "dragonbody_ambient.png", "dragonchain_ambient.png" };
	const char* specular[] = {"", "", "" };
	const char* depth[] = {"", "", "" };

	model_count = (sizeof(obj) / sizeof(obj[0]));
	root.Init();

	for (int i = 0; i < model_count; i++)
	{
		temp = base + model_dir + model;
		temp.append(obj[i]);
		dir = temp.c_str();
		bool res = loadOBJ(dir, vertices, uvs, normals, tangent, bitangent, vertIndices);

		for (int j = 0; j < vertices.size(); j++)
		{
			vertex.position = vertices[j];
			vertex.normal = normals[j];
			vertex.tex_coords = uvs[j];
			//vertex.Tangent = tangent[j];
			//vertex.Bitangent = bitangent[j];
			vertexes.push_back(vertex);
			indices.push_back(j);
		}
		LoadTexture(albedo[i], "texture_diffuse");
		LoadTexture(normal[i], "texture_normal");
		LoadTexture(metallic[i], "texture_metallic");
		LoadTexture(roughness[i], "texture_roughness");
		LoadTexture(ambient[i], "texture_ambient");
		LoadTexture(specular[i], "texture_specular");
		LoadTexture(depth[i], "texture_depth");
		
		Mesh *mesh = new Mesh();
		Model *child = new Model();
		mesh->CreateMesh(vertexes, indices, textures);
		std::string name = obj[i];
		name = std::string(obj[i], 0, name.length() - 4);
		child->setName(&name);
		child->setId(&i);
		child->setMesh(mesh);
		child->Init();
		root.AddChild(child);

		verts += vertexes.size();
		tris += vertIndices.size() / 3;
		metrics->tris = &tris;
		metrics->verts = &verts;

		vertexes.clear();
		vertices.clear();
		uvs.clear();
		tangent.clear();
		bitangent.clear();
		normals.clear();
		textures.clear();
		indices.clear();
		vertIndices.clear();
	}
	return &root;
}