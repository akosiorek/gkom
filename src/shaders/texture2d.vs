#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec4 fragIntensity;
out vec2 fragCoord;

uniform mat4 gWVP;

uniform vec3 dirToLight;
uniform vec4 diffuseLightIntensity;
uniform vec4 ambientLightIntensity;


void main() {

	gl_Position = gWVP * position;		
	
	vec3 normCamSpace = normalize(mat3(gWVP) * normal);		
	float cosAngIncidence = clamp(dot(normCamSpace, dirToLight), 0, 1);		
	fragIntensity = ambientLightIntensity + diffuseLightIntensity * cosAngIncidence;

	fragCoord = texCoord;
}
