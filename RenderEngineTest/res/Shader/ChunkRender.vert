#version 330

layout(location = 0) in uint 	fblockInfo;
layout(location = 1) in uint 	fnearbyBlockInfo;

out VS_OUT
{
   uvec2 texturePos;
   uint  nearbyBlockInfo;
}vs_out;

void  main()
{
	uint blockLocation 	= fblockInfo << 20 >> 20;
	uint blockID 		= fblockInfo >> 12;
	
	vs_out.texturePos.y = blockID / 32u;
	vs_out.texturePos.x = blockID - vs_out.texturePos.y * 32u;
	
	vs_out.nearbyBlockInfo = fnearbyBlockInfo;
	
	uint posY = blockLocation / 256u;
	uint posX = (blockLocation - posY * 256u) / 16u;
	uint posZ = (blockLocation - posY * 256u) - posX * 16u;
	
	gl_Position = uvec4(posX,posY,posZ,1.0f);
	//gl_Position = uvec4(0.0,0.0,0.0,1.0f);
}