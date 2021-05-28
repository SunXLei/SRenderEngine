#version 400 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;
out vec4 FragPosLightSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
	fragPos = vec3(model * vec4(aPos, 1.0));
	normal = normalize(transpose(inverse(mat3(model))) * aNormal);
	texCoords = aTexCoords;
	FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}