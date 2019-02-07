#version 330

in vec4 vNoise;
in float intensity;

out vec4 fragColor;

void main() 
{
	vec4 orange = vec4(0.8, 0.3, 0.0, 1.0);
	vec4 red = vec4(0.9, 0.0, 0.2, 1.0);

    fragColor = vec4(mix(orange, red, intensity));
}