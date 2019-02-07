#version 330

in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 eyeDir;
out vec4 fragColor;


void main() { 

	float intensity = dot(lightDir,vertNormal);
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

	float silhouette = max(dot(vertNormal,normalize(-eyeDir.xyz)), 0.0);

	
	if (silhouette < 0.2){
		fragColor = color;	
	}else if (intensity > 0.95){
		fragColor = vec4(1.0, 0.5, 0.5, 1.0);
	}else if (intensity > 0.5){
		fragColor = vec4(0.6, 0.3, 0.3, 1.0);
	}else if (intensity > 0.25){
		fragColor = vec4(0.4, 0.2, 0.2, 1.0);
	}else{
		fragColor = vec4(0.2, 0.1, 0.1, 1.0);
	}
} 