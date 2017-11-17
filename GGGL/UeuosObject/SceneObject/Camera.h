#pragma once

#include "../Base/UeuosObject.h"
#include "../../Math/Transform.h"

namespace Ueuos {
	using namespace Math;
	using Math::Vector3;
	class Camera {
	public:
		Camera();
		
		void setProjectionMatrix(const Matrix& mat);
		void lookAt(const Vector3 & target, const Vector3 & up);
		void setPosition(const Vector3& pos);
		Vector3 getPosition();

		virtual Matrix getViewProjMat() = 0;

		public:
		Vector3   up;
		Vector3   target;
		Transform transform;
		Matrix    projection;
		Matrix	  view;
	};
}