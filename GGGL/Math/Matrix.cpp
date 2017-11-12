#include "Matrix.h"
#include <iostream>

namespace Math {
	float indentityData[] = {
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0 };
	Matrix Matrix::indentity = Matrix(indentityData);

	Matrix Matrix::createPerspective(float left, float right, float top, float bottom, float near, float far) {
		Matrix mat;
		mat.m[0] = 2 * near / (right - left);
		mat.m[5] = 2 * near / (top-bottom);
		mat.m[8] = (right + left) / (right - left);
		mat.m[9] = (top + bottom) / (top - bottom);
		mat.m[10] = -(far + near) / (far-near);
		mat.m[11] = -1.0f;
		mat.m[14] = -2 * far*near / (far - near);
		return mat;
	} 

	Matrix Matrix::multiply(const Matrix& a, const Matrix& b) {
		Matrix mat;
		for (int i = 0; i < 16; ++i)
		{
			float value = 0.0;
			for (int  j = 0; j < 4; ++j)
			{
				value += a.m[int(i / 4) * 4 + j] * b.m[j * 4 + (i % 4)];
			}
			mat.m[i] = value;
		}
		return mat;
	}
	
	Matrix Matrix::operator*(const Matrix& mat) {
		return Matrix();
	}
	
	Matrix& Matrix::operator*=(const Matrix& mat) {
		return (*this);
	}

	float& Matrix::operator[](int idx) {
		return m[idx];
	}
}