#version 330 core

uniform mat4 projection;

layout(points) in ;
layout(triangle_strip, max_vertices = 4) out;

out GS_OUT
{
   vec2 texturePos;
}gs_out;

void renderBlock(vec3 position,float blockTextureID)
{
	float texturePosX = mod(blockTextureID,32.0f);
	float texturePosY = (blockTextureID - texturePosX) / 32.0f;
	
	float texturePosY2 = texturePosY + 1;
	float texturePosX2 = texturePosX + 1;
	
	texturePosX /= 32.0f;
	texturePosY /= 32.0f;
	
	texturePosX2 /= 32.0f;
	texturePosY2 /= 32.0f;
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY);
	EmitVertex();
	EndPrimitive();
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
	
	float posX = ceil(gl_in[0].gl_Position[1] / 1024);
	float posZ = ceil(gl_in[0].gl_Position[1] - posX * 1024);
	
	vec3 position = vec3(posX - 512.0f, -2.0f, posZ + 512.0f);
	
    renderBlock(position,3);
}