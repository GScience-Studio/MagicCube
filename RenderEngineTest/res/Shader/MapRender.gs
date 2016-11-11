#version 330 core

uniform mat4 projection;

layout(points) in ;
layout(triangle_strip, max_vertices = 24) out;

in VS_OUT
{
   uvec2 texturePos;
}vs_out[];

out GS_OUT
{
   vec2 texturePos;
   mat3 TBN;
}gs_out;

void renderBlock(vec3 position,float blockTextureID)
{
	float texturePosX = float(vs_out[0].texturePos.x);
	float texturePosY = float(vs_out[0].texturePos.y);
	
	float texturePosY2 = texturePosY + 1;
	float texturePosX2 = texturePosX + 1;
	
	texturePosX /= 32.0f;
	texturePosY /= 32.0f;
	
	texturePosX2 /= 32.0f;
	texturePosY2 /= 32.0f;
	
	//up
	vec3 vertexNormal_cameraspace = normalize(vec3(0.0,1.0,0.0));
    vec3 vertexTangent_cameraspace = normalize(vec3(1.0,0.0,0.0));
    vec3 vertexBitangent_cameraspace = normalize(vec3(0.0,0.0,1.0));

	gs_out.TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));
	
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
	
	//down
	vertexNormal_cameraspace = normalize(vec3(0.0,-1.0,0.0));
    vertexTangent_cameraspace = normalize(vec3(-1.0,0.0,0.0));
    vertexBitangent_cameraspace = normalize(vec3(0.0,0.0,-1.0));

	gs_out.TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));
	
	gl_Position = vec4(position + vec3(0.0f,-1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,-1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,-1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,-1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY);
	EmitVertex();
	EndPrimitive();

	//back
	vertexNormal_cameraspace = normalize(vec3(0.0,0.0,-1.0));
    vertexTangent_cameraspace = normalize(vec3(0.0,-1.0,0.0));
    vertexBitangent_cameraspace = normalize(vec3(-1.0,0.0,0.0));

	gs_out.TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,-1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,-1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY);
	EmitVertex();
	EndPrimitive();
	
	//toward
	vertexNormal_cameraspace = normalize(vec3(0.0,0.0,1.0));
    vertexTangent_cameraspace = normalize(vec3(0.0,1.0,0.0));
    vertexBitangent_cameraspace = normalize(vec3(1.0,0.0,0.0));

	gs_out.TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));
	
	gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,-1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,-1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY);
	EmitVertex();
	EndPrimitive();
	
	//left
	vertexNormal_cameraspace = normalize(vec3(-1.0,0.0,0.0));
    vertexTangent_cameraspace = normalize(vec3(0.0,0.0,-1.0));
    vertexBitangent_cameraspace = normalize(vec3(0.0,-1.0,0.0));

	gs_out.TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,-1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,-1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY);
	EmitVertex();
	EndPrimitive();
	
	//right
	vertexNormal_cameraspace = normalize(vec3(1.0,0.0,0.0));
    vertexTangent_cameraspace = normalize(vec3(0.0,0.0,1.0));
    vertexBitangent_cameraspace = normalize(vec3(0.0,1.0,0.0));

	gs_out.TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    ));
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(0.0f,-1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX,texturePosY);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY2);
	EmitVertex();
	gl_Position = vec4(position + vec3(1.0f,-1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePosX2,texturePosY);
	EmitVertex();
	EndPrimitive();
	
	
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
		
	vec3 position = vec3(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y, gl_in[0].gl_Position.z);

    renderBlock(position,3);
}