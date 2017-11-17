#include "Grid.h"


namespace Ueuos {
	Grid::Grid(int unitCount, float unitSize) {
		std::vector<VertexInfo> data;
		//data.reserve(unitCount*unitCount * 4);
		//VertexInfo 
		VertexInfo v0 = VertexInfo(Vector3(0, 0, 0),Color4F(1.0,1.0,1.0,1.0));
		VertexInfo v1 = VertexInfo(Vector3(0, 0,50), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo v2 = VertexInfo(Vector3(50,0,50), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo v3 = VertexInfo(Vector3(50, 0, 0), Color4F(1.0, 1.0, 1.0, 1.0));
		data.push_back(v0);
		data.push_back(v1);
		data.push_back(v2);
		data.push_back(v3);
		_verties.swap(data);
		buferData(_verties);
	}

	void Grid::buferData(std::vector<VertexInfo>& data) {
		GLuint vbo;
		
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * 4, &_verties[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (const void*)offsetof(VertexInfo, color));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void Grid::onDraw() {
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}