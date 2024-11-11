#ifndef OBJECT_HPP
# define OBJECT_HPP

#include "./main.h"

class Object {
	private:
		glm::mat4	_model;
		GLuint	_VAO;
		GLuint	_VBO;
		std::vector<glm::vec3>	_vertexBuffer;
	public:
		Object(std::vector<glm::vec3> vertex);
		GLuint	getVAO();
		GLuint	getVBO();
		glm::mat4 getModel();

};

#endif