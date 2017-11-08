#include <math.h>
#include <utility>
#include "Vector2.h"

namespace Math {
	
	Vector2::Vector2(float xx,float yy):_x(xx), _y(yy) {
	
	}

	Vector2::Vector2(const Vector2& rhs) : _x(rhs._x), _y(rhs._y) {
	
	}

	float Vector2::magnitude() {
		return (float)sqrt(sqrMagnitude());
	}

	Vector2 Vector2::normalize(){
		Vector2 temp(*this);
		float mag = temp.magnitude();
		temp._x /= mag;
		temp._y /= mag;
		return temp;
	}

	float Vector2::sqrMagnitude() {
		return _x*_x + _y*_y;
	}

	float Vector2::angle(Vector2& from, Vector2& to) {
		float cosVal = dot(from, to);
		return acos(cosVal);
		//return 0.0;
	}
	/*
		[ a b ]*[ c d ] = ac+bd
	*/
	float Vector2::dot(Vector2& a, Vector2& b) {
		return a._x*b._x + a._y*b._y;
	}

	float Vector2::distance(Vector2& a, Vector2& b) {
		//return ||(a-b)||
		return (a - b).magnitude();
	}

	Vector2 Vector2::clampMagnitude(Vector2& vec, float maxMag) {
		return Vector2(0, 0);
	}

	Vector2 Vector2::lerp(Vector2& a, Vector2& b, float t) {
		Vector2 temp(a);
		if (t>1.0f)
		{
			t = 1.0f;
		}
		else if (t < 0.0f) {
			t = 0.0f;
		}
		return lerpUnclamped(a, b, t);
	}

	Vector2 Vector2::lerpUnclamped(Vector2& a, Vector2& b, float t) {
		Vector2 temp(a*(1.0f - t) + b*t);
		return temp;
	}

	Vector2 Vector2::operator*( float t) {
		Vector2 temp(*this);
		temp._x*=t;
		temp._y*=t;
		return temp;
	}

	float Vector2::operator*(Vector2& vec) {
		return dot(*this, vec);
	}

	Vector2 Vector2::operator+(Vector2& other) {
		Vector2 temp(*this);
		temp._x += other._x;
		temp._y += other._y;
		return temp;
	}

	Vector2 Vector2::operator-(Vector2& vec) {
		Vector2 temp(*this);
		temp._x -= vec._x;
		temp._y -= vec._y;
		return temp;
	}

	Vector2 Vector2::max(Vector2& a, Vector2& b) {
		return a.magnitude() > b.magnitude() ? a : b;
	}

	Vector2 Vector2::min(Vector2& a, Vector2& b) {
		return  a.magnitude() < b.magnitude() ? a : b;
	}
	//math explian
	//http://www.cnblogs.com/graphics/archive/2013/02/21/2920627.html
	
	Vector2 Vector2::reflect(Vector2& inComing, Vector2& normal) {
		Vector2 NormalI = inComing.normalize();
		Vector2 NormalN = normal.normalize();
		Vector2 outgoing = NormalI - 2.0f*(NormalI*NormalN)*NormalN;
		return outgoing;
	}









};