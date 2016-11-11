#version 330

uniform sampler2D texture;
uniform sampler2D normal;

out vec4 fColor;

in GS_OUT
{
   vec2 texturePos;
   mat3 TBN;
}gs_out;

vec3 expand(vec3 v)
{
	return (v-0.5) * 2.0;
}

void main()
{	
	vec3 lightPos = normalize(vec3(-1.0,1.0,0.6)) * gs_out.TBN;
	
	fColor = texture2D(texture,gs_out.texturePos);
	
	if (fColor.a < 0.5f)
	{
		discard;
		
		return;
	}
	vec3 normalColor = texture2D(normal, gs_out.texturePos).xyz;
	vec3 normal = expand(normalColor);

	float diffuse = max(0.2,dot(normal,lightPos));
	
	fColor *= vec4(min(vec3(0.0,0.0,0.0) + vec3(1.0,1.0,1.0) * diffuse, vec3(1.0)),1.0);
}