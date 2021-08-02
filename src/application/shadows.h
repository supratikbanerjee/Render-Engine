#pragma once
#include <glad/glad.h>
#include "../utils//shader_manager.h"

class ShadowMaps
{
public:
	ShadowMaps(int);
	Shader* GetShader();
	void Init();
	void Bind();
	void Unbind();
	unsigned int* GetDepthMap();
private:
	Shader shader;
	unsigned int depthMapfbo;
	unsigned int depthMap;
	unsigned int shadowMapResolution;
};