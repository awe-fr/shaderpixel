#include "./../headers/Object.hpp"

Object::Object(std::vector<glm::vec3> vertex) : _vertexBuffer(vertex) {
	this->_model = glm::mat4(1);

	glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);

	glGenBuffers(1, &this->_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
	glBufferData(GL_ARRAY_BUFFER, this->_vertexBuffer.size() * sizeof(glm::vec3), &this->_vertexBuffer[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// glDisableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint	Object::getVAO() {
	return (this->_VAO);
}

GLuint	Object::getVBO() {
	return (this->_VBO);
}

glm::mat4 Object::getModel() {
	return (this->_model);
}