#pragma once
#include "Vector2.h"

namespace Math {
	class Vector3 {
	public:
		Vector3(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {}
	private:
		float x;
		float y;
		float z;
	};
}