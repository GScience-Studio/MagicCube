#version 330

layout(location = 0) in uint 	fblockID;
layout(location = 1) in uint 	fblockLocation;
layout(location = 2) in uint 	fnearbyBlockInfo;

out VS_OUT
{
   uvec2 texturePos;
   uint  nearbyBlockInfo;
}vs_out;

void  main()
{
	uint blockID = uint(fblockID);
	uint blockLocation = fblockLocation;
	
	vs_out.texturePos.y = blockID / 32u;
	vs_out.texturePos.x = blockID - vs_out.texturePos.y * 32u;
	
	vs_out.nearbyBlockInfo = fnearbyBlockInfo;
	
	uint posX = blockLocation / 16u;
	uint posZ = blockLocation - posX * 16u;
	uint posY = 0u;
	
	gl_Position = uvec4(posX,posY,posZ,1.0f);
	//gl_Position = uvec4(0.0,0.0,0.0,1.0f);
}