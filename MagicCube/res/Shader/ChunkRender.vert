#version 330

#define getChunkBlockX(location) (location << 28 >> 28)
#define getChunkBlockY(location) (location << 24 >> 28)
#define getChunkBlockZ(location) (location << 20 >> 28)

layout(location = 0) in uint 	fblockInfo;
layout(location = 1) in uint 	fnearbyBlockInfo;

out VS_OUT
{
   uint  nearbyBlockInfo;
   uint	 blockID;
}vs_out;

void  main()
{
	uint blockLocation 	= fblockInfo << 20 >> 20;
	vs_out.blockID 		= fblockInfo >> 12;
	
	vs_out.nearbyBlockInfo = fnearbyBlockInfo;
	
	gl_Position = uvec4(getChunkBlockX(blockLocation),getChunkBlockY(blockLocation),getChunkBlockZ(blockLocation),1.0f);
}