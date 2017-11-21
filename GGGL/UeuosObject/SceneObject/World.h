#pragma once
#include "../Base/UeuosObject.h"
#include "Axis.h"
#include "Grid.h"
#include <stack>
#include "Camera.h"

namespace Ueuos{
	class World : public UeuosObject {
	public:
		World();
		virtual void draw();
		virtual void draw(const Matrix& parentMatrix) override;
	protected:
		virtual void buferData(std::vector<VertexInfo>& data);
		virtual void onDraw(const Matrix& parentMatrix);
	private:
		std::stack<Matrix*> modelMatrixStack;
		std::vector<Camera*> cameras;
	};
}