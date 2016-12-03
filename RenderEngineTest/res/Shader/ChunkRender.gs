#version 330 core

#define HIDE_TOP		0x01u
#define HIDE_DOWM		0x02u
#define HIDE_LEFT		0x04u
#define HIDE_RIGHT		0x08u
#define HIDE_BACK		0x10u
#define HIDE_FRONT		0x20u

uniform mat4 projection;

layout(points) in ;
layout(triangle_strip, max_vertices = 24) out;

uniform vec3 lightPos;
uniform vec3 eyesPos;

in VS_OUT
{
   uvec2 texturePos;
   uint  nearbyBlockInfo;
}vs_out[];

out GS_OUT
{
   vec2 texturePos;
   vec2 textureSizeLimit[2];
   vec3 lightPos;
   vec3 eyesPos;
}gs_out;

void renderBlock(vec3 position,float blockTextureID)
{
	vec3 normalizeLightPos = vec3(0.0,0.0,0.0);
	
	if (lightPos != vec3(0.0,0.0,0.0))
		normalizeLightPos = normalize(lightPos);
	
	float texturePosX = float(vs_out[0].texturePos.x);
	float texturePosY = float(vs_out[0].texturePos.y);
	
	float texturePosY2 = texturePosY + 1;
	float texturePosX2 = texturePosX + 1;
	
	texturePosX /= 32.0f;
	texturePosY /= 32.0f;
	
	texturePosX2 /= 32.0f;
	texturePosY2 /= 32.0f;
	
	gs_out.textureSizeLimit[0] = vec2(texturePosX,texturePosY);
	gs_out.textureSizeLimit[1] = vec2(texturePosX2,texturePosY2);
	
	vec3 vertexNormal_cameraspace;
	vec3 vertexTangent_cameraspace;
	vec3 vertexBitangent_cameraspace;
	
	mat3 TBN;
	
	//up
	if ((vs_out[0].nearbyBlockInfo & HIDE_TOP) == 0u)
	{
		vertexNormal_cameraspace = normalize(vec3(0.0,1.0,0.0));
		vertexTangent_cameraspace = normalize(vec3(1.0,0.0,0.0));
		vertexBitangent_cameraspace = normalize(vec3(0.0,0.0,1.0));

		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		));
		
		gs_out.lightPos = normalizeLightPos * TBN;

		gs_out.eyesPos = abs((vec3(0.0f,0.0f,0.0f) + position - eyesPos)) * TBN;
		
		gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX,texturePosY2);
		EmitVertex();
		
		gs_out.eyesPos = abs((vec3(0.0f,0.0f,1.0f) + position - eyesPos)) * TBN;
		
		gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX2,texturePosY2);
		EmitVertex();
		
		gs_out.eyesPos = abs((vec3(1.0f,0.0f,0.0f) + position - eyesPos)) * TBN;
		
		gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX,texturePosY);
		EmitVertex();
		
		gs_out.eyesPos = abs((vec3(1.0f,0.0f,1.0f) + position - eyesPos)) * TBN;
		
		gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX2,texturePosY);
		EmitVertex();
		EndPrimitive();
	}
	
	//down
	if ((vs_out[0].nearbyBlockInfo & HIDE_DOWM) == 0u)
	{
		vertexNormal_cameraspace = normalize(vec3(0.0,-1.0,0.0));
		vertexTangent_cameraspace = normalize(vec3(-1.0,0.0,0.0));
		vertexBitangent_cameraspace = normalize(vec3(0.0,0.0,-1.0));

		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		));
		
		gs_out.lightPos = normalizeLightPos * TBN;

		gs_out.eyesPos = normalize(eyesPos - vec3(0.0f,-1.0f,0.0f) - position) * TBN;
		
		gl_Position = vec4(position + vec3(0.0f,-1.0f,0.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX,texturePosY2);
		EmitVertex();
		
		gs_out.eyesPos = normalize(eyesPos - vec3(1.0f,-1.0f,0.0f) - position) * TBN;
		
		gl_Position = vec4(position + vec3(1.0f,-1.0f,0.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX,texturePosY);
		EmitVertex();
		
		gs_out.eyesPos = normalize(eyesPos - vec3(0.0f,-1.0f,01.0f) - position) * TBN;
		
		gl_Position = vec4(position + vec3(0.0f,-1.0f,1.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX2,texturePosY2);
		EmitVertex();
		
		gs_out.eyesPos = normalize(eyesPos - vec3(1.0f,-1.0f,1.0f) - position) * TBN;
		
		gl_Position = vec4(position + vec3(1.0f,-1.0f,1.0f), 1.0f) * projection;
		gs_out.texturePos = vec2(texturePosX2,texturePosY);
		EmitVertex();
		EndPrimitive();
	}

	//back
	if ((vs_out[0].nearbyBlockInfo & HIDE_BACK) == 0u)
	{
		vertexNormal_cameraspace = normalize(vec3(0.0,0.0,-1.0));
		vertexTangent_cameraspace = normalize(vec3(0.0,-1.0,0.0));
		vertexBitangent_cameraspace = normalize(vec3(-1.0,0.0,0.0));

		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		));
		
		gs_out.lightPos = normalizeLightPos * TBN;

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
	}
	
	//front
	if ((vs_out[0].nearbyBlockInfo & HIDE_FRONT) == 0u)
	{
		vertexNormal_cameraspace = normalize(vec3(0.0,0.0,1.0));
		vertexTangent_cameraspace = normalize(vec3(0.0,1.0,0.0));
		vertexBitangent_cameraspace = normalize(vec3(1.0,0.0,0.0));

		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		));
		
		gs_out.lightPos = normalizeLightPos * TBN;

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
	}
	
	//left
	if ((vs_out[0].nearbyBlockInfo & HIDE_LEFT) == 0u)
	{
		vertexNormal_cameraspace = normalize(vec3(-1.0,0.0,0.0));
		vertexTangent_cameraspace = normalize(vec3(0.0,0.0,-1.0));
		vertexBitangent_cameraspace = normalize(vec3(0.0,-1.0,0.0));

		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		));
		
		gs_out.lightPos = normalizeLightPos * TBN;

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
	}
	
	//right
	if ((vs_out[0].nearbyBlockInfo & HIDE_RIGHT) == 0u)
	{
		vertexNormal_cameraspace = normalize(vec3(1.0,0.0,0.0));
		vertexTangent_cameraspace = normalize(vec3(0.0,0.0,1.0));
		vertexBitangent_cameraspace = normalize(vec3(0.0,1.0,0.0));

		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		));
		
		gs_out.lightPos = normalizeLightPos * TBN;

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
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
		
	vec3 position = vec3(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y, gl_in[0].gl_Position.z);

    renderBlock(position,3);
}