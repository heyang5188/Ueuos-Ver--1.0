#pragma once
namespace Math {
	class Vector3 {
	public:
		Vector3(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {}

		float magnitude();
		Vector3 normalize();
		Vector3 inverse();
		float sqrMagnitude();
		void set(float x, float y, float z);

	public:
		static float angle(Vector3& from, Vector3& to);
		static float clampMagnitude();
		static Vector3 cross(Vector3& a, Vector3& b);
		static Vector3 distance(Vector3& a,Vector3& b);
		static Vector3 dot(Vector3& a, Vector3& b);
		static Vector3 lerp(Vector3& a, Vector3& b, float t);
		static Vector3 lerpUnclamped(Vector3& a, Vector3& b,float t);
		static Vector3 max(Vector3& a, Vector3&b);
		static Vector3 min(Vector3& a, Vector3&b);
		static Vector3 moveTowards(Vector3& current, Vector3& target, float maxDistanceDelta);
		static Vector3 normalize(Vector3& v);
		static Vector3 orthoNormalize(Vector3& normal,Vector3& tangent);
		static Vector3 project(Vector3& vector, Vector3& onNormal);
		static Vector3 projectOnPlane(Vector3& vector, Vector3& planeNormal);
		static Vector3 reflect(Vector3& incoming, Vector3& normal);
		static Vector3 rotateTowards(Vector3& current, Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);
		static Vector3 scale(Vector3& a, Vector3&b);
		static Vector3 signedAngle(Vector3& a, Vector3&b);
		static Vector3 slerp(Vector3&a, Vector3& b, float t);
		static Vector3 slerpUnclamped(Vector3& a, Vector3& b, float t);
		//static Vector3 smoothDamp(???)

	public: 
		//   static
		static const Vector3 back;
		static const Vector3 down;
		static const Vector3 forward;
		static const Vector3 left;
		static const Vector3 negativeInfinity;
		static const Vector3 one;
		static const Vector3 positiveInfinity;
		static const Vector3 right;
		static const Vector3 up;
		static const Vector3 zero;
	public: 
		// Operator override

		float operator[](int i) {
			float *p = (float*)this;
			return *(p + i);
		}

		Vector3 operator+(Vector3& other);
		Vector3 operator-(Vector3& other);
		//dot!
		Vector3 operator*(Vector3& other);
		Vector3 operator/(Vector3& other);

		Vector3 operator!=(Vector3& other);
		Vector3 operator==(Vector3& other);

	public:
		float x;
		float y;
		float z;
	};
}