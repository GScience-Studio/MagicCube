#version 330  

layout(location = 0) in int in_position;

void  main()
{
	gl_Position = vec4(in_position,0.0f,0.0f,0.0f);
}