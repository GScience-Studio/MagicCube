#version 330 core

uniform mat4 projection;

layout(points) in ;
layout(triangle_strip, max_vertices = 4) out;

out GS_OUT
{
   vec2 texturePos;
}gs_out;

void renderBlock(vec4 position)
{
    gl_Position = vec4(-1.0f, -1.0f, -position[1] / 1000.0f, 1.0f) * projection;
	gs_out.texturePos = vec2(0.0f,1.0f);
    EmitVertex();
    gl_Position = vec4(1.0f, -1.0f, -position[1] / 1000.0f, 1.0f) * projection;
	gs_out.texturePos = vec2(1.0f,1.0f);
    EmitVertex();
    gl_Position = vec4(-1.0f, 1.0f, -position[1] / 1000.0f, 1.0f) * projection;
	gs_out.texturePos = vec2(0.0f,0.0f);
	EmitVertex();
    gl_Position = vec4(1.0f, 1.0f, -position[1] / 1000.0f, 1.0f) * projection;
	gs_out.texturePos = vec2(1.0f,0.0f);
    EmitVertex();
    EndPrimitive();
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
    renderBlock(gl_in[0].gl_Position);
}