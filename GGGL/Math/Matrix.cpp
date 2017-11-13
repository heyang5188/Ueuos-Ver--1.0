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
		mat[0] = 2 * near / (right - left);
		mat[3] = (right + left) / (right - left);
		mat[5] = 2 * near / (top-bottom);
		mat[6] = (top+bottom) / (top - bottom);
		mat[10] = -(far + near) / (far - near);
		mat[11] = -2*far* near / (far - near);
		mat[14] = -1;
		return mat;
	}

	Matrix Matrix::createOrthographic(float l, float r, float t, float b, float n, float f)
	{
		Matrix mat;
		mat[0] = 2 / (r - l);
		mat[3] = -(r + l) / (r - l);
		mat[5] = 2 / (t - b);
		mat[7] = -(t + b) / (t - b);
		mat[10] = -2 / (f - n);
		mat[11] = -(f + n) / (f - n);
		mat[15] = 1;
		return mat;
	}


	Matrix Matrix::lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{

		Vector3 z = Vector3::normalized(eye - target);
		Vector3 x = Vector3::normalized(Vector3::cross(z, up));
	//	Vector3 x(  (Vector3::cross(z, up).normalize()));
		Vector3 y(Vector3::cross(x, z));

		Matrix result;

		result[0] = x.x;
		result[4] = x.y;
		result[8] = x.z;
		result[12] = -Vector3::dot(x, eye);

		result[1] = y.x;
		result[5] = y.y;
		result[9] = y.z;
		result[13] = -Vector3::dot(y, eye);

		result[2] = z.x;
		result[6] = z.y;
		result[10] = z.z;
		result[14] = -Vector3::dot(z, eye);

		result[3] = result[7] = result[11] = 0.0f;
		result[15] = 1.0f;
		return result;
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
	
	Matrix Matrix::operator*(const Matrix& b) {
		Matrix mat;
		for (int i = 0; i < 16; ++i)
		{
			float value = 0.0;
			for (int j = 0; j < 4; ++j)
			{
				value += m[int(i / 4) * 4 + j] * b.m[j * 4 + (i % 4)];
			}
			mat.m[i] = value;
		}
		return mat;
	}
	
	Matrix& Matrix::operator*=(const Matrix& mat) {
		return (*this);
	}

	float& Matrix::operator[](int idx) {
		return m[idx];
	}
}