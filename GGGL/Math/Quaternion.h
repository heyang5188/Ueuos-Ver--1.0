#pragma once

#include "Vector3.h"
#include "MathMacro.h"

namespace Math {

	class Quaternion {
	public:
		Quaternion(float x, float y, float z,float w);
		Quaternion(float yaw, float pitch, float roll);

		//Vector3 eulerAngles();
		//unless you know what you are doing, DO NOT INVOKE THIS FUNCTION
		void set(float x, float y, float z, float w);
		
		void setFromToRotation(Vector3& fromDirection, Vector3& toDirection);
		void setLookRotation(const Vector3& view, const Vector3& up=Vector3::up);
		void toAngleAxis(float& angle, Vector3& axis);

		void setEulerAngle(float yaw, float pitch, float roll);

	public:
		static const Quaternion identity;
		
	public:
		static float angle(const Quaternion& a, const Quaternion& b);
		static Quaternion angleAxis(float angle, const Vector3& axis);
		static float dot(const Quaternion& a, const Quaternion& b);
		static Vector3 euler(const Quaternion& a);

		static Quaternion fromToRotation(const Vector3& fromDirection,const Vector3& toDirection);
		static Quaternion inverse(const Quaternion& rotation);
		static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
		static Quaternion lerpUnclamped(const Quaternion& a, const Quaternion& b, float t);
		static Quaternion lookRotation(const Vector3& forward, const Vector3& upwards = Vector3::up);
		static Quaternion rotateTowards(const Quaternion& from,const Quaternion& to, float maxDegreesDelta);
		static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
		static Quaternion slerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

	public:
		Quaternion operator*(float rhs);
		Quaternion operator==(const Quaternion& other);

		friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);


	public:
		float w;
		float x;
		float y;
		float z;

		Vector3 eulerAngles;

	};
}