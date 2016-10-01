
#include "Application.h"
#include "GLManager.h"

//instance
gl_manager gl_manager::_glInstance;

//shader info
typedef struct
{
	GLenum       Type;
	const char*  FileName;
	GLuint       Shader;
} shader_info;

//读取Shader程序
const char* readShader(const char* FileName)
{
	//读取文件
	FILE* infile = fopen(FileName, "rb");

	//是否读取
	if (!infile)
	{
		return NULL;
	}

	//设置读取位置
	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	//读取数据
	GLchar* source = new GLchar[len + 1];

	//读取并关闭
	fread(source, 1, len, infile);
	fclose(infile);

	//最后处理
	source[len] = 0;

	//返回
	return const_cast<const GLchar*>(source);
}

//加载一个shader
GLuint loadShader(shader_info* Shaders)
{
	//检测是否为空
	if (Shaders == NULL)
	{
		return 0;
	}

	//创建着色器程序
	GLuint Program = glCreateProgram();

	shader_info* Entry = Shaders;

	//循环编译着色器
	while (Entry->Type != GL_NONE)
	{
		//创建Shader
		GLuint Shader = glCreateShader(Entry->Type);

		//读取Shader代码
		const GLchar* Source = readShader(Entry->FileName);

		//检测代码是否为空
		if (Source == NULL)
		{
			//删除Shader
			for (Entry = Shaders; Entry->Type != GL_NONE; ++Entry)
			{
				glDeleteShader(Shader);
			}
			return 0;
		}

		//绑定源码
		glShaderSource(Shader, 1, &Source, NULL);
		delete[] Source;

		//编译源码
		glCompileShader(Shader);

		//获取编译状态
		GLint compiled;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &compiled);

		//如果编译出错
		if (!compiled)
		{
			//获取错误并输出
			GLsizei len;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(Shader, len, &len, log);
			std::cerr << "[ERROR]Shader compilation failed: " << log << std::endl;
			delete[] log;

			return 0;
		}

		//绑定Shader到着色器程序
		glAttachShader(Program, Shader);

		++Entry;
	}
	glLinkProgram(Program);

	GLint linked;
	glGetProgramiv(Program, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(Program, len, &len, log);
		std::cerr << "[ERROR]Shader linking failed: " << log << std::endl;
		delete[] log;
		return 0;
	}
	glUseProgram(Program);

	return Program;
}

//create window
void gl_manager::_loadWindow()
{
	//get app instance
	application& appInstance = application::getInstance();

	//load window
	_window = glfwCreateWindow(appInstance._windowSize.getHeight(), appInstance._windowSize.getWidth(), appInstance._appName, nullptr, nullptr);

	if (!_window)
	{
		glfwTerminate();
		
		message("Couldn't load the window", msgError,true);
	}

	//set context
	glfwMakeContextCurrent(_window);

	//set view port
	glViewport(0, 0, appInstance._windowSize.getHeight(), appInstance._windowSize.getWidth());

	//set vertical retrace
	glfwSwapInterval(1);

	//init glew
	glewInit();
}
//load shaders
shader_program* gl_manager::addShader(char* vert, char* frag, shader_program* newShaderProgramClass)
{
	shader_info shaderInfo[] = {
		{ GL_VERTEX_SHADER, vert },
		{ GL_FRAGMENT_SHADER, frag },
		{ GL_NONE, NULL } };

	//load shader
	newShaderProgramClass->programID = loadShader(shaderInfo);

	_shaderProgramList.push_front(newShaderProgramClass);

	return nullptr;
}

//create buffer of normail 3d
void gl_manager::normail3DShader::createBuffer(const void* bufferData, const GLsizeiptr size, buffer& buffer) const
{
	glInstance.useBuffer(buffer);

	if (buffer.size >= size)
	{
		glInstance.bufferSubData(buffer, 0, size, bufferData);
	}
	else
	{
		glInstance.bufferData(buffer, size, bufferData);
	}
	if (!buffer.hasInit)
	{
		buffer.hasInit = true;

		//location data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		//color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//texture pos
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}
}