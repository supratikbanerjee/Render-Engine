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
	TextureLoader TexLoad;

	unsigned int cubemapTexture;
	unsigned int skyboxVAO, skyboxVBO;

	/*float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};*/

	std::vector<std::string> faces
	{
		/*"../Assets/textures/skybox/right.jpg",
		"../Assets/textures/skybox/left.jpg",
		"../Assets/textures/skybox/top.jpg",
		"../Assets/textures/skybox/bottom.jpg",
		"../Assets/textures/skybox/front.jpg",
		"../Assets/textures/skybox/back.jpg"*/

		"../Assets/textures/skybox/posx.jpg",
		"../Assets/textures/skybox/negx.jpg",
		"../Assets/textures/skybox/posy.jpg",
		"../Assets/textures/skybox/negy.jpg",
		"../Assets/textures/skybox/posz.jpg",
		"../Assets/textures/skybox/negz.jpg"
	};


	Skybox();

	void skyboxTex();

	unsigned int getCubemapTexture();

	unsigned int getSkyboxVAO();
};
#endif