#pragma once

struct RenderParams
{
	bool shaded = true;
	bool wireframe = false;
	bool skybox = true;
};

enum class PASS { SHADOW, GEOMETRY };