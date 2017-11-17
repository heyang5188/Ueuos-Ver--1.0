#include "TargetCamera.h"

namespace Ueuos {


	TargetCamera::TargetCamera() {
		target = Vector3::forward;
		up = Vector3(0.0,1.0,0.0);
	}

	Matrix Ueuos::TargetCamera::getViewProjMat()
	{

		Vector3 n = (target - transform.position).normalize();
		Vector3 u = Vector3::cross(n, up).normalize();
		Vector3 v = Vector3::cross(u, n).normalize();

		float data[] = {
			u.x,v.x,-n.x,0,
			u.y,v.y,-n.y,0,
			u.z,v.z,-n.z,0,
			-(transform.position*u),-(transform.position*v),transform.position*n,1
		};
		Matrix viewMat(data);
		view = viewMat;
		return view*projection;
	}
	void TargetCamera::lookAt(const Vector3 & target)
	{
		this->target = target;
	}
}
