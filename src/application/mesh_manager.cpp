#include <glm/glm.hpp>
#include "mesh_manager.h"

vector<Vertex> vertices;
vector<unsigned int> indices;
vector<Texture> textures;
unsigned int VAO;

Mesh::Mesh()
{
	printf("Mesh\n");	
}

void Mesh::CreateMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		string name = textures[i].type;
		shader->setInt((name).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Mesh::ShaderParameters(Shader* shader)
{
	shader->setFloat("light_energy", light_energy);

	shader->setVec3("base_color", base_color);
	shader->setFloat("subsurface", subsurface);
	shader->setVec3("subsurface_color", subsurface_color);
	shader->setVec3("subsurface_radius", subsurface_radius);
	shader->setFloat("p_metallic", metallic);
	shader->setFloat("specular", specular);
	shader->setFloat("p_roughness", roughness);
	
	shader->setFloat("occlusion", occlusion);
	shader->setBool("dipole", dipole);
	shader->setBool("paralax_map", paralax_map);
	shader->setFloat("IOR", ior);
	shader->setFloat("ref", reflection_refratoin_ratio);
	shader->setBool("fresn", fresnel);
	shader->setBool("normalMapping", normal_mapping);
	shader->setFloat("mipmap_level", mipmap_level);
	shader->setBool("mipmap_auto", mipmap_auto);
}


void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glBindVertexArray(0);
}