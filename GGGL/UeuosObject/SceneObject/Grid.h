#pragma once

#include "../Base/UeuosObject.h"

namespace Ueuos {
	class Grid : public UeuosObject {
	public:
		Grid(int lineCount, float spacing);

		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void onDraw(const Matrix& parentMatrix);
	private:
	};
}