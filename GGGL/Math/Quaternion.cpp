#include "Quaternion.h"
#include <math.h>

namespace Math {

	const Quaternion Quaternion::identity(0.0,0.0,0.0,1.0);

	Quaternion::Quaternion(float xx, float yy, float zz, float ww) {
		float mag = xx*xx + yy*yy + zz*zz + ww*ww;
		x = xx / mag;
		y = yy / mag;
		z = zz / mag;
		w = ww / mag;
	}

	Quaternion::Quaternion(float yaw, float pitch, float roll) {
		setEulerAngle(yaw, pitch, roll);
	}

	//Vector3 Quaternion::eulerAngles() {
	//	return Vector3::zero;
	//}
	
	//Degs of two quaternion
	float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
		return RADIANS_TO_DEGREES(acos(a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w));
	}

	void Quaternion::setEulerAngle(float yaw, float pitch, float roll) {

	}

	void Quaternion::set(float xx, float yy, float zz, float ww) {
		x = xx;
		y = yy;
		z = zz;
		w = zz;
	}


}