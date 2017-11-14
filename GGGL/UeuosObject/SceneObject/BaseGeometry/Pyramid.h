#pragma once
#include "../../Base/UeuosObject.h"
namespace Ueuos {
	class Pyramid : public UeuosObject {
	public:
		Pyramid();
		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void onDraw();
	private:
		GLushort indeies[5];
	};
}