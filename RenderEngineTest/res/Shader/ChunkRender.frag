#version 330

uniform sampler2D texture;
uniform sampler2D depthMap;
uniform sampler2D normal;

out vec4 fColor;

in GS_OUT
{
	vec2 texturePos;
	//vec2 textureSizeLimit[2];
	//vec3 lightPos;
	vec3 lightColor;
}gs_out;

vec3 expand(vec3 v)
{
	return (v-0.5f) * 2.0f;
}

void main()
{
	vec3 lightColor = min((1.0f - gs_out.lightColor) * 0.3f + gs_out.lightColor, vec3(1.0f));
	
	vec2 texCoords = gs_out.texturePos;
	
	fColor = texture2D(texture,texCoords);
	
	if (fColor.a < 0.5f)
	{
		discard;
		
		return;
	}
	
	fColor *= vec4(lightColor, 1.0f);
	/*
	vec3 normalColor = texture2D(normal, texCoords).xyz;
	vec3 normal = expand(normalColor);

	float diffuse = clamp(dot(normal,gs_out.lightPos), 0.01f, 1.0f);
	
	fColor *= vec4(min(lightColor * 0.6 + lightColor * diffuse, vec3(1.0f)),1.0f);
	*/
	//fColor = vec4(lightColor, 1.0f);
}