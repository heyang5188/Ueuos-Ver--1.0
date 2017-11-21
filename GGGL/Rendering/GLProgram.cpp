#include "GLProgram.h"
#include <cstdlib>
#include <stdio.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)


namespace Ueuos {
	GLProgram::GLProgram(const char * vertexShader, const char * fragShader):program(0)
	{
		program = 0;
		program = glCreateProgram();
		GLuint vshader = genShader(vertexShader, ShaderType::SHADER_TYPE_VERTEX);
		GLuint fshader = genShader(fragShader, ShaderType::SHADER_TYPE_FRAGMENT);
		
		glAttachShader(program, vshader);
		glAttachShader(program, fshader);

		glLinkProgram(program);
		GLint linkPass;
		glGetProgramiv(program, GL_LINK_STATUS, &linkPass);
		GLchar info[512] = { 0 };
		if (!linkPass)
		{
			glGetProgramInfoLog(program, 512, NULL, info);
		}
		CHECK_GL_ERROR_DEBUG();
		//glDeleteShader(vshader);
		//glDeleteShader(fshader);
	}

	GLuint GLProgram::genShader(const char * source, ShaderType type)
	{
		GLuint shader = 0;
		switch (type)
		{
		case Ueuos::ShaderType::SHADER_TYPE_VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Ueuos::ShaderType::SHADER_TYPE_FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			break;
		}
		glShaderSource(shader,1,&source,NULL);
		glCompileShader(shader);
		GLint compileStatus;
		GLchar info[512] = { 0 };
		glGetShaderiv(shader,GL_COMPILE_STATUS,&compileStatus);

		if (!compileStatus)
		{
			glGetShaderInfoLog(shader, 512, NULL, info);
			return 0;
		}

		return shader;
	}
}