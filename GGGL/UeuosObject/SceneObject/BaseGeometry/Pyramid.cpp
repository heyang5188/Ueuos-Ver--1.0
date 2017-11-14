#include "Pyramid.h"

namespace Ueuos {
	Pyramid::Pyramid() {
		VertexInfo vi0 = VertexInfo(Vector3(-0.5, -0.5, 0.5), Color4F(1.0, .5, 1.0, 1.0));
		VertexInfo vi1 = VertexInfo(Vector3(0.5, -0.5, 0.5), Color4F(1.0, 1.0, .0, 1.0));
		VertexInfo vi2 = VertexInfo(Vector3(0.5, -0.5, -0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi3 = VertexInfo(Vector3(-0.5, -0.5, -0.5), Color4F(1.0, 0.0, 1.0, 1.0));
		VertexInfo vi4 = VertexInfo(Vector3(0, 0.5, 0), Color4F(1.0, 0.0, 0.0, 1.0));
		std::vector<VertexInfo> data = { vi0,vi1,vi2,vi3,vi4 };

		_verties.swap(data);

		GLushort temp[] =
		{
			0,1,4,
			1,2,4,
			2,3,4,
			3,0,4,
			0,3,1,
			3,2,1
		}; 
		//18 
		memcpy(indeies, temp, sizeof(temp));
		buferData(_verties);
	}
	void Pyramid::buferData(std::vector<VertexInfo>& data)
	{
		GLuint vbo;
		GLuint veo;
		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &veo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 18, indeies, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Ueuos::VertexInfo) * 5, (const void*)&_verties[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Ueuos::VertexInfo), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Ueuos::VertexInfo), (GLvoid*)offsetof(Ueuos::VertexInfo, color));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Pyramid::onDraw()
	{
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, 16, GL_UNSIGNED_SHORT, indeies);
		glBindVertexArray(0);
	}
}