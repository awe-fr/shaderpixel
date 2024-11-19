#version 430 core

uniform sampler2D tex;

in vec4 col;
in vec2 UV;

out vec4 color;

void main() {
	color = texture(tex, UV);
}