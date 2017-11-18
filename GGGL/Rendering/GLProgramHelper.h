#pragma once

#include "GLProgram.h"
#include <string>
#include <map>


namespace Ueuos {
	using std::map;
	using std::string;
	const char* UNLIT_MVP_SHADER_VERTEX =
		"#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec4 color;\n"
		"uniform mat4 transform;\n"
		"uniform mat4 mvp;\n"
		"out vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"gl_Position = mvp*vec4(position.x, position.y, position.z, 1.0);\n"
		"vertexColor=color;"
		"}\0";
	const GLchar* UNLIT_MVP_SHADER_FRAGMENT =
		"#version 330 core\n"
		"out vec4 color;\n"
		"in  vec4 vertexColor;\n"
		"void main()\n"
		"{\n"
		"color = vertexColor;\n"
		"}\n\0";

	class GLProgramHelper {
	public:
		GLProgramHelper* getInstance();
	 	~GLProgramHelper();
		GLProgram* getProgramForName(string name);

		//glUniformBlock

	private:
		static GLProgramHelper* _instance;
		map<string, GLProgram*> programs;
	};
}