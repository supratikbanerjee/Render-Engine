#include <vector>
#include <glm\glm.hpp>

bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals, std::vector< glm::vec3 > & tangent, std::vector< glm::vec3 > & bitangent);
glm::vec3 getTangent(std::vector<glm::vec3> pos, std::vector<glm::vec2> uv);