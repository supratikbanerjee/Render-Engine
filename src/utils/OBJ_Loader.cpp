#include "OBJ_Loader.h"

glm::vec3 getTangent(std::vector<glm::vec3> pos, std::vector<glm::vec2> uv)
{
	//printf("%f %f %f \n", pos[0].x, pos[0].y, pos[0].z);

	glm::vec3 tangent, bitangent;
	// triangle 1
	// ----------
	glm::vec3 w = pos[1] - pos[0];
	glm::vec3 v = pos[2] - pos[0];

	float sx = uv[1].x - uv[0].x;
	float tx = uv[2].x - uv[0].x;

	float sy = uv[1].y - uv[0].y;
	float ty = uv[2].y - uv[0].y;

	float dirCorrection = (tx * sy - ty * sx) < 0.0f ? -1.0f : 1.0f;
	// when t1, t2, t3 in same position in UV space, just use default UV direction.
	if (sx * ty == sy * tx) {
		sx = 0.0; sy = 1.0;
		tx = 1.0; ty = 0.0;
	}
	//float f = 1.0f / (deltaUV1x * deltaUV2y - deltaUV2.x * deltaUV1.y);

	tangent.x = (w.x * sy - v.x * ty) * dirCorrection;
	tangent.y = (w.y * sy - v.y * ty) * dirCorrection;
	tangent.z = (w.z * sy - v.z * ty) * dirCorrection;
	tangent = glm::normalize(tangent);

	bitangent.x = (w.x * sx - v.x * tx) * dirCorrection;
	bitangent.y = (w.y * sx - v.y * tx) * dirCorrection;
	bitangent.z = (w.z * sx - v.z * tx) * dirCorrection;
	bitangent = glm::normalize(bitangent);


	return tangent, bitangent;
}

bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertices, std::vector < glm::vec2 > & out_uvs, std::vector < glm::vec3 > & out_normals, std::vector< glm::vec3 > & tangent, std::vector< glm::vec3 > & bitangent)
{
	unsigned int cc = 0;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, " %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			//printf(" %f %f %f\n", vertex.x, vertex.y, vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			//std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			//printf("%d/%d/%d %d/%d/%d %d/%d/%d\n", vertexIndex[0], uvIndex[0], normalIndex[0], vertexIndex[1], uvIndex[1], normalIndex[1], vertexIndex[2], uvIndex[2], normalIndex[2]);
			//int matches = fscanf(file, "%d\//%d %d\//%d %d\//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			//printf("%d//%d %d//%d %d//%d\n", vertexIndex[0], normalIndex[0], vertexIndex[1], normalIndex[1], vertexIndex[2], normalIndex[2]);
			if (matches != 9) {			

				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	printf("%d %d\n", temp_vertices.size(), normalIndices.size());

	/*for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		//printf("%d VI\n", vertexIndices[i]);
		out_indices_vec.push_back(vertexIndices[i] - 1);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		out_indices_norm.push_back(normalIndices[i] - 1);
	}*/


	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		//printf(" %f %f %f\n", vertex.x, vertex.y, vertex.z);
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}
	int tc = 0;
	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> uv;
	glm::vec3 tangent_tmp = glm::vec3(1.0);
	glm::vec3 bitangent_tmp = glm::vec3(1.0);

	for (unsigned int i = 0; i < vertexIndices.size()/3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			tc++;
			pos.push_back(out_vertices[i+j]);
			uv.push_back(out_uvs[i+j]);

		}
		tangent_tmp, bitangent_tmp = getTangent(pos, uv);
		//printf("T %f %f %f \n", tangent_tmp.x, tangent_tmp.y, tangent_tmp.z);
		//printf("B %f %f %f \n", bitangent_tmp.x, bitangent_tmp.y, bitangent_tmp.z);
		tangent.push_back(tangent_tmp);
		tangent.push_back(tangent_tmp);
		tangent.push_back(tangent_tmp);
		bitangent.push_back(bitangent_tmp);
		bitangent.push_back(bitangent_tmp);
		bitangent.push_back(bitangent_tmp);

		pos.clear();
		uv.clear();
	}

	/*for (unsigned int i = 0; i < temp_vertices.size(); i++) {
		out_vertices.push_back(temp_vertices[i]);
	}

	for (unsigned int i = 0; i < temp_normals.size(); i++) {
		out_normals.push_back(temp_normals[i]);
	}*/

	//printf("%d %d\n", out_indices_vec.size(), out_indices_norm.size());
	printf("load %d\n", cc);
}

