#version 430 core

in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D displayTexture;

void main()
{             
    FragColor = vec4(texture(displayTexture, texCoords).rrr, 1.0f);
}