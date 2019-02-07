#version 330

in vec4 vVertex;
in vec3 vNormal;
in vec2 texCoords;

out vec4 vNoise;
out float intensity;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightDir;
uniform sampler3D tNoise;
uniform float elapsedTime;

void main()
{
	vec3 newVNormal;
	newVNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	vec3 lightPos = normalize(lightDir - eyePos.xyz); /// Create the light direction


	//vNoise = normalize(vec3(texture(tNoise, newVNormal.xyz + elapsedTime * 0.4)));

	//get texture vector
	vNoise = texture(tNoise, vVertex.xyz);

	//vec3(texture(tNoise, newVNormal.xyz + elapsedTime * 0.4));

	//get intensity
	intensity = vNoise[0] + vNoise[1] + vNoise[2];
	

	vec3 offset = newVNormal.xyz * dot(newVNormal, vNoise.xyz) * 1.15;


	gl_Position =  projectionMatrix * modelViewMatrix * (vVertex + vec4(newVNormal * elapsedTime,1)); 
}