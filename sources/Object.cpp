#include "./../headers/Object.hpp"

Object::Object(const char *path) {
	parseModel(path);

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

bool	Object::parseModel(const char *path) {
	std::ifstream file(path, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Error : Imposible to open the file." << std::endl;
		return false;
	}

	std::string line;

	while (std::getline(file, line)) {
		if (!line.empty()) {
			std::vector<std::string> cut_line = split(line, ' ');
			if (cut_line.empty())
				continue;
			else if (cut_line[0] == "v" && cut_line.size() == 4) {
				try {
					glm::vec3 vertex(std::stof(cut_line[1]), std::stof(cut_line[2]), std::stof(cut_line[3]));
					this->_vertexBuffer.push_back(vertex);
				}
				catch (std::exception &e) {
					std::cerr << "Error : Wrong vertice." << std::endl;
					std::cerr << "	" << line << std::endl;
					return false;
				}
			}
			else if (cut_line[0] == "vt" && (cut_line.size() == 3 || cut_line.size() == 4)) {
				try {
					if (cut_line.size() == 4) {
						float test = std::stof(cut_line[3]);
						if (test != 0) {
							std::cerr << "Error : volumetric texture are not available." << std::endl;
							std::cerr << "	" << line << std::endl;
							return false;
						}
					}
					glm::vec2 vertex(std::stof(cut_line[1]), std::stof(cut_line[2]));
					this->_textureBuffer.push_back(vertex);
				}
				catch (std::exception &e) {
					std::cerr << "Error : Wrong texture coordinate." << std::endl;
					std::cerr << "	" << line << std::endl;
					return false;
				}
			}
			else if (cut_line[0] == "vn" && cut_line.size() == 4) {
				try {
					glm::vec3 vertex(std::stof(cut_line[1]), std::stof(cut_line[2]), std::stof(cut_line[3]));
					this->_normalBuffer.push_back(vertex);
				}
				catch (std::exception &e) {
					std::cerr << "Error : Wrong normal." << std::endl;
					std::cerr << "	" << line << std::endl;
					return false;
				}
			}
			else if (cut_line[0] == "f" && (cut_line.size() == 4 || cut_line.size() == 5)) {
				glm::vec3 vertTmp(0, 0, 0);
				glm::vec3 textTmp(0, 0, 0);
				glm::vec3 normTmp(0, 0, 0);
				for(int i = 0; i < 3; i++) {
					std::vector<std::string> infos = split(cut_line[i + 1], '/');
					if (infos.size() != 3) {
						std::cerr << "Error : Wrong index." << std::endl;
						std::cerr << "	" << line << std::endl;
						return false;
					}
					try {
						int vert = std::stoi(infos[0]);
						int text = std::stoi(infos[1]);
						int norm = std::stoi(infos[2]);
						if (vert > 0 && vert <= this->_vertexBuffer.size() && text > 0 && text <= this->_textureBuffer.size() && norm > 0 && norm <= this->_normalBuffer.size()) {
							if (i == 0) {
								vertTmp.x = vert;
								textTmp.x = text;
								normTmp.x = norm;
							}
							else if (i == 1) {
								vertTmp.y = vert;
								textTmp.y = text;
								normTmp.y = norm;
							}
							else {
								vertTmp.z = vert;
								textTmp.z = text;
								normTmp.z = norm;
							}
						}
						else {
							std::cerr << "Error : Wrong index." << std::endl;
							std::cerr << "	" << line << std::endl;
							return false;
						}
					}
					catch (std::exception &e) {
						std::cerr << "Error : Wrong index." << std::endl;
						std::cerr << "	" << line << std::endl;
						return false;
					}
				}
				this->_vertexIndex.push_back(vertTmp);
				this->_textureIndex.push_back(textTmp);
				this->_normalIndex.push_back(normTmp);
			}
		}
	}

	file.close();
	return true;
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

size_t	Object::getVBOSize() {
	return (this->_vertexBuffer.size());
}

std::vector<std::string> split(std::string line, char cut) {
	std::vector<std::string> ret;
	std::string new_line;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == cut) {
			if (!new_line.empty()) {
				ret.push_back(new_line);
				new_line.clear();
			}
			continue;
		}
		new_line += line[i];
	}
	if (new_line != "\n" && new_line != "\r")
		ret.push_back(new_line);
	return (ret);
}