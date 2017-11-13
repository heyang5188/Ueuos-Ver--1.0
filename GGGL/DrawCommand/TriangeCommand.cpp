#include "TriangeCommand.h"

TriangeCommand::TriangeCommand() {

}

TriangeCommand::~TriangeCommand() {

}
GLushort idx[] = { 0,1,2 };
void TriangeCommand::applyVertexData() {
	GLuint vbo;
	GLuint veo;


	//GLushort idx[] = { 0,1,2 };
	glGenVertexArrays(1, &_vao);

	glGenBuffers(1, &veo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3, idx, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo)*3, (const void*)&_verties[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexInfo),(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid*)(  sizeof(float)*3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void TriangeCommand::doDraw() {
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_SHORT, idx);
	glBindVertexArray(0);
}