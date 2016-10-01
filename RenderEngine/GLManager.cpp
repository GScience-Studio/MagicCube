
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

//��ȡShader����
const char* readShader(const char* FileName)
{
	//��ȡ�ļ�
	FILE* infile = fopen(FileName, "rb");

	//�Ƿ��ȡ
	if (!infile)
	{
		return NULL;
	}

	//���ö�ȡλ��
	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	//��ȡ����
	GLchar* source = new GLchar[len + 1];

	//��ȡ���ر�
	fread(source, 1, len, infile);
	fclose(infile);

	//�����
	source[len] = 0;

	//����
	return const_cast<const GLchar*>(source);
}

//����һ��shader
GLuint loadShader(shader_info* Shaders)
{
	//����Ƿ�Ϊ��
	if (Shaders == NULL)
	{
		return 0;
	}

	//������ɫ������
	GLuint Program = glCreateProgram();

	shader_info* Entry = Shaders;

	//ѭ��������ɫ��
	while (Entry->Type != GL_NONE)
	{
		//����Shader
		GLuint Shader = glCreateShader(Entry->Type);

		//��ȡShader����
		const GLchar* Source = readShader(Entry->FileName);

		//�������Ƿ�Ϊ��
		if (Source == NULL)
		{
			//ɾ��Shader
			for (Entry = Shaders; Entry->Type != GL_NONE; ++Entry)
			{
				glDeleteShader(Shader);
			}
			return 0;
		}

		//��Դ��
		glShaderSource(Shader, 1, &Source, NULL);
		delete[] Source;

		//����Դ��
		glCompileShader(Shader);

		//��ȡ����״̬
		GLint compiled;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &compiled);

		//����������
		if (!compiled)
		{
			//��ȡ�������
			GLsizei len;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(Shader, len, &len, log);
			std::cerr << "[ERROR]Shader compilation failed: " << log << std::endl;
			delete[] log;

			return 0;
		}

		//��Shader����ɫ������
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