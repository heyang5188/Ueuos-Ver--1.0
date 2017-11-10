#include "Matrix.h"

namespace Math {
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
		return mat;
	}
	
	Matrix Matrix::operator*(const Matrix& mat) {
		return Matrix();
	}
	
	Matrix& Matrix::operator*=(const Matrix& mat) {
		return (*this);
	}
}