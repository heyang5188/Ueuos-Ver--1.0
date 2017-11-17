#pragma once
#include "Camera.h"

namespace Ueuos {
	class TargetCamera : public Camera {
	public:
		TargetCamera();

		virtual Matrix getViewProjMat();
		void lookAt(const Vector3& target);
	};
}