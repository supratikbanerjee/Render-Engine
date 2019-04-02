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
	/*ShaderManager.getDiffuseAdd(&diffuseAdd);
	ShaderManager.getSpecularAdd(&specularAdd);
	ShaderManager.getSmoothness(&smoothness);
	ShaderManager.getOcclusion(&occlusion);
	ShaderManager.getSpecDefMult(&specular_default_multiplier);
	ShaderManager.getDiffuseColorTone(&diffuse_color_tone);*/

	shader->setFloat("smoothness", smoothness);
	shader->setFloat("occlusion", occlusion);
	shader->setFloat("specularAdd", specularAdd);
	shader->setFloat("diffuseAdd", diffuseAdd);
	shader->setFloat("spec_def_mult", specular_default_multiplier);
	shader->setVec3("diffuse_colorTone", diffuse_color_tone);

	/*ShaderManager.getIOR(&ior);
	ShaderManager.getRefRef(&reflection_refratoin_ratio);
	ShaderManager.getFresnel(&fresnel);*/

	shader->setFloat("IOR", ior);
	shader->setFloat("ref", reflection_refratoin_ratio);
	shader->setBool("fresn", fresnel);

	//ShaderManager.getNormalMapping(&normalMapping);
	shader->setBool("normalMapping", normal_mapping);

	//ShaderManager.getMipMappingAuto(&mipmap_auto);
	//ShaderManager.getMipMappingLevel(&mipmap_level);

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