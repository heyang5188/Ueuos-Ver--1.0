#include "Grid.h"


namespace Ueuos {
	Grid::Grid(int lineCount, float spacing) {
		std::vector<VertexInfo> data;
		//data.reserve(unitCount*unitCount * 4);
		//VertexInfo 
		if (lineCount%2==0)
		{
			lineCount++;
		}
		int mid = lineCount / 2;
		float lineLen = (lineCount - 1)*spacing;
		for (int i = 0; i < lineCount; ++i)
		{
			float pos = (i - mid)*spacing;
			VertexInfo v0 = VertexInfo(Vector3(pos, 0, -lineLen/2), Color4F(.5, .5, .5, .5));
			VertexInfo v1 = VertexInfo(Vector3(pos, 0, lineLen/2), Color4F(.5, .5, .5, .5));
			data.push_back(v0);
			data.push_back(v1);
			VertexInfo v3 = VertexInfo(Vector3(-lineLen / 2, 0, pos), Color4F(.5, .5, .5, .5));
			VertexInfo v4 = VertexInfo(Vector3(lineLen / 2, 0, pos), Color4F(.5, .5, .5, .5));
			data.push_back(v3);
			data.push_back(v4);
		}


		//data.push_back(v0);
		//data.push_back(v1);
		//data.push_back(v2);
		//data.push_back(v3);
		_verties.swap(data);
		buferData(_verties);
	}

	void Grid::buferData(std::vector<VertexInfo>& data) {
		GLuint vbo;
		
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo) * _verties.size(), &_verties[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (const void*)offsetof(VertexInfo, color));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void Grid::onDraw(const Matrix& parentMatrix) {

		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, (GLsizei)_verties.size());
		glBindVertexArray(0);
		//glUseProgram(0);
	}
}