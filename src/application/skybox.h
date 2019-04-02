#ifndef SKYBOX_H
#define SKYBOX_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

#include "../utils/stb_image.h"
#include "../utils/texture_loader.h"


class Skybox
{
public:
	Skybox();
	unsigned int getCubemapTexture();
	unsigned int getSkyboxVAO();

private:
	TextureLoader TexLoad;
	unsigned int cubemap_texture;
	unsigned int skyboxVAO, skyboxVBO;
	std::vector<std::string> faces
	{

		"../Assets/textures/skybox/posx.jpg",
		"../Assets/textures/skybox/negx.jpg",
		"../Assets/textures/skybox/posy.jpg",
		"../Assets/textures/skybox/negy.jpg",
		"../Assets/textures/skybox/posz.jpg",
		"../Assets/textures/skybox/negz.jpg"
	};

	void skyboxTex();

};
#endif