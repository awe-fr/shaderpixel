#define STB_IMAGE_IMPLEMENTATION

#include "./../headers/Object.hpp"
#include "./../headers/stb_image.h"

Object::Object(const char *path_obj, const char *path_text, short min_filter, short mag_filter, short wrap, bool flipped) {
	this->_model = glm::mat4(1);

	if (parseModel(path_obj) == false)
		throw wrongInit();

	if (parseTexture(path_text, min_filter, mag_filter, wrap, flipped) == false)
		throw wrongInit();

	glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);

	glGenBuffers(1, &this->_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->_VBO);
	glBufferData(GL_ARRAY_BUFFER, this->_VBOBuffer.size() * sizeof(Vertex), this->_VBOBuffer.data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &this->_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_IBOBuffer.size() * sizeof(GLuint), this->_IBOBuffer.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool	Object::parseTexture(const char *path, short min_filter, short mag_filter, short wrap, bool flipped) {
	if (flipped == 1)
		stbi_set_flip_vertically_on_load(1);
	
	int widthImg, heightImg, numColCh;
	unsigned char *bytes = stbi_load(path, &widthImg, &heightImg, &numColCh, 0);
	if (!bytes) {
		std::cerr << "Error : std failed to load texture." << std::endl;
		return (false);
	}

	glGenTextures(1, &this->_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->_texture);

	switch(min_filter) {
		case 0:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case 1:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case 2:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		case 3:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case 4:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			break;
		case 5:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		default:
			std::cerr << "Error : Wrong min filter parameter." << std::endl;
			return (false);
	}

	switch(mag_filter) {
		case 0:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case 1:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		default:
			std::cerr << "Error : Wrong mag filter parameter." << std::endl;
			return (false);
	}

	switch(wrap) {
		case 0:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			break;
		case 1:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
			break;
		case 2:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
			break;
		case 3:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
			break;
		case 4:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRROR_CLAMP_TO_EDGE);
			break;
		default:
			std::cerr << "Error : Wrong wrap texture parameter." << std::endl;
			return (false);
	}

	if (numColCh == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	else if (numColCh == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else {
		std::cerr << "Error : std failed detect channel." << std::endl;
		return (false);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);

	return (true);
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
				if(subParseModel(line, cut_line) == false)
					return false;
				if (cut_line.size() == 5) {
					cut_line[2] = cut_line[3];
					cut_line[3] = cut_line[4];
					if(subParseModel(line, cut_line) == false)
						return false;
				}
			}
		}
	}
	file.close();
	return (true);
}

bool	Object::subParseModel(std::string line, std::vector<std::string> cut_line) {
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
				int tmp = isExist(this->_vertexBuffer[vert - 1], this->_textureBuffer[text - 1], this->_normalBuffer[norm -1]);

				if (tmp == -1) {
					this->_IBOBuffer.push_back(this->_VBOBuffer.size());
					this->_VBOBuffer.push_back({this->_vertexBuffer[vert - 1], this->_textureBuffer[text - 1], this->_normalBuffer[norm - 1]});
				}
				else {
					this->_IBOBuffer.push_back(tmp);
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
	return (true);
}

int	Object::isExist(glm::vec3 Cpos, glm::vec2 Ctex, glm::vec3 Cnorm) {
	if (!this->_VBOBuffer.empty()) {
		for(int i = this->_VBOBuffer.size() - 1; i >= 0; i--) {
			if (this->_VBOBuffer[i].pos == Cpos && this->_VBOBuffer[i].tex == Ctex && this->_VBOBuffer[i].norm == Cnorm) {
				return (i);
			}
		}
	}
	return (-1);
}

GLuint	Object::getVAO() {
	return (this->_VAO);
}

GLuint	Object::getVBO() {
	return (this->_VBO);
}

GLuint	Object::getTexture() {
	return (this->_texture);
}

glm::mat4 Object::getModel() {
	return (this->_model);
}

size_t	Object::getVBOSize() {
	return (this->_VBOBuffer.size());
}

size_t	Object::getIBOSize() {
	return (this->_IBOBuffer.size());
}

const char *Object::wrongInit::what() const throw()
{
	return ("Init problem");
}

std::vector<std::string>	split(std::string line, char cut) {
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

void	askObject(const char *path_obj, const char *path_text, short min_filter, short mag_filter, short wrap, bool flipped) {
	ObjectList *lst = ObjectList::getInstance();
	try {
		Object	*obj = new Object(path_obj, path_text, min_filter, mag_filter, wrap, flipped);
		lst->add(obj);
		return ;
	}
	catch (std::exception &e) {
		return ;
	}
}