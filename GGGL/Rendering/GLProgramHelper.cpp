#include "GLProgramHelper.h"

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

}