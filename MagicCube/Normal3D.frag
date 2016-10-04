#version 330

uniform sampler2D texture;
uniform sampler2D normal;

in vec3 color;
in vec2 texturePos;

out vec4 fColor;

void main()  
{
	fColor = texture2D(texture,texturePos) + texture2D(normal,texturePos) * 0.2;
}