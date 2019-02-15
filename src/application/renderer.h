#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include "../utils/shader_manager.h"
#include "../global_variables.h"
#include "skybox.h"
#include "camera.h"
#include "scene_manager.h"

class Renderer
{
public:
	SceneManager scene;

	Renderer();
	void Render(Shader shader, Shader skybox_shader, Skybox sky, Camera camera);
private:
	int display_w = 1920;
	int display_h = 1080;
};
#endif

