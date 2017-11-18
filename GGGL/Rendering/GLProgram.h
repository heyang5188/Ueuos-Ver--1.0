#pragma once

#include <GL/glew.h>

namespace Ueuos {
	enum class ShaderType {
		SHADER_TYPE_VERTEX,
		SHADER_TYPE_FRAGMENT,
	};

	class GLProgram {
	public:
		GLProgram(const char* vertexShader, const char* fragShader);
	private:
		GLuint genShader(const char* source, ShaderType type);

	private:
		GLuint program;
	};
}