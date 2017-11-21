#pragma once

#include "../../Base/UeuosObject.h"

namespace Ueuos {
	class Cube : public UeuosObject {
	public:
		Cube();
		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void  onDraw(const Matrix& parentMatrix);
	private:
		GLushort indeies[36];
	};
}