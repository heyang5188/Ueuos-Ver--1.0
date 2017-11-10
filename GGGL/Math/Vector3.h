#pragma once
namespace Math {
	class Vector3 {
	public:
		Vector3(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {}

		float magnitude() const;
		Vector3& normalize();
		float sqrMagnitude() const;
		void set(float x, float y, float z);

	public:
		static float angle(const Vector3& from,const Vector3& to);
		static float clampMagnitude();
		static Vector3 cross(const Vector3& a, const Vector3& b);
		static Vector3 distance(const Vector3& a, const Vector3& b);
		static float dot(const Vector3& a, const Vector3& b);
		static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
		static Vector3 lerpUnclamped(const Vector3& a, const Vector3& b,float t);
		static Vector3& max(const Vector3& a, const Vector3&b);
		static Vector3& min(const Vector3& a, const Vector3&b);
		static Vector3 moveTowards(Vector3& current, Vector3& target, float maxDistanceDelta);
		static Vector3 normalized(const Vector3& v);
		static Vector3 orthoNormalize(Vector3& normal,Vector3& tangent);
		static Vector3 project(Vector3& vector, Vector3& onNormal);
		static Vector3 projectOnPlane(Vector3& vector, Vector3& planeNormal);
		static Vector3 reflect(Vector3& incoming, Vector3& normal);
		static Vector3 rotateTowards(Vector3& current, Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);
		static Vector3 scale(Vector3& a, Vector3&b);
		static float signedAngle(const Vector3& a, const Vector3&b);
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

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		//dot!
		float operator*(const Vector3& other) const;
		
		Vector3 operator*(float scalar) const;
		friend Vector3 operator*(float scalar, const Vector3& vec) {
			return vec*scalar;
		}

		//Vector3 operator/(Vector3& other);
		bool operator!=(const Vector3& other) const;
		bool operator==(const Vector3& other) const;

	public:
		float x;
		float y;
		float z;
	};
}