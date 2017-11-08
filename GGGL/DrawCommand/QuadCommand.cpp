#include "QuadCommand.h"



QuadCommand::QuadCommand(Vector3 origin, Vector3 end)
{

}

QuadCommand::QuadCommand(Vector3 topLeft, Vector3 bottomLeft, Vector3 topRight, Vector3 bottomRight)
{
	VertexInfo v0 = VertexInfo(topLeft);
	VertexInfo v1 = VertexInfo(bottomLeft);
	VertexInfo v2 = VertexInfo(topRight);
	VertexInfo v3 = VertexInfo(bottomRight);
	vector<VertexInfo> data{ v0,v1,v2,v3 };
	setVertexData(data);
//	vector<VertexInfo>().swap(data);
}



QuadCommand::~QuadCommand()
{
}


/*
** TRIANGLE_FANS
** 0   2
**
** 1   3
** when index i%2==0 index goes n,n+1,n+2
                 otherwise goes n,n+2,n+1
**               make sure edge wind anti-clockwise.
*/

void QuadCommand::applyVertexData() {
	GLuint vbo;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * 4, (const void*)&_verties[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(VertexInfo),0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,sizeof(VertexInfo),(GLvoid*)offsetof(VertexInfo, position));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void QuadCommand::doDraw() {
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
