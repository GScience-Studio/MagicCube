#version 330 core

uniform mat4 projection;

layout(points) in ;
layout(triangle_strip, max_vertices = 4) out;

void renderBlock(vec4 position)
{
    gl_Position = vec4(-1.0f, -1.0f, -position[1] / 1000.0f, 1.0f) * projection;
    EmitVertex();
    gl_Position = vec4(1.0f, -1.0f, -position[1] / 1000.0f, 1.0f) * projection;
    EmitVertex();
    gl_Position = vec4(-1.0f, 1.0f, -position[1] / 1000.0f, 1.0f) * projection;
	EmitVertex();
    gl_Position = vec4(1.0f, 1.0f, -position[1] / 1000.0f, 1.0f) * projection;
    EmitVertex();
    EndPrimitive();
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
    renderBlock(gl_in[0].gl_Position);
}