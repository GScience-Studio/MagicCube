#version 330

in vec3 color;
in vec2 texturePos;

out vec4 fColor;

void main()  
{
	fColor=vec4(color,1.0);
}