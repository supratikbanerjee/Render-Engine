#define OBJECTHANDLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include "stb_image.h"
#include "Shader.h"

class ObjectHandler
{
public:
	unsigned int VBO_P, VBO_N, VBO_T, EBO, VAO;
	unsigned int texture;
	unsigned int cubemapTexture;
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int loadCubemap(std::vector<std::string> faces)
	{
		//std::cout << "Cubemap " << std::endl;
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				//std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

	void genVAO(int objs, std::vector < std::vector< glm::vec3 >> vertices, std::vector < std::vector< glm::vec3 >> normals, std::vector < float > vertex_count, std::vector <unsigned int> vertex_position, Shader shader)
	{

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO_P);
		glGenBuffers(1, &VBO_N);

		GLuint v_vbo_size = 0;
		GLuint n_vbo_size = 0;
		unsigned int prev_size = 0;

		for (int i = 0; i < vertices.size(); i++)
		{
			v_vbo_size += vertices[i].size();
			n_vbo_size += normals[i].size();
		}

		//glGenBuffers(1, &VBO_T);

		//glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_P);
		glBufferData(GL_ARRAY_BUFFER, v_vbo_size * sizeof(glm::vec3), 0, GL_STATIC_DRAW);
		for (int i = 0; i < objs; i++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, vertex_position[i] * sizeof(glm::vec3), vertex_count[i] * sizeof(glm::vec3), &vertices[i][0]);
			//prev_size = vertices[i - 1].size();
		}
		prev_size = 0;
		glBindBuffer(GL_ARRAY_BUFFER, VBO_N);
		glBufferData(GL_ARRAY_BUFFER, n_vbo_size * sizeof(glm::vec3), 0, GL_STATIC_DRAW);

		for (int i = 0; i < objs; i++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, vertex_position[i] * sizeof(glm::vec3), vertex_count[i] * sizeof(glm::vec3), &normals[i][0]);
			//prev_size = vertices[i - 1].size();
		}

		//glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
		//glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(texCoords), texCoords, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint positionID = shader.getAttribLocation("vertex_position");
		GLuint normalID = shader.getAttribLocation("vertex_normals");
		//GLuint textureID = shader.getAttribLocation("aTexCoord");

		glEnableVertexAttribArray(positionID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_P);
		glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(normalID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_N);
		glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, NULL);


		//glEnableVertexAttribArray(textureID);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO_T);
		//glVertexAttribPointer(textureID, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		/*// load and create a texture
		// -------------------------
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
		unsigned char *data = stbi_load("../Assets/textures/container.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);*/
	}

	ObjectHandler()
	{

	}

	void skyboxTex()
	{
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};


		// skybox VAO
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		// load textures
		// -------------
		//unsigned int cubeTexture = loadTexture("../Assets/textures/wall.jpg");

		std::vector<std::string> faces
		{
			/*"../Assets/textures/skybox/right.jpg",
			"../Assets/textures/skybox/left.jpg",
			"../Assets/textures/skybox/top.jpg",
			"../Assets/textures/skybox/bottom.jpg",
			"../Assets/textures/skybox/front.jpg",
			"../Assets/textures/skybox/back.jpg"*/

			"../Assets/textures/skybox/posx.jpg",
			"../Assets/textures/skybox/negx.jpg",
			"../Assets/textures/skybox/posy.jpg",
			"../Assets/textures/skybox/negy.jpg",
			"../Assets/textures/skybox/posz.jpg",
			"../Assets/textures/skybox/negz.jpg"
		};
		cubemapTexture = loadCubemap(faces);
	}

	unsigned int getCubemapTexture()
	{
		return cubemapTexture;
	}

	unsigned int getSkyboxVAO()
	{
		return skyboxVAO;
	}

	unsigned int getVAO()
	{
		return VAO;
	}
};