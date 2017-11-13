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
		//View Plane Normal ,acting like Z-axis 
		Vector3 VPN = target - eye;
		Vector3 n = Vector3::normalized(VPN);
		Vector3 Vup = Vector3::normalized(up);
		//like X-axis
		Vector3 u = Vector3::normalized(Vector3::cross(VPN, Vup));
		//like Y 
		Vector3 v = Vector3::normalized(Vector3::cross(u, n));
		// A = TR --- > inverse(A) = inverse(TR) ---> inverse(A) = inverse(R)*inverse(T)
		Matrix mat;
		float inverseT[] = {
			1.0,0.0,0.0,0.0,
			0.0,1.0,0.0,0.0,
			0.0,0.0,1.0,0.0,
			eye.x,eye.y,eye.z,1.0 };
		Matrix inverseTMat(inverseT);
		float invserR[] = {
			u.x,  u.y, u.z,0.0,
			v.x,  v.y, v.z,0.0,
			-n.x,-n.y,-n.z,0.0,
			0.0,  0.0, 0.0,1.0
		};
		Matrix inverseRMat(invserR);
		mat = inverseTMat*inverseRMat;
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