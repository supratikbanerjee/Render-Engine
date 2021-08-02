#include "framebuffer.h"
#include "glad\glad.h"

#include <iostream>

Framebuffer::Framebuffer(glm::ivec2* screenSize)
{
	printf("Framebuffer\n");
	this->screenSize = screenSize;
	Init();
}

void Framebuffer::Init()
{
	if (fbo)
	{
		glDeleteFramebuffers(1, &fbo);
		glDeleteTextures(1, &cba);
		glDeleteRenderbuffers(1, &rbo);
		fbo = 0;
		cba = 0;
		rbo = 0;
	}
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &cba);
	glBindTexture(GL_TEXTURE_2D, cba);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenSize->x, screenSize->y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cba, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenSize->x, screenSize->y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); 
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, screenSize->x, screenSize->y);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Resize(int width, int height)
{
	screenSize->x = width;
	screenSize->y = height;

	Init();
}

unsigned int* Framebuffer::GetColorAttachment()
{
	return &cba;
}

glm::ivec2* Framebuffer::GetScreenSize()
{
	return screenSize;
}