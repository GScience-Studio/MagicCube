#version 330

uniform sampler2D texture;
uniform sampler2D normal;

in vec2 texturePos;

out vec4 fColor;

void main()  
{
	fColor = texture2D(texture,texturePos) + texture2D(normal,texturePos) * 0.1;
	fColor = vec4(1.0f,1.0f,0.0f,0.0f);
}