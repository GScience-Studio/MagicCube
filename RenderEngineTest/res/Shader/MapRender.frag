#version 330

uniform sampler2D texture;
uniform sampler2D normal;

out vec4 fColor;
in vec2 texturePos;

void main()  
{
	fColor = texture2D(texture,texturePos) + texture2D(normal,texturePos) * 0.1;
	fColor = vec4(1.0,0.0,0.0,1.0);
}