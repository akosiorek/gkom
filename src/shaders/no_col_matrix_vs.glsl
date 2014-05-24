#version 330

layout(location = 0) in vec4 position;
uniform mat4 perspectiveMatrix;

void main() {

	gl_Position = perspectiveMatrix * position;
}
