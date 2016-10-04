#version 330

uniform sampler2D texture;
uniform sampler2D normal;

in vec3 color;
in vec2 texturePos;

out vec4 fColor;

void main()  
{
	fColor = vec4(texturePos,0.0,0.0);
	fColor = texture2D(texture,texturePos);
}