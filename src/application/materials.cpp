#include "materials.h"

Material::Material()
{
	shader = new Shader();
	shader->CompileShaders("shaders/PBR/PBR.vs.glsl", "shaders/PBR/P_BSDF.frag");
}

void Material::ShaderParameters()
{
	switch (renderFace)
	{
	case 0:
		glDisable(GL_CULL_FACE);
		break;
	case 1:
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_FRONT);
		break;
	case 2:
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		break;
	}

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
	shader->setBool("z_buffer", z_buffer);
	shader->setBool("roughness_tex", rough_tex);
	shader->setBool("metallic_tex", metallic_tex);
}

void Material::setRenderFace(int opt)
{
	renderFace = opt;

}

Shader* Material::getShader()
{
	return shader;
}