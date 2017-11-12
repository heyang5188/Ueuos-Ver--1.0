#include "Quaternion.h"
#include <math.h>

namespace Math {

	const Quaternion Quaternion::identity(0.0,0.0,0.0,1.0);

	Quaternion::Quaternion():x(0.0),y(0.0),z(0.0),w(1.0) {
	}

	Quaternion::Quaternion(float xx, float yy, float zz, float ww):x(xx),y(yy),z(zz),w(ww) {
		normalize();
	}

	Quaternion::Quaternion(float yaw, float pitch, float roll) {
		setEulerAngle(yaw, pitch, roll);
	}

	Quaternion::Quaternion(const Vector3 & euler)
	{
		f64 angle;

		angle =  0.5*DEGREES_TO_RADIANS(euler.x);
		const f64 sr = sin(angle);
		const f64 cr = cos(angle);
		
		angle = 0.5*DEGREES_TO_RADIANS(euler.y);
		const f64 sp = sin(angle);
		const f64 cp = cos(angle);

		angle = 0.5*DEGREES_TO_RADIANS(euler.z);
		const f64 sy = sin(angle);
		const f64 cy = cos(angle);

		const f64 cpcy = cp * cy;
		const f64 spcy = sp * cy;
		const f64 cpsy = cp * sy;
		const f64 spsy = sp * sy;

		x = (f32)(sr * cpcy - cr * spsy);
		y = (f32)(cr * spcy + sr * cpsy);
		z = (f32)(cr * cpsy - sr * spcy);
		w = (f32)(cr * cpcy + sr * spsy);
		
		normalize();

	}

	Quaternion & Quaternion::normalize()
	{
		float mag = magnitude();
		x = x / mag;
		y = y / mag;
		z = z / mag;
		w = w / mag;
		return *this;
	}

	float Quaternion::magnitude() {
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	//Vector3 Quaternion::eulerAngles() {
	//	return Vector3::zero;
	//}
	//||Axis|| == 1.0 Unit V3  angle in radians
	Quaternion Quaternion::angleAxis(float angle, const Vector3 & axis)
	{
		const float fHalfAngle = angle / 2;
		const float fSin = sinf(fHalfAngle);
		float x = fSin*axis.x;
		float y = fSin*axis.y;
		float z = fSin*axis.z;
		float w = cosf(fHalfAngle);
		return Quaternion(x,y,z,w);
	
	}

	//Degs of two quaternion
	float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
		return (a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w);
	}

	Vector3 Quaternion::euler(const Quaternion & a)
	{
		Vector3 euler;
		const double sqrW = a.w*a.w;
		const double sqrX = a.x*a.x;
		const double sqrY = a.y*a.y;
		const double sqrZ = a.z*a.z;

		const double test = 2.0*(a.y*a.w - a.x*a.z);
		//
		if (test == 1.0)
		{
			//heading -->roll aoubt z-axis
			euler.z = -2.0*atan2(a.x,a.w);
			//bank --> roll abount x-axis
			euler.x = 0.0f;
			//attitude roll about y-axis
			euler.y = M_PI / 2.0;
		}
		else if (test == -1.0) {
			euler.z = 2.0*atan2(a.x, a.w);
			euler.x = 0.0f;
			euler.y = M_PI / -2.0;
		}
		else {
			euler.z = atan2(2.0*(a.x*a.y+a.z*a.w),(sqrX-sqrY-sqrZ+sqrW));
			euler.x = atan2(2.0*(a.y*a.z + a.x*a.w), (-sqrX - sqrY + sqrZ + sqrW));
			euler.y = asin(CLAMP(test, -1.0, 1.0));
		}

		return euler;
	}

	void Quaternion::setEulerAngle(float yaw, float pitch, float roll) {

	}

	Matrix Quaternion::getRotationMatrix() const
	{
		typedef double f32;
		Matrix dest = Matrix();

		Quaternion quat(*this);
		quat.normalize();
		f32 X = quat.x;
		f32 Y = quat.y;
		f32 Z = quat.z;
		f32 W = quat.w;

		dest[0] = (f32)1.0 - 2.0*Y*Y - 2.0*Z*Z;
		dest[1] = (f32)2.0f*X*Y - 2.0f*Z*W;
		dest[2] = (f32)2.0f*X*Z + 2.0f*Y*W;

		dest[4] = (f32)2.0f*X*Y + 2.0f*Z*W;
		dest[5] = (f32)1.0f - 2.0f*X*X - 2.0f*Z*Z;
		dest[6] = (f32)2.0f*Z*Y - 2.0f*X*W;

		dest[8] = (f32)2.0f*X*Z - 2.0f*Y*W;
		dest[9] = (f32)2.0f*Z*Y + 2.0f*X*W;
		dest[10] = (f32)1.0f - 2.0f*X*X - 2.0f*Y*Y;

		dest[15] = 1.0f;

		return dest ;
	}

	void Quaternion::set(float xx, float yy, float zz, float ww) {
		x = xx;
		y = yy;
		z = zz;
		w = zz;
	}

	Quaternion Quaternion::conjugate(const Quaternion& other) {
		return Quaternion(-other.x,-other.y,-other.z,other.w);
	}

	//Quaternion Quaternion::inverse(const Quaternion& other) {
	//	return Quaternion();
	//}

	Quaternion Quaternion::lerp(const Quaternion & a, const Quaternion & b, float t)
	{
		return a*(1.0 - t) + b*t;
	}

	Quaternion Quaternion::operator*(float s) const
	{
		return Quaternion(s*x,s*y,s*z,s*w);
	}

	bool Quaternion::operator==(const Quaternion& other) const {
		if (this == &other)
		{
			return true;
		}

		return	x == other.x &&
				y == other.y &&
				z == other.z &&
				w == other.w;
	}

	bool Quaternion::operator!=(const Quaternion& other) const {
		return !(*this==other);
	}

	Quaternion Quaternion::operator+(const Quaternion & other) const
	{
		Quaternion quat;
		quat.x = x + other.x;
		quat.y = y + other.y;
		quat.z = z + other.z;
		quat.w = w + other.w;
		return quat;
	}

	// (x0*i + y0*j + z0*k + w0)*(x1*i + y1*j + z1*k + w1)
	// =
	// i*(+x0*w1 + y0*z1 - z0*y1 + w0*x1) +
	// j*(-x0*z1 + y0*w1 + z0*x1 + w0*y1) +
	// k*(+x0*y1 - y0*x1 + z0*w1 + w0*z1) +
	// 1*(-x0*x1 - y0*y1 - z0*z1 + w0*w1)
	Quaternion operator*(const Quaternion & lhs, const Quaternion & rhs)
	{

		return Quaternion
			(
				+lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x,
				-lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x + lhs.w * rhs.y,
				+lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w + lhs.w * rhs.z,
				-lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z + lhs.w * rhs.w
				);
	}

}