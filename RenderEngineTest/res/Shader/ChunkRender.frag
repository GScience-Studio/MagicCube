#version 330

uniform sampler2D texture;
uniform sampler2D depthMap;
uniform sampler2D normal;

out vec4 fColor;

in GS_OUT
{
	vec2 texturePos;
	vec2 textureSizeLimit[2];
	vec3 lightPos;
	vec3 lightColor;
}gs_out;

vec3 expand(vec3 v)
{
	return (v-0.5) * 2.0;
}

void main()
{
	vec2 texCoords = gs_out.texturePos;
	
	fColor = texture2D(texture,texCoords);
	
	if (fColor.a < 0.5f)
	{
		discard;
		
		return;
	}
	vec3 normalColor = texture2D(normal, texCoords).xyz;
	vec3 normal = expand(normalColor);

	float diffuse = clamp(dot(normal,gs_out.lightPos), 0.01, 1.0) / 1.0 * 0.7 + 0.3;
	
	fColor *= vec4(min(vec3(0.3,0.3,0.3) + gs_out.lightColor * diffuse, vec3(1.0)),1.0);
}