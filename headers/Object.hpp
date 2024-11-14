#ifndef OBJECT_HPP
# define OBJECT_HPP

#include "./main.h"

class Object {
	private:
		glm::mat4	_model;
		GLuint	_VAO;
		GLuint	_VBO;
		std::vector<glm::vec3>	_vertexBuffer;
		std::vector<glm::vec2>	_textureBuffer;
		std::vector<glm::vec3>	_normalBuffer;
		std::vector<glm::vec3>	_vertexIndex;
		std::vector<glm::vec3>	_textureIndex;
		std::vector<glm::vec3>	_normalIndex;
	public:
		Object(const char *path);
		GLuint	getVAO();
		GLuint	getVBO();
		glm::mat4 getModel();
		size_t	getVBOSize();
		bool	parseModel(const char *path);
};

std::vector<std::string> split(std::string line, char cut);

#endif