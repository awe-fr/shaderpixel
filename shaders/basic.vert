#version 430 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 textureUV;
layout(location = 2) in vec2 Normal;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

out vec4 col;
out vec2 UV;

vec4 colors[3] = vec4[3](vec4(1, 0, 0, 1),vec4(0, 1, 0, 1),vec4(0, 0, 1, 1));

void main() {
	mat4 MVP = Projection * View * Model;
	gl_Position = MVP * vec4(vertex, 1);
	col = colors[gl_VertexID % 3];
	UV = textureUV;
}