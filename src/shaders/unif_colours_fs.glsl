#version 330

uniform vec3 baseColour;

out vec4 outputColor;

void main() {
	outputColor = vec4(baseColour, 1.0);
}