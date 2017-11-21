#include "World.h"
#include <stdio.h>
using namespace Ueuos;
#include "TargetCamera.h"
#include "../../Rendering/GLProgramHelper.h"

Ueuos::World::World()
{
	Grid* worldGrid = new Grid(50,30);
	Axis* worldAxis = new Axis();
	//worldAxis->setScale(Vector3(100, 10, 1000));
	//transform.addChil
	addChild(&worldGrid->transform);
	addChild(&worldAxis->transform);

	TargetCamera* camera = new Ueuos::TargetCamera();
	camera->setPosition(Math::Vector3(0, 100, 100));
	camera->lookAt(Math::Vector3(0, 0, 0));
	Math::Matrix p1 = Math::Matrix::createPerspective(45, 800.0f / 600.0f, 0.1, 10000);
	camera->setProjectionMatrix(p1);
	cameras.push_back(camera);
}

void Ueuos::World::draw()
{
	draw(Matrix::indentity);
}

void Ueuos::World::draw(const Matrix & parentMatrix)
{
	modelMatrixStack.push(&transform.getModelMatrix());
	for (auto child : transform.getChildren())
	{
		UeuosObject* obj = (UeuosObject*)((*child).object);
		
		//GLProgram pro = GLProgram::
		GLuint glPro = GLProgramHelper::getInstance()->getProgramForName("TEST")->program;
		glUseProgram(glPro);
		GLint mvLoc = glGetUniformLocation(glPro, "pv");
		GLint tranformLoc = glGetUniformLocation(glPro, "transform");
		//glUseProgram(getGLProgram()->program);
		glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, (GLfloat*)&getModelMatrix());
		Matrix pv = cameras[0]->getViewProjMat();
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, (GLfloat*)&pv);
		obj->draw();
	}
	modelMatrixStack.pop();
}

void Ueuos::World::buferData(std::vector<VertexInfo>& data)
{
}
void Ueuos::World::onDraw(const Matrix & parentMatrix)
{
}
