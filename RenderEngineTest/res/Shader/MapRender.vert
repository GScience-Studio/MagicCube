#version 330  

layout(location = 0) in float blockID;
layout(location = 0) in float blockLocation;

void  main()
{
	gl_Position = vec4(blockID,blockLocation,0.0f,0.0f);
}