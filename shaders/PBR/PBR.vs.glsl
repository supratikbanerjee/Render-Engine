#version 330 core
layout (location = 0) in vec3 Vertex;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;

out vec2 TexCoords;
out vec3 WorldPosition;
out vec3 Normals;


uniform mat4 MVP;
uniform mat4 model;


void main()
{
	Normals = mat3(model) * Normal;
    TexCoords = vec2(UV.x, 1-UV.y);    
    gl_Position = MVP * vec4(Vertex, 1.0);
    WorldPosition = vec3(model * vec4(Vertex, 1.0));
}