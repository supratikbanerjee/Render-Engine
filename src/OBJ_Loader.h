#include <vector>
#include <glm\glm.hpp>

bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals, std::vector< unsigned int > out_indices_vec, std::vector< unsigned int >);


#pragma once
