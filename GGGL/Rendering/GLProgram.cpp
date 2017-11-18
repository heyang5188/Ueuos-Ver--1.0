#include "GLProgram.h"
#include <cstdlib>

namespace Ueuos {
	GLProgram::GLProgram(const char * vertexShader, const char * fragShader)
	{
		GLuint program = glCreateProgram();
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
		glDeleteShader(vshader);
		glDeleteShader(fshader);
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