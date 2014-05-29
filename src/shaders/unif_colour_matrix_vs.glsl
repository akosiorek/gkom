#version 330

layout(location = 0) in vec4 position;
uniform mat4 perspectiveMatrix;

uniform vec3 baseColour;

smooth out vec4 theColor;

void main() {

	gl_Position = perspectiveMatrix * position;
	theColor = vec4(baseColour, 1.0);
}
