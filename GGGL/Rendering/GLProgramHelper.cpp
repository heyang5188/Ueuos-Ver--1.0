#include "GLProgramHelper.h"
//#include <utility>
const char* UNLIT_MVP_SHADER_VERTEX =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec4 color;\n"
"uniform mat4 transform;\n"
"uniform mat4 pv;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = pv*transform*vec4(position.x, position.y, position.z, 1.0);\n"
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

namespace Ueuos {
	GLProgramHelper* GLProgramHelper::_instance = nullptr;

	GLProgramHelper* GLProgramHelper::getInstance() {
		if (_instance == nullptr)
		{
			_instance =new GLProgramHelper();
		}
		return _instance;
	}

	GLProgramHelper::~GLProgramHelper()
	{
		delete _instance;
		_instance = nullptr;
	}

	GLProgram* GLProgramHelper::getProgramForName(string name)
	{
		map<string, GLProgram*>::iterator it;
		it = programs.find(name);
		if (it!=programs.end())
		{
			return (*it).second;
		}
		return nullptr;
	}

	GLProgram GLProgramHelper::createTestShader()
	{
		return GLProgram(UNLIT_MVP_SHADER_VERTEX, UNLIT_MVP_SHADER_FRAGMENT);
	}

	GLProgramHelper::GLProgramHelper() {
		GLProgram* pro1 =  new GLProgram(UNLIT_MVP_SHADER_VERTEX,UNLIT_MVP_SHADER_FRAGMENT);
		programs.insert(std::pair<string,GLProgram*>(string("TEST"), pro1));
	}

}