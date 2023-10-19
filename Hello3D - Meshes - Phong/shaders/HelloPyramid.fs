#version 400

in vec3 finalColor;
in vec3 scaledNormal;
in vec2 texcoord;
in vec3 fragpos;

uniform float ka;
uniform float kd;
uniform float ks;
uniform float q;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec4 color;

void main()
{
	//Parcela ambiente
	vec3 ambient = ka * lightColor;

	//Parcela difusa
	vec3 N = normalize(scaledNormal);
	vec3 L = normalize(lightPos - fragpos);
	vec3 diffuse = kd * max(dot(N,L),0) * lightColor;

	//Parcela especular
	vec3 V = normalize(cameraPos - fragpos);
	vec3 R = normalize(reflect(-L,N));
	vec3 specular = ks * pow(max(dot(N,L),0),q) * lightColor;
	
	color = vec4((ambient + diffuse)* finalColor + specular,1.0);

}