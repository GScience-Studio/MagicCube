
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

	//读取文件
	FILE* infile = fopen(fullFileName.c_str(), "rb");

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

//windows size change event
void gl_manager::windowsSizeChangeListener(int width, int height)
{
	std::cout << width << "," << height << std::endl;

	_perspectiveLock.lock();

	_perspective = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1448.0f);

	_perspectiveLock.unlock();
}

//create window
void gl_manager::_loadWindow(const size_vec &windowSize,const char* appName)
{
	//load window
	_window = glfwCreateWindow(windowSize.getWidth(), windowSize.getHeight(), appName, nullptr, nullptr);

	if (!_window)
	{
		glfwTerminate();
		
		message("Couldn't load the window", msgError,true);
	}

	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 2);

	//set context
	glfwMakeContextCurrent(_window);

	if (_window == nullptr)
		message("[Error]Can't load an OpenGL window!Program will exit.", msgError, true);

	//set view port
	glViewport(0, 0, windowSize.getWidth(), windowSize.getHeight());

	//set perspective
	_perspective = glm::perspective(45.0f, (GLfloat)windowSize.getWidth() / (GLfloat)windowSize.getHeight(), 0.1f, 500.0f);

#ifndef _DEBUG
	//set vertical retrace
	glfwSwapInterval(1);
#endif

	//init glew
	glewInit();

	//init opengl state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifndef _DEBUG
	glEnable(GL_CULL_FACE);
#endif
}
//load shaders
render_program* gl_manager::bindShader(char* vert, char* frag, render_program* renderProgramClass)
{
	shader_info shaderInfo[] = {
		{ GL_VERTEX_SHADER, vert },
		{ GL_FRAGMENT_SHADER, frag },
		{ GL_NONE, NULL } };

	//load shader
	renderProgramClass->_programID = loadShader(shaderInfo);
	renderProgramClass->_projection = glGetUniformLocation(renderProgramClass->_programID, "projection");

	renderProgramClass->_init();

	_renderProgramList.push_front(renderProgramClass);

	return renderProgramClass;
}
render_program* gl_manager::bindShader(char* vert, char* frag, char* gs, render_program* renderProgramClass)
{
	shader_info shaderInfo[] = {
		{ GL_VERTEX_SHADER, vert },
		{ GL_FRAGMENT_SHADER, frag },
		{ GL_GEOMETRY_SHADER, gs},
		{ GL_NONE, NULL } };

	//load shader
	renderProgramClass->_programID = loadShader(shaderInfo);
	renderProgramClass->_projection = glGetUniformLocation(renderProgramClass->_programID, "projection");

	renderProgramClass->_init();

	_renderProgramList.push_front(renderProgramClass);

	return renderProgramClass;
}
void render_program::_setCamera(camera globalCamera, camera modelLocation)
{
	gl_manager::getInstance().useShaderProgram(_programID);

	glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(-globalCamera.getLocation()->getX(), -globalCamera.getLocation()->getY(), -globalCamera.getLocation()->getZ()));
	glm::mat4 cameraRotate = glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 cameraModelTranslate = glm::translate(glm::mat4(), glm::vec3(modelLocation.getLocation()->getX(), modelLocation.getLocation()->getY(), modelLocation.getLocation()->getZ()));
	glm::mat4 cameraModelRotate = glm::rotate(glm::mat4(), modelLocation.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), modelLocation.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(gl_manager::getInstance().getPerspective() * cameraRotate * cameraTranslate * cameraModelTranslate * cameraModelRotate));
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
	/* 读取PNG_BYTES_TO_CHECK个字节的数据 */
	temp = fread(buf, 1, PNG_BYTES_TO_CHECK, fp);
	/* 若读到的数据并没有PNG_BYTES_TO_CHECK个字节 */
	if (temp < PNG_BYTES_TO_CHECK) 
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}
	/* 检测数据是否为PNG的签名 */
	temp = png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK);
	/* 如果不是PNG的签名，则说明该文件不是PNG文件 */
	if (temp != 0) 
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		return false;
	}

	/* 复位文件指针 */
	rewind(fp);
	/* 开始读文件 */
	png_init_io(png_ptr, fp);
	/* 读取PNG图片信息 */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
	/* 获取图像的色彩类型 */
	color_type = png_get_color_type(png_ptr, info_ptr);
	/* 获取图像的宽高 */
	image.width = png_get_image_width(png_ptr, info_ptr);
	image.height = png_get_image_height(png_ptr, info_ptr);
	/* 获取图像的所有行像素数据，row_pointers里边就是rgba数据 */
	row_pointers = png_get_rows(png_ptr, info_ptr);
	/* 根据不同的色彩类型进行相应处理 */

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

texture* gl_manager::genTexture(const char* fileName[], GLuint count)
{
	texture* newTexture = new texture();

	newTexture->_textureCount	= count;
	newTexture->_textureIDList	= new GLuint[count];

	glGenTextures(count, newTexture->_textureIDList);

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
			glBindTexture(GL_TEXTURE_2D, newTexture->_textureIDList[i]);

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
	_textureList.push_front(newTexture);

	return newTexture;
}

void gl_manager::_refreshQueue()
{
	//check weather is zero(no matter if the data it returned is wrong)
	if (_renderQueue.size() == 0)
		return;

	_renderQueueLock.lock();

	double startRefreshTime = glfwGetTime();

	//loop to finish task
	while (glfwGetTime() - startRefreshTime <= 0.016 && _renderQueue.size() != 0)
	{
		gl_render_command getRenderCommand = _renderQueue.front();

		switch (getRenderCommand.commandType)
		{
		case gl_render_command::COMMAND_SET_BUFFER_DATA:
		{
			command_set_buffer_data* commandSetBufferData = ((command_set_buffer_data*)getRenderCommand.data);

			bufferData(*commandSetBufferData->inBuffer, commandSetBufferData->differentBufferDataPos, commandSetBufferData->size, commandSetBufferData->data, commandSetBufferData->shaderProgram);

			free(commandSetBufferData->data);
			delete (commandSetBufferData);

			break;
		}
		}
		//remove it
		_renderQueue.pop();
	}

	_renderQueueLock.unlock();
}