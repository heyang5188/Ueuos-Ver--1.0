#include "Camera.h"
namespace Ueuos {
	Camera::Camera():transform(Vector3::zero,Vector3::zero,Vector3(1.0,1.0,1.0)){

		transform.updateModleMatrix();
	}

	void Camera::setPosition(const Vector3& pos) {
		transform.position = pos;
		transform.updateModleMatrix();
	}

	Vector3 Camera::getPosition()
	{
		return transform.position;
	}

	void Camera::setProjectionMatrix(const Matrix& mat) {
		projection = mat;
	}
	
	void Camera::lookAt(const Vector3& target,const Vector3& up) {
		this->target = target;
	}

	//void 
}