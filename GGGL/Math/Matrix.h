#pragma once
#include <memory>
namespace Math {
	class Matrix {
	public:
		Matrix() {
			memset(m,0,sizeof(float)*16);
		}

	
	public:
		static Matrix createPerspective(float left, float right,float top, float bottom,float near, float far);
		static Matrix multiply(const Matrix& a, const Matrix& b);

	public:
		Matrix operator*(const Matrix& mat);
		Matrix& operator*=(const Matrix& mat);
	private:
		float m[16];
	};
}