#include "model_loader.h"



ModelLoader::ModelLoader()
{
	printf("Model Loader\n");
}

Model* ModelLoader::LoadModel()
{

	const char *obj[] = { "../Assets/models/dragonbody.obj","../Assets/models/dragonchain.obj"};
	const char *albedo[] = { "../Assets/textures/dragonbody/dragonbody_diffuse.png", "../Assets/textures/dragonchain/dragonchain_diffuse.png"};
	const char *normal[] = { "../Assets/textures/dragonbody/dragonbody_normal.png", "../Assets/textures/dragonchain/dragonchain_normal.png"};
	const char *metallic[] = { "../Assets/textures/dragonbody/dragonbody_metallic.png", "../Assets/textures/dragonchain/dragonchain_metallic.png"};
	const char *roughness[] = { "../Assets/textures/dragonbody/dragonbody_roughness.png", "../Assets/textures/dragonchain/dragonchain_roughness.png"};
	const char *ambient[] = { "../Assets/textures/dragonbody/dragonbody_ambient.png","../Assets/textures/dragonchain/dragonchain_ambient.png"};

	mesh_count = (sizeof(obj) / sizeof(obj[0]));
	root.setLocalTransform(&identity);
	root.setGlobalTransform(&identity);
	//int tempid = -1;
	//root.setId(&tempid);

	for (int i = 0; i < mesh_count; i++)
	{

		bool res = loadOBJ(obj[i], vertices, uvs, normals, tangent, bitangent);

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

		texture.id = TexLoader.TextureFromFile(albedo[i]);
		texture.type = "texture_diffuse";
		textures.push_back(texture);
		texture.id = TexLoader.TextureFromFile(normal[i]);
		texture.type = "texture_normal";
		textures.push_back(texture);
		texture.id = TexLoader.TextureFromFile(metallic[i]);
		texture.type = "texture_metallic";
		textures.push_back(texture);
		texture.id = TexLoader.TextureFromFile(roughness[i]);
		texture.type = "texture_roughness";
		textures.push_back(texture);
		texture.id = TexLoader.TextureFromFile(ambient[i]);
		texture.type = "texture_ambient";
		textures.push_back(texture);

		Mesh *mesh = new Mesh();
		Model *child = new Model();
		mesh->CreateMesh(vertexes, indices, textures);

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

int ModelLoader::getModelCount()
{
	return mesh_count;
}