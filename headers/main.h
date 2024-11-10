#ifndef MAIN_H
# define MAIN_H

// define
# define WIDTH 1280
# define HEIGHT 720

// graphique includes
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/gtx/transform.hpp>

// standard includes
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

// file includes
# include "./WindowApp.hpp"
# include "./Player.hpp"

GLuint	LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif