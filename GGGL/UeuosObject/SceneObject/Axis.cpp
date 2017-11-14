#include "Axis.h"
namespace Ueuos {
	Ueuos::Axis::Axis()
	{
		//RED X
		VertexInfo originX = VertexInfo(Vector3(0, 0, 0), Color4F(1.0, 0.0, 0.0, 1.0));
		VertexInfo endX    = VertexInfo(Vector3(1, 0, 0), Color4F(1.0, 0.0, 0.0, 1.0));
		//Green Y
		VertexInfo originY = VertexInfo(Vector3(0, 0, 0), Color4F(0.0, 1.0, 0.0, 1.0));
		VertexInfo endY = VertexInfo(Vector3(0, 1, 0), Color4F(0.0, 1.0, 0.0, 1.0));
		//Blue Z or
		VertexInfo originZ = VertexInfo(Vector3(0, 0, 0), Color4F(0.0, 0.0, 1.0, 1.0));
		VertexInfo endZ = VertexInfo(Vector3(0, 0, 1), Color4F(0.0, 0.0, 1.0, 1.0));

		std::vector<VertexInfo> data = { originX,endX,originY,endY,originZ,endZ };
		
		_verties.swap(data);
		buferData(_verties);
	}

	void Axis::buferData(std::vector<VertexInfo>& data) {
		GLuint vbo;
	
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
			
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * 6, (const void*)&_verties[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (const void*)offsetof(VertexInfo, color));
		glEnableVertexAttribArray(1);
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Axis::onDraw() {
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 6);
		glBindVertexArray(0);
	}

}
