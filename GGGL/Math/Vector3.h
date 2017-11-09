#pragma once
namespace Math {
	class Vector3 {
	public:
		Vector3(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {}
		Vector3(const Vector3& vec);

		float magnitude();
		Vector3 normalize();
		Vector3 inverse();
		float sqrMagnitude();

	public: 

		//   static
		static Vector3 back;
		static Vector3 down;
		static Vector3 forward;
		static Vector3 left;
		static Vector3 negativeInfinity;
		static Vector3 one;
		static Vector3 positiveInfinity;
		static Vector3 right;
		static Vector3 up;
		static Vector3 zero;
	public: 
		// Operator override

		float operator[](int i) {
			float *p = (float*)this;
			return *(p + i);
		}

	public:
		float x;
		float y;
		float z;
	};
}