#pragma once

#include "Vector3.h"
#include "MathMacro.h"
#include "Matrix.h"
#include "TypeRedef.h"

namespace Math {

	class Quaternion {
	public:
		Quaternion();
		Quaternion(float x, float y, float z,float w);
		Quaternion(float yaw, float pitch, float roll);
		Quaternion(const Vector3& euler);
		Quaternion(const Matrix& mtx);

		//Vector3 eulerAngles();
		//unless you know what you are doing, DO NOT INVOKE THIS FUNCTION
		void set(float x, float y, float z, float w);
		void set(float yaw, float pitch, float roll);
		

		void setFromToRotation(Vector3& fromDirection, Vector3& toDirection);
		void setLookRotation(const Vector3& view, const Vector3& up=Vector3::up);
		void toAngleAxis(float& angle, Vector3& axis);
		Quaternion& normalize();
		float magnitude();

		void setEulerAngle(float yaw, float pitch, float roll);
		Matrix getRotationMatrix() const;

	public:
		static const Quaternion identity;
		static Quaternion zero;      // z = 0*i + 0*j + 0*k + 0
		static Quaternion I;         // i = 1*i + 0*j + 0*k + 0
		static Quaternion J;         // j = 0*i + 1*j + 0*k + 0
		static Quaternion K;         // k = 0*i + 0*j + 1*k + 0	
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
		static Quaternion conjugate(const Quaternion& other);


	public:
		Quaternion operator*(float rhs) const;
		bool operator==(const Quaternion& other) const;
		bool operator!=(const Quaternion& other) const;
		Quaternion operator+(const Quaternion& other) const;
		//?
		Quaternion operator=(const Quaternion& other);
		Quaternion operator=(const Matrix& matirx);


		friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);

	public:
		float w;
		float x;
		float y;
		float z;

//		Vector3 eulerAngles;

	};
}