#version 400 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D floorTexture;


void main()
{
	vec3 color = texture(floorTexture, texCoords).rgb;
	vec3 ambient, diffuse, specular;

	// ambient
	ambient = 0.05f * color; 

	// diffuse
	vec3 lightDir = normalize(lightPos - fragPos);
	float NdotL = max(dot(lightDir, normal), 0.0f);
	diffuse = color * NdotL;

	// specular;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 h = normalize(lightDir + viewDir);
	float NdotH = max(dot(normal,h), 0.0f);
	specular = vec3(0.3) * pow(NdotH, 32.0f);

	FragColor = vec4(ambient + diffuse + specular, 1.0f);
}
