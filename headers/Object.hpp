#ifndef OBJECT_HPP
# define OBJECT_HPP

#include "./main.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec2 tex;
	glm::vec3 norm;
};

class Object {
	private:
		glm::mat4	_model;

		GLuint	_VAO;
		GLuint	_VBO;
		GLuint	_IBO;

		std::vector<glm::vec3>	_vertexBuffer;
		std::vector<glm::vec2>	_textureBuffer;
		std::vector<glm::vec3>	_normalBuffer;

		std::vector<GLuint>	_vertexIndex;
		std::vector<GLuint>	_textureIndex;
		std::vector<GLuint>	_normalIndex;

		std::vector<Vertex> _VBOBuffer;
		std::vector<GLuint>	_IBOBuffer;
	public:
		Object(const char *path);
		GLuint	getVAO();
		GLuint	getVBO();
		glm::mat4 getModel();
		size_t	getVBOSize();
		size_t	getIBOSize();
		int	isExist(glm::vec3 Cpos, glm::vec2 Ctex, glm::vec3 Cnorm);
		bool	parseModel(const char *path);
		bool	subParseModel(std::string line, std::vector<std::string> cut_line);

		class wrongInit : public std::exception {
			public:
				virtual const char *what() const throw();
		};
};

std::vector<std::string>	split(std::string line, char cut);
Object	*askObject(const char *path);

#endif