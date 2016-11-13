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
	
	uint posX = blockLocation / 50u;
	uint posZ = blockLocation - posX * 50u;
	uint posY = 0u;
	
	gl_Position = uvec4(posX - 25u,posY,posZ - 25u,1.0f);
	//gl_Position = uvec4(0.0,0.0,0.0,1.0f);
}