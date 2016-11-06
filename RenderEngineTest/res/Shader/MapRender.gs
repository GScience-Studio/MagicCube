#version 330  

uniform mat4 projection;

layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 gColor;
out vec2 texturePos;

void main()
{
	gl_Position = vec4(0.0,0.0,0.0,0.0);
	texturePos = vec2(0.0,0.0);
	gColor = vec3(1.0f,1.0f,1.0f);
	EmitVertex();

	gl_Position = vec4(0.0,1.0,0.0,0.0);
	texturePos = vec2(1.0,0.0);
	gColor = vec3(1.0f,1.0f,1.0f);
	EmitVertex();

	gl_Position = vec4(1.0,1.0,0.0,0.0);
	texturePos = vec2(0.0,1.0);
	gColor = vec3(1.0f,1.0f,1.0f);
	EmitVertex();

	EndPrimitive();
}