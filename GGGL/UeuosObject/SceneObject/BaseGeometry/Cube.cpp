#include "Cube.h"

namespace Ueuos {
	Ueuos::Cube::Cube()
	{
		// cube ///////////////////////////////////////////////////////////////////////
		//
		//		  y
		//		  |
		//        |
		//		  v6----- v5
		//		 /|      /|
		//		v1------v0|
		//		| |     | |
		//		| |v7---|-|v4
		//		|/      |/    ----->x
		//		v2------v3  
		//	   /
		//    / 
		//   z
		VertexInfo vi0 = VertexInfo(Vector3(0.5,0.5,0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi1 = VertexInfo(Vector3(-0.5, 0.5, 0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi2 = VertexInfo(Vector3(-0.5, -0.5, 0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi3 = VertexInfo(Vector3(0.5, -0.5, 0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi4 = VertexInfo(Vector3(0.5, -0.5, -0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi5 = VertexInfo(Vector3(0.5, 0.5, -0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi6 = VertexInfo(Vector3(-0.5, 0.5, -0.5), Color4F(1.0, 1.0, 1.0, 1.0));
		VertexInfo vi7 = VertexInfo(Vector3(-0.5, -0.5, -0.5), Color4F(1.0, 1.0, 1.0, 1.0));

		std::vector<VertexInfo> data = { vi0,vi1,vi2,vi3,vi4,vi5,vi6,vi7 };
		_verties.swap(data);

		GLushort temp[] =
			{ 0,1,2, 2,3,0,   // 36 of indices
			0,3,4, 4,5,0,
			0,5,6, 6,1,0,
			1,6,7, 7,2,1,
			7,4,3, 3,2,7,
			4,7,6, 6,5,4 };
		memcpy(indeies, temp, sizeof(temp));
		buferData(_verties);

	}

	void Ueuos::Cube::buferData(std::vector<VertexInfo>& data)
	{
		GLuint vbo;
		GLuint veo;
		glGenVertexArrays(1,&vao);

		glGenBuffers(1, &veo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3, indeies, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glGenBuffers(1, &veo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		glBufferData(GL_ARRAY_BUFFER,sizeof(VertexInfo)*8,(const void*)&_verties[0],GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid*)offsetof(VertexInfo, position));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Ueuos::Cube::onDraw()
	{
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,indeies);
		glBindVertexArray(0);
	}
}
