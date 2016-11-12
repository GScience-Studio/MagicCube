#version 330

uniform sampler2D texture;
uniform sampler2D depthMap;
uniform sampler2D normal;

out vec4 fColor;
float height_scale = -0.55;

in GS_OUT
{
   vec2 texturePos;
   vec2 textureSizeLimit[2];
   vec3 lightPos;
   vec3 eyesPos;
}gs_out;

vec3 expand(vec3 v)
{
	return (v-0.5) * 2.0;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    // number of depth layers
	
    const float minLayers = 10.0;
    const float maxLayers = 50.0;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.yx / viewDir.z * height_scale; 
    vec2 deltaTexCoords = P / numLayers;
  
    // get initial values
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture2D(depthMap, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords -= deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture2D(depthMap, currentTexCoords).r;  
        // get depth of next layer
        currentLayerDepth += layerDepth;  
    }
    
    // -- parallax occlusion mapping interpolation from here on
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture2D(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}


void main()
{
	vec3 normalizeEyesPos = gs_out.eyesPos;

	normalizeEyesPos = normalize(gs_out.eyesPos);
		
    vec2 texCoords = ParallaxMapping(gs_out.texturePos,  normalizeEyesPos);

	if(texCoords.x < gs_out.textureSizeLimit[0].x || texCoords.y < gs_out.textureSizeLimit[0].y || texCoords.x > gs_out.textureSizeLimit[1].x || texCoords.y > gs_out.textureSizeLimit[1].y)
       discard;
	
	fColor = texture2D(texture,texCoords);
	
	if (fColor.a < 0.5f)
	{
		//discard;
		
		//return;
	}
	vec3 normalColor = texture2D(normal, texCoords).xyz;
	vec3 normal = expand(normalColor);

	float diffuse = clamp(dot(normal,gs_out.lightPos), 0.0, 1.0);
	
	fColor *= vec4(min(vec3(0.0,0.0,0.0) + vec3(1.0,1.0,1.0) * diffuse, vec3(1.0)),1.0);
	//fColor = vec4(normalizeEyesPos,1.0);
}