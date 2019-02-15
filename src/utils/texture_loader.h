#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "../utils/stb_image.h"


using namespace std;

class TextureLoader
{
public:

	TextureLoader();

	unsigned int loadCubemap(std::vector<std::string> faces);

	unsigned int LoadHDR(const char *path);

	unsigned int TextureFromFile(const char *path);
};
#endif