#version 330 core

#define HIDE_TOP		0x01u
#define HIDE_DOWM		0x02u
#define HIDE_LEFT		0x04u
#define HIDE_RIGHT		0x08u
#define HIDE_BACK		0x10u
#define HIDE_FRONT		0x20u

#define GET_LIGHT_UP float(vs_out[0].nearbyBlockInfo << 20 >> 28) / 15.0f
#define GET_LIGHT_DOWN float(vs_out[0].nearbyBlockInfo << 16 >> 28) / 15.0f
#define GET_LIGHT_LEFT float(vs_out[0].nearbyBlockInfo << 12 >> 28) / 15.0f
#define GET_LIGHT_RIGHT float(vs_out[0].nearbyBlockInfo << 8 >> 28) / 15.0f
#define GET_LIGHT_FRONT float(vs_out[0].nearbyBlockInfo << 4 >> 28) / 15.0f
#define GET_LIGHT_BACK float(vs_out[0].nearbyBlockInfo >> 28) / 15.0f

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
	vec3 lightColor;
}gs_out;

vec3 getLightDir(vec3 normal,vec3 tangent)
{
	vec3 n = normalize(normal);
	vec3 t = normalize(tangent);
	vec3 b = cross(n,t);
	
	vec3 v;
	
	v.x = dot(lightPos, t);
	v.y = dot(lightPos, b);
	v.z = dot(lightPos, n);
	
	return normalize(v);
}

vec4 getTexturePos(float blockTextureID)
{
	float texturePosX = float(vs_out[0].texturePos.x);
	float texturePosY = float(vs_out[0].texturePos.y);
	
	float texturePosY2 = texturePosY + 1;
	float texturePosX2 = texturePosX + 1;
	
	texturePosX /= 32.0f;
	texturePosY /= 32.0f;
	
	texturePosX2 /= 32.0f;
	texturePosY2 /= 32.0f;
	
	return vec4(texturePosX,texturePosY,texturePosX2,texturePosY2);
}
void drawBlockUp(vec3 position, float blockTextureID)
{
	vec4 texturePos = getTexturePos(blockTextureID);
	
	gs_out.lightColor = vec3(GET_LIGHT_UP,GET_LIGHT_UP,GET_LIGHT_UP);

	gs_out.lightPos = getLightDir(vec3(0.0,1.0,0.0),vec3(0.0,0.0,-1.0));

	gl_Position = vec4(position + vec3(0.0f,1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[3]);
	EmitVertex();

	gl_Position = vec4(position + vec3(0.0f,1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[1]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(1.0f,1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[1]);
	EmitVertex();
	EndPrimitive();
}
void drawBlockDown(vec3 position, float blockTextureID)
{
	vec4 texturePos = getTexturePos(blockTextureID);
	
	gs_out.lightColor = vec3(GET_LIGHT_DOWN,GET_LIGHT_DOWN,GET_LIGHT_DOWN) * 0.7;
	
	gs_out.lightPos = getLightDir(vec3(0.0,-1.0,0.0),vec3(0.0,0.0,1.0));
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[3]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[1]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[3]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[1]);
	EmitVertex();
	
	EndPrimitive();
}

void drawBlockBack(vec3 position, float blockTextureID)
{
	vec4 texturePos = getTexturePos(blockTextureID);

	gs_out.lightColor = vec3(GET_LIGHT_BACK,GET_LIGHT_BACK,GET_LIGHT_BACK);
	
	gs_out.lightPos = getLightDir(vec3(1.0,0.0,0.0),vec3(0.0,0.0,1.0));

	gl_Position = vec4(position + vec3(0.0f,1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[3]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[1]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(0.0f,1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[3]);
	EmitVertex();
		
	gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[1]);
	EmitVertex();
	EndPrimitive();
}

void drawBlockFront(vec3 position, float blockTextureID)
{
	vec4 texturePos = getTexturePos(blockTextureID);

	gs_out.lightColor = vec3(GET_LIGHT_FRONT,GET_LIGHT_FRONT,GET_LIGHT_FRONT) * 0.7;
	
	gs_out.lightPos = getLightDir(vec3(-1.0,0.0,0.0),vec3(0.0,0.0,-1.0));

	gl_Position = vec4(position + vec3(1.0f,1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[1]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[1]);
	EmitVertex();
	
	EndPrimitive();
}
void drawBlockLeft(vec3 position, float blockTextureID)
{
	vec4 texturePos = getTexturePos(blockTextureID);

	gs_out.lightColor = vec3(GET_LIGHT_LEFT,GET_LIGHT_LEFT,GET_LIGHT_LEFT);
	
	gs_out.lightPos = getLightDir(vec3(0.0,0.0,1.0),vec3(-1.0,1.0,0.0));

	gl_Position = vec4(position + vec3(0.0f,1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,1.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[1]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,0.0f,0.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[1]);
	EmitVertex();
	
	EndPrimitive();
}

void drawBlockRight(vec3 position, float blockTextureID)
{
	vec4 texturePos = getTexturePos(blockTextureID);

	gs_out.lightColor = vec3(GET_LIGHT_RIGHT,GET_LIGHT_RIGHT,GET_LIGHT_RIGHT) * 0.7;
	
	gs_out.lightPos = getLightDir(vec3(0.0,0.0,-1.0),vec3(1.0,-1.0,0.0));

	gl_Position = vec4(position + vec3(0.0f,1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(0.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[0],texturePos[1]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,1.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[3]);
	EmitVertex();
	
	gl_Position = vec4(position + vec3(1.0f,0.0f,1.0f), 1.0f) * projection;
	gs_out.texturePos = vec2(texturePos[2],texturePos[1]);
	EmitVertex();
	
	EndPrimitive();
}

void renderBlock(vec3 position,float blockTextureID)
{
	//up
	if ((vs_out[0].nearbyBlockInfo & HIDE_TOP) == 0u)
	{
		drawBlockUp(position, blockTextureID);
	}
	
	//down
	if ((vs_out[0].nearbyBlockInfo & HIDE_DOWM) == 0u)
	{
		drawBlockDown(position, blockTextureID);
	}

	//back
	if ((vs_out[0].nearbyBlockInfo & HIDE_BACK) == 0u)
	{
		drawBlockBack(position, blockTextureID);
	}
	
	//front
	if ((vs_out[0].nearbyBlockInfo & HIDE_FRONT) == 0u)
	{
		drawBlockFront(position, blockTextureID);
	}
	
	//left
	if ((vs_out[0].nearbyBlockInfo & HIDE_LEFT) == 0u)
	{
		drawBlockLeft(position, blockTextureID);
	}
	
	//right
	if ((vs_out[0].nearbyBlockInfo & HIDE_RIGHT) == 0u)
	{
		drawBlockRight(position, blockTextureID);
	}
}
void main()
{
    gl_PointSize = gl_in[0].gl_PointSize;
	
	vec3 position = vec3(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y, gl_in[0].gl_Position.z);
	
    renderBlock(position,3);
}