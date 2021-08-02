#pragma once
#include "..\utils\shader_manager.h"

class Framebuffer
{
public:
	Framebuffer(glm::ivec2*);
	void Init();
	void Bind();
	void Unbind();
	void Resize(int, int);
	unsigned int* GetColorAttachment();
	glm::ivec2* GetScreenSize();
private:
	glm::ivec2* screenSize;
	int *height, *width;
	unsigned int fbo = 0; // Frame Buffer Object
	unsigned int cba = 0; // Color Buffer Attachment
	unsigned int rbo = 0; // Render Buffer Object (DEPTH24_STENCIL8)
};