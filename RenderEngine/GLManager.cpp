
#define PNG_BYTES_TO_CHECK 4

#include "GLManager.h"

//libpng
#include <libPNG\png.h>

//glm
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//instance
gl_manager gl_manager::_glInstance;

//shader info
typedef struct
{
	GLenum       Type;
	const char*  FileName;
	GLuint       Shader;
} shader_info;

typedef struct
{
	bool	hasAlpha;

	GLuint height;
	GLuint width;

	unsigned char* imageData;
} image_info;

//read Shader program
const char* readShader(const char* FileName)
{
	std::string fullFileName = std::string("res\\shader\\") + FileName;

	//��ȡ�ļ�
	FILE* infile = fopen(fullFileName.c_str(), "rb");

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
void gl_manager::_loadWindow(const size_vec &windowSize,const char* appName)
{
	//load window
	_window = glfwCreateWindow(windowSize.getHeight(), windowSize.getWidth(), appName, nullptr, nullptr);

	if (!_window)
	{
		glfwTerminate();
		
		message("Couldn't load the window", msgError,true);
	}

	//set context
	glfwMakeContextCurrent(_window);

	//set view port
	glViewport(0, 0, windowSize.getHeight(), windowSize.getWidth());

	//set vertical retrace
	glfwSwapInterval(1);

	//init glew
	glewInit();

	//init opengl state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}
//load shaders
shader_program* gl_manager::genShader(char* vert, char* frag, shader_program* newShaderProgramClass)
{
	shader_info shaderInfo[] = {
		{ GL_VERTEX_SHADER, vert },
		{ GL_FRAGMENT_SHADER, frag },
		{ GL_NONE, NULL } };

	//load shader
	newShaderProgramClass->_programID = loadShader(shaderInfo);
	newShaderProgramClass->_projection = glGetUniformLocation(newShaderProgramClass->_programID, "projection");

	newShaderProgramClass->_init();

	_shaderProgramList.push_front(newShaderProgramClass);

	return nullptr;
}

void shader_program::setCamera(camera& globalCamera,camera& modelLocation) const
{
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 500.0f);
	glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(globalCamera.getLocation()->getX(), -globalCamera.getLocation()->getY(), globalCamera.getLocation()->getZ()));
	glm::mat4 cameraRotate = glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 cameraModelTranslate = glm::translate(glm::mat4(), glm::vec3(-modelLocation.getLocation()->getX(), modelLocation.getLocation()->getY(), -modelLocation.getLocation()->getZ()));
	glm::mat4 cameraModelRotate = glm::rotate(glm::mat4(), modelLocation.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), modelLocation.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));


	glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(projection * cameraRotate * cameraTranslate * cameraModelTranslate * cameraModelRotate));
}

bool loadPNG(const char *filepath, image_info& image)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep* row_pointers;

	char buf[PNG_BYTES_TO_CHECK];
	unsigned int x, y, temp, color_type;

	std::string fullFileName = std::string("res\\texture\\") + filepath;

	fp = fopen(fullFileName.c_str(), "rb");

	if (fp == NULL) 
	{
		return false;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	info_ptr = png_create_info_struct(png_ptr);

	setjmp(png_jmpbuf(png_ptr));
	/* ��ȡPNG_BYTES_TO_CHECK���ֽڵ����� */
	temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
	/* �����������ݲ�û��PNG_BYTES_TO_CHECK���ֽ� */
	if (temp < PNG_BYTES_TO_CHECK) 
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}
	/* ��������Ƿ�ΪPNG��ǩ�� */
	temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
	/* �������PNG��ǩ������˵�����ļ�����PNG�ļ� */
	if (temp != 0) 
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}

	/* ��λ�ļ�ָ�� */
	rewind(fp);
	/* ��ʼ���ļ� */
	png_init_io(png_ptr, fp);
	/* ��ȡPNGͼƬ��Ϣ */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
	/* ��ȡͼ���ɫ������ */
	color_type = png_get_color_type(png_ptr, info_ptr);
	/* ��ȡͼ��Ŀ�� */
	image.width = png_get_image_width(png_ptr, info_ptr);
	image.height = png_get_image_height(png_ptr, info_ptr);
	/* ��ȡͼ����������������ݣ�row_pointers��߾���rgba���� */
	row_pointers = png_get_rows(png_ptr, info_ptr);
	/* ���ݲ�ͬ��ɫ�����ͽ�����Ӧ���� */

	switch (color_type)
	{
	case PNG_COLOR_TYPE_RGB_ALPHA:
	{
		image.imageData = new unsigned char[image.width * image.height * 4];
		image.hasAlpha = true;

		for (y = 0; y < image.height; ++y)
		{
			for (x = 0; x < image.width * 4; )
			{
				image.imageData[y * image.width * 4 + x] = row_pointers[y][x++];
				image.imageData[y * image.width * 4 + x] = row_pointers[y][x++];
				image.imageData[y * image.width * 4 + x] = row_pointers[y][x++];
				image.imageData[y * image.width * 4 + x] = row_pointers[y][x++];
			}
		}
		break;
	}
	case PNG_COLOR_TYPE_RGB:
	{
		image.imageData = new unsigned char[image.width * image.height * 4];
		image.hasAlpha = false;

		unsigned int total = 0;

		for (y = 0; y < image.height; ++y)
		{
			for (x = 0; x < image.width * 3; )
			{
				image.imageData[total++] = row_pointers[y][x++];
				image.imageData[total++] = row_pointers[y][x++];
				image.imageData[total++] = row_pointers[y][x++];
				image.imageData[total++] = 0;
			}
		}
	
		break;
	}
	default:
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}
	fclose(fp);

	png_destroy_read_struct(&png_ptr, &info_ptr, 0);

	return true;
}

texture gl_manager::genTexture(char* fileName[], GLuint count)
{
	texture texture;

	texture._textureCount	= count;
	texture._textureIDList	= new GLuint[count];

	glGenTextures(count, texture._textureIDList);

	for (unsigned int i = 0; i < count; i++)
	{
		image_info image;

		if (!loadPNG(fileName[i], image))
		{
			std::string errorMessage = "[Error]Can't load image call:";

			message((errorMessage + fileName[i]).c_str(), msgError, false);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, texture._textureIDList[i]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			if (image.hasAlpha)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.imageData);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.imageData);

			glBindTexture(GL_TEXTURE_2D, 0);

			delete[](image.imageData);
		}
	}
	_textureList.push_front(texture);

	return texture;
}