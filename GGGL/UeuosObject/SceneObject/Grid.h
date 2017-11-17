#pragma once

#include "../Base/UeuosObject.h"

namespace Ueuos {
	class Grid : public UeuosObject {
	public:
		Grid(int unitCount, float unitSize);

		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void onDraw();
	private:
	};
}