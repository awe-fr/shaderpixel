#version 430 core

layout(location = 0) in vec3 vertex;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

void main() {
	mat4 MVP = Projection * View * Model;
	gl_Position = MVP * vec4(vertex, 1);
}