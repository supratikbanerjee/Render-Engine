#include "model_loader.h"



ModelLoader::ModelLoader()
{
	printf("Model Loader\n");
}

Model* ModelLoader::LoadModel()
{
	std::string base = "../Assets/";
	std::string model_dir = "models/";
	std::string texture_dir = "textures/";
	std::string model = "Head/";
	std::string temp;
	const char* dir;

	const char* obj[] = { "head.obj" };
	const char* albedo[] = { "lambertian.jpg" };
	const char* normal[] = { "perry_normal.png" };
	const char* metallic[] = { "" };
	const char* roughness[] = { "" };
	const char* ambient[] = { "out_occlusion.bmp" };
	const char* specular[] = { "out_translucency.bmp" };
	const char* depth[] = { "bump.png" };

	mesh_count = (sizeof(obj) / sizeof(obj[0]));
	root.setLocalTransform(&identity);
	root.setGlobalTransform(&identity);
	//int tempid = -1;
	//root.setId(&tempid);

	for (int i = 0; i < mesh_count; i++)
	{
		temp = base + model_dir + model;
		temp.append(obj[i]);
		dir = temp.c_str();
		bool res = loadOBJ(dir, vertices, uvs, normals, tangent, bitangent);

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

		// TODO: refactor texture importing
		if (albedo[i] != "")
		{
			temp = base + texture_dir + model;
			temp.append(albedo[i]);
		}
		else
			temp = default_mat;
		dir = temp.c_str();
		texture.id = TexLoader.TextureFromFile(dir);
		texture.type = "texture_diffuse";
		textures.push_back(texture);
		if (normal[i] != "")
		{
			temp = base + texture_dir + model;
			temp.append(normal[i]);
		}
		else
			temp = default_mat;
		dir = temp.c_str();
		texture.id = TexLoader.TextureFromFile(dir);
		texture.type = "texture_normal";
		textures.push_back(texture);

		if (metallic[i] != "")
		{
			temp = base + texture_dir + model;
			temp.append(metallic[i]);
		}
		else
			temp = default_mat;
		dir = temp.c_str();
		texture.id = TexLoader.TextureFromFile(dir);
		texture.type = "texture_metallic";
		textures.push_back(texture);
		if (roughness[i] != "")
		{
			temp = base + texture_dir + model;
			temp.append(roughness[i]);
		}
		else
			temp = default_mat;
		dir = temp.c_str();
		texture.id = TexLoader.TextureFromFile(dir);
		texture.type = "texture_roughness";
		textures.push_back(texture);
		if (specular[i] != "")
		{
			temp = base + texture_dir + model;
			temp.append(specular[i]);
		}
		else
			temp = default_mat;
		dir = temp.c_str();
		texture.id = TexLoader.TextureFromFile(dir);
		texture.type = "texture_specular";
		textures.push_back(texture);

		if (depth[i] != "")
		{
			temp = base + texture_dir + model;
			temp.append(depth[i]);
		}
		else
			temp = default_mat;
		dir = temp.c_str();
		texture.id = TexLoader.TextureFromFile(dir);
		texture.type = "texture_depth";
		textures.push_back(texture);
		

		//name = model.substr(0, model.length()-1);
		Mesh *mesh = new Mesh();
		Model *child = new Model();
		mesh->CreateMesh(vertexes, indices, textures);
		std::string name = obj[i];
		name = std::string(obj[i], 0, name.length() - 4);
		child->setName(&name);
		child->setId(&i);
		child->setMesh(mesh);
		child->setLocalTransform(&identity);
		global = *root.getGlobalTransform();
		local = *child->getLocalTransform();
		child->setGlobalTransform(&(global * local));
		root.AddChild(child);

		vertexes.clear();
		vertices.clear();
		uvs.clear();
		tangent.clear();
		bitangent.clear();
		normals.clear();
		textures.clear();
		indices.clear();
	}
	return &root;
}