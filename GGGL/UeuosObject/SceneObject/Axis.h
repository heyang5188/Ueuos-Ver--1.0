#pragma once
#include "../Base/UeuosObject.h"
namespace Ueuos {
	class Axis : public UeuosObject {
	public:
		Axis();

		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void onDraw();
	private:
		
	};
}