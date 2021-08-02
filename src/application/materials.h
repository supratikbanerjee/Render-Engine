#pragma once
#include "../utils/shader_manager.h"

class Material
{
public:
	Material();
	Shader* shader;
	Shader* getShader();
	void ShaderParameters();
	void setRenderFace(int);

	float light_energy = 5.0;
	glm::vec3 base_color = glm::vec3(1.0f);
	float subsurface = 0.0;
	glm::vec3 subsurface_radius = glm::vec3(1.0f);
	glm::vec3 subsurface_color = glm::vec3(1.0f);
	float metallic = 0.0;
	float specular = 0.5;
	float roughness = 0.5;
	float occlusion = 0.0;
	float reflection_refratoin_ratio = 0.0;
	float ior = 1.5;
	float mipmap_level = 1.0;
	bool dipole = false;
	bool paralax_map = false;
	bool fresnel = false;
	bool normal_mapping = true;
	bool mipmap_auto = true;
	bool z_buffer = false;
	bool rough_tex = false;
	bool metallic_tex = false;
	int renderFace = 1;	
};