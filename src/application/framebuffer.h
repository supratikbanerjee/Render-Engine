#pragma once
#include "..\utils\shader_manager.h"

class Framebuffer
{
public:
	Framebuffer(int*, int*);
	void Init();
	void Bind();
	void Unbind();
	unsigned int* GetColorAttachment();
private:

	int *height, *width;
	unsigned int fbo = 0; // Frame Buffer Object
	unsigned int cba = 0; // Color Buffer Attachment
	unsigned int rbo = 0; // Render Buffer Object (DEPTH24_STENCIL8)
};