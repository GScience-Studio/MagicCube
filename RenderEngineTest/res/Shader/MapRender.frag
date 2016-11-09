#version 330

uniform sampler2D texture;
uniform sampler2D normal;

out vec4 fColor;

in GS_OUT
{
   vec2 texturePos;
}gs_out;

void main()  
{
	fColor = texture2D(texture,gs_out.texturePos) + texture2D(normal,gs_out.texturePos) * 0.1;
}