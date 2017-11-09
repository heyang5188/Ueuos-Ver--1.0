#include <math.h>
#include <utility>
#include "Vector2.h"

namespace Math {
	
	const Vector2 Vector2::up(0.0, 1.0);
	const Vector2 Vector2::zero(0.0, 0.0);
	const Vector2 Vector2::left(-1.0, 0);


	Vector2::Vector2(float xx,float yy):x(xx), y(yy) {
	
	}

	float Vector2::magnitude() {
		return (float)sqrt(sqrMagnitude());
	}

	Vector2 Vector2::normalize(){
		Vector2 temp(*this);
		float mag = temp.magnitude();
		temp.x /= mag;
		temp.y /= mag;
		return temp;
	}

	float Vector2::sqrMagnitude() {
		return x*x + y*y;
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
		return a.x*b.x + a.y*b.y;
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
		temp.x*=t;
		temp.y*=t;
		return temp;
	}

	float Vector2::operator*(Vector2& vec) {
		return dot(*this, vec);
	}

	Vector2 Vector2::operator+(Vector2& other) {
		Vector2 temp(*this);
		temp.x += other.x;
		temp.y += other.y;
		return temp;
	}

	Vector2 Vector2::operator-(Vector2& vec) {
		Vector2 temp(*this);
		temp.x -= vec.x;
		temp.y -= vec.y;
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