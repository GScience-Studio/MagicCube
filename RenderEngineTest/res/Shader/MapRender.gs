#version 330 core

uniform mat4 projection;

layout(points) in ;
layout(triangle_strip, max_vertices = 4) out;

out GS_OUT
{
   vec2 texturePos;
}gs_out;

void renderBlock(vec3 position)
{
    gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(0.0f,1.0f);
    EmitVertex();
    gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(1.0f,1.0f);
    EmitVertex();
    gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(0.0f,0.0f);
	EmitVertex();
    gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(1.0f,0.0f);
    EmitVertex();
    EndPrimitive();
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
	float posX = ceil(gl_in[0].gl_Position[1] / 1024);
	float posY = ceil(gl_in[0].gl_Position[1] - posX * 1024);
	
	vec3 position = vec3(posX - 512.0f, -10.0f, posY + 512.0f);
	
    renderBlock(position);
}