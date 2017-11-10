#include "Vector3.h"
#include <math.h>
#include <algorithm>

#define M_PI 3.14159265358979323846
#define RADIANS_TO_DEGREES(radians) ((radians) * (180.0 / M_PI))
namespace Math {
	const Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::back(0.0f,0.0f,-1.0f);
	const Vector3 Vector3::down(0.0f,-1.0f,0.0f);
	const Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::negativeInfinity(FLT_MIN,FLT_MIN,FLT_MIN);
	const Vector3 Vector3::positiveInfinity(FLT_MAX, FLT_MAX, FLT_MAX);
	const Vector3 Vector3::one(1.0f,1.0f,1.0f);
	const Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);

	float Vector3::magnitude() const{
		return (float)sqrt(sqrMagnitude());
	}

	Vector3& Vector3::normalize() {
		float magSqr = sqrMagnitude();
		if (magSqr == 1.0f)
		{
			return *this;
		}
		float mag = sqrt(magSqr);
		x /= mag;
		y /= mag;
		z /= mag;
		return *this;
	}
	
	float Vector3::sqrMagnitude() const {
		return x*x + y*y + z*z;
	}

	void Vector3::set(float xx, float yy, float zz) {
		x = xx;
		y = yy;
		z = zz;
	}

	float Vector3::angle(const Vector3& a, const Vector3& b) {
		Vector3 NorA = normalized(a);
		Vector3 NorB = normalized(b);
		float cosValue = dot(NorA, NorB);
		return RADIANS_TO_DEGREES(acos(cosValue));
	}
		
	float Vector3::dot(const Vector3& a, const Vector3& b) {
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}
	Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
		Vector3 temp(zero);
		temp.x = a.y*b.z - a.z*b.y;
		temp.y = a.z*b.x - a.x*b.z;
		temp.z = a.x*b.y - b.x*a.y;
		return temp;
	}
	

	float Vector3::signedAngle(const Vector3& a, const Vector3&b) {
		Vector3 NorA = normalized(a);
		Vector3 NorB = normalized(b);
		float cosValue = dot(NorA,NorB);
		int sign = cross(NorA, NorB).y > 0 ? 1 : -1;
		return RADIANS_TO_DEGREES(acos(cosValue))*sign;
	}
	Vector3 Vector3::normalized(const Vector3& v) {
		Vector3 temp(v);
		temp.normalize();
		return temp;
	}
	Vector3 Vector3::lerp(const Vector3& a, const Vector3&b, float t) {
		if (t<0.0)
		{
			t = 0.0;
		}
		else if (t > 1.0) {
			t = 1.0;
		}
		return (1 - t)*a + t*b;
	}
	Vector3 Vector3::lerpUnclamped(const Vector3& a, const Vector3& b, float t) {
		return (1 - t)*a + t*b;
	}
	Vector3& Vector3::max(const Vector3& a, const Vector3&  b) {
		float magSqrA = a.sqrMagnitude();
		float magSqrB = b.sqrMagnitude();
		return const_cast<Vector3&>(magSqrA > magSqrB ? a:b);
	}
	Vector3& Vector3::min(const Vector3& a, const Vector3&  b) {
		float magSqrA = a.sqrMagnitude();
		float magSqrB = b.sqrMagnitude();
		return const_cast<Vector3&>(magSqrA > magSqrB ? b : a);
	}
	Vector3 Vector3::operator*(float scalar) const{
		return Vector3(this->x*scalar,this->y*scalar,this->z*scalar);
	}
	Vector3 Vector3::operator+(const Vector3& other) const {
		Vector3 temp(*this);
		temp.x += other.x;
		temp.y += other.y;
		temp.z += other.z;
		return temp;
	}
	Vector3 Vector3::operator-(const Vector3& other) const {
		Vector3 temp(*this);
		temp.x -= other.x;
		temp.y -= other.y;
		temp.z -= other.z;
		return temp;
	}
	float Vector3::operator*(const Vector3& other) const {
		return dot(*this, other);
	}
	//Vector3
	bool Vector3::operator!=(const Vector3& other) const {
		return  x != other.x ||
				y != other.y ||
				z != other.z ;
	}
	bool Vector3::operator==(const Vector3& other) const {
		return (*this) != other;
	}

}