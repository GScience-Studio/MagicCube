#version 330

uniform sampler2D texture;

in vec3 color;
in vec2 texturePos;

out vec4 fColor;

void main()  
{
	fColor = texture2D(texture,texturePos);
	
	if (fColor.a < 0.5f)
	{
		discard;
		
		return;
	}
}