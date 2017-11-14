#pragma once

#include "../Base/UeuosObject.h"
#include "../../Math/Transform.h"

namespace Ueuos {
	using namespace Math;
	class Camera{
	public:
		Camera();
		
		void setProjectionMatrix(const Matrix& mat);
		void lookAt(const Vector3 & target, const Vector3 & up);
		void setPosition(const Vector3& pos);

		Matrix getViewProjMat();

	private:
		Transform transform;
		Matrix    projection;
		Matrix	  view;
	};
}