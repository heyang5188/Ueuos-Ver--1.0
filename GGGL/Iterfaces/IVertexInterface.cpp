#include "IVertexInterface.h"
#include "../Rendering/GLProgramHelper.h"
Ueuos::IVertexInterface::IVertexInterface()
{
	GLProgram* pro = GLProgramHelper::getInstance()->getProgramForName("TEST");
	glProgram = pro;
}
