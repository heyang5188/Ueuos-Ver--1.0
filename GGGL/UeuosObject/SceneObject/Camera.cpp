#include "Camera.h"
namespace Ueuos {
	Camera::Camera(){}

	void Camera::setPosition(const Vector3& pos) {
		transform.position = pos;
	}

	void Camera::setProjectionMatrix(const Matrix& mat) {
		projection = mat;
	}
	
	void Camera::lookAt(const Vector3& target,const Vector3& up) {
		Vector3 VPN = target - transform.position;
		Vector3 n = Vector3::normalized(VPN);
		Vector3 nUp = Vector3::normalized(up);
		//X
		Vector3 u = Vector3::cross(nUp,n).normalize();
		//Y
		Vector3 v = Vector3::cross(n, u);
	}

	Matrix getViewProj() {
		return Matrix();
	}
}