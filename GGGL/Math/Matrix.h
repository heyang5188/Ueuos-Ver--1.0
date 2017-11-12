#pragma once
#include <memory>
#include "Vector3.h"
namespace Math {
	class Matrix {
	public: 
		Matrix(float data[16]) {
			memcpy(m,data,sizeof(float)*16);
		}
		Matrix() {
			memset(m,0,sizeof(float)*16);
		}
	public:
		static Matrix indentity;

	
	public:
		static Matrix createPerspective(float left, float right,float top, float bottom,float near, float far);
		static Matrix createOrthographic(float l, float r, float t, float b, float n, float f);
		static Matrix multiply(const Matrix& a, const Matrix& b);

		static Matrix lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

	public:
		Matrix operator*(const Matrix& mat);
		Matrix& operator*=(const Matrix& mat);

		float& operator[](int idx);

	private:
		float m[16];
	};
}