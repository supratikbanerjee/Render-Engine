#include "shadows.h"
#include <iostream>

ShadowMaps::ShadowMaps(int resolution)
{
	printf("ShadowMaps\n");
    shader.CompileShaders("shaders/shadowmap.vs", "shaders/shadowmap.fs");
    shadowMapResolution = resolution;
    Init();
}

void ShadowMaps::Init()
{
	glGenFramebuffers(1, &depthMapfbo);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapResolution, shadowMapResolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapfbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Shader* ShadowMaps::GetShader()
{
    return &shader;
}

void ShadowMaps::Bind()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, shadowMapResolution, shadowMapResolution);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapfbo);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMaps::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int* ShadowMaps::GetDepthMap()
{
    return &depthMap;
}