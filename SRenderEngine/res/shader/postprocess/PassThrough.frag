#version 430 core

// input and output
in vec2 texCoord;
out vec4 FinalColor;

// gbuffer
uniform sampler2D colorTexture;
uniform sampler2D ssrTexture;


void main()
{
	vec4 baseColor = texture(colorTexture, texCoord);
	vec4 ssrColor = texture(ssrTexture,texCoord);

	float luminance = (ssrColor.r + ssrColor.g + ssrColor.b)/3.0;
	float factor = 1;
	// if(luminance > 0.3) factor = 1;
	// else factor = 0.2; 

	vec3 color = vec3(baseColor + 0.8 * ssrColor).rgb;
	
	FinalColor = vec4(color, 1.0f);
}
