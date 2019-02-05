#version 330 core
in vec3 vertex_position;
in vec3 vertex_normals;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    Normal = mat3(transpose(inverse(model))) * vertex_normals;
    Position = vec3(model * vec4(vertex_position, 1.0));
    gl_Position = proj * view * model * vec4(vertex_position, 1.0);
}