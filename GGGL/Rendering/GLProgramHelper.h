#ifndef _GLPROGRAM_HELPER_H_
#define _GLPROGRAM_HELPER_H_


#include "GLProgram.h"
#include <string>
#include <map>


namespace Ueuos {
	using std::map;
	using std::string;

	class GLProgramHelper {
	public:
		static GLProgramHelper* getInstance();
	 	~GLProgramHelper();
		GLProgram* getProgramForName(string name);
		GLProgram  createTestShader();
		//glUniformBlock
	
	private:
		GLProgramHelper();
		static GLProgramHelper* _instance;
		map<string, GLProgram*> programs;
	};
}

#endif