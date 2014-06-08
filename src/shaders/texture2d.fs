#version 330

in vec4 fragIntensity;
in vec2 fragCoord;

out vec4 outputColor;

uniform sampler2D gSampler;

void main() {
	outputColor = fragIntensity * texture2D(gSampler, fragCoord.xy);
}