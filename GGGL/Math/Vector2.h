#pragma once
namespace Math {

	class Vector2 {
	public:
		Vector2(float xx, float yy);

		float magnitude();
		Vector2 normalize();
		Vector2 inverse();
		float sqrMagnitude();


		//static methods
		static float angle(Vector2& from,Vector2& to);
		static Vector2 clampMagnitude(Vector2& vec,float maxMag);
		static float distance(Vector2& a,Vector2& b);
		static float dot(Vector2& a, Vector2& b);
		static Vector2 lerp(Vector2& a, Vector2& b, float t);
		static Vector2 lerpUnclamped(Vector2& a, Vector2& b, float t);
		static Vector2 max(Vector2& a, Vector2& b);
		static Vector2 min(Vector2& a, Vector2& b);
		static Vector2 reflect(Vector2& inComing,Vector2& normal);
		static float singedAngle(Vector2& a, Vector2& b);

		//operators override

		friend Vector2 operator*(float t, Vector2& vec) {
			return vec*t;
		}
		Vector2 operator*(float t);
		float operator*(Vector2& vec);
		Vector2 operator+(Vector2& vec);
		Vector2 operator-(Vector2& vec);

		// DIV
		// EQL
		// V3 TO V2 
		// V2 TO V3
	public:
		float x;
		float y;
	public:
		static const Vector2 zero;
		static const Vector2 up;
		static const Vector2 left;
	};

};