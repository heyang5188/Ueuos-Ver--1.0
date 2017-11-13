#pragma once

#include "../../Base/UeuosObject.h"

namespace Ueuos {
	class Cube : public UeuosObject {
	public:
		Cube();
		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void onDraw();
	private:
		GLushort indeies[36];
	};
}