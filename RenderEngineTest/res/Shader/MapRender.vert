#version 330

layout(location = 0) in float fblockID;
layout(location = 1) in float fblockLocation;

out VS_OUT
{
   uvec2 texturePos;
}vs_out;

void  main()
{
	uint blockID = uint(fblockID);
	uint blockLocation = uint(fblockLocation);

	vs_out.texturePos.y = blockID / 32u;
	vs_out.texturePos.x = blockID - vs_out.texturePos.y * 32u;
	
	uint posX = blockLocation / 1024u;
	uint posZ = blockLocation - posX * 1024u;
	uint posY = 0u;
	
	gl_Position = uvec4(posX,posY,posZ,1.0f);
}