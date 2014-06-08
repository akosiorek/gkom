#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;

smooth out vec4 theColor;

uniform mat4 perspectiveMatrix;
uniform mat3 normalMatrix;
uniform vec3 baseColour;

uniform vec4 ambientLightIntensity;

void main() {

	gl_Position = perspectiveMatrix * position;	
	
	
	vec3 normCamSpace = normalize(mat3(perspectiveMatrix) * normal);	
	float cosAngIncidence = clamp(dot(normCamSpace, normalize(vec3(-1.0, .5, .5))), 0, 1);
	float cosAngIncidence2 = clamp(dot(normCamSpace, normalize(vec3(.7, -.5, -.5))), 0, 1);		
	theColor = (ambientLightIntensity + ambientLightIntensity * cosAngIncidence + ambientLightIntensity * cosAngIncidence2 * 0.2) * vec4(baseColour, 1.0);
}
