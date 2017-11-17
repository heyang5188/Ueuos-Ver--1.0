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
		mat[9] = (right + left) / (right - left);
		mat[5] = 2 * near / (top-bottom);
		mat[9] = (top+bottom) / (top - bottom);
		mat[10] = -(far + near) / (far - near);
		mat[14] = -2*far* near / (far - near);
		mat[11] = -1;
		return mat;
	}

	Matrix Matrix::createPerspective(float fov, float aspect, float near, float far)
	{
		Matrix rlt;
		const float tanHalfFovy = tan(fov / 2);
		rlt[0] = 1 / (aspect * tanHalfFovy);
		rlt[5] = 1 / (tanHalfFovy);
		rlt[10] = -(near + far) / (far - near);
		rlt[11] = -1;
		rlt[14] = -2 * far * near / (far - near);
		

		return rlt;
	}

	Matrix Matrix::createOrthographic(float l, float r, float t, float b, float n, float f)
	{
		Matrix mat;
		mat[0] = 2 / (r - l);
		mat[3] = -(r + l) / (r - l);
		mat[5] = 2 / (t - b);
		mat[7] = -(t + b) / (t - b);
		mat[10] = 2 / (f - n);
		mat[11] = -(f + n) / (f - n);
		mat[15] = 1;
		return mat;
	}


	Matrix Matrix::lookAt(const Math::Vector3& eye, const Vector3& target, const Vector3& up)
	{		
		using Math::Vector3;

		//View Plane Normal ,acting like Z-axis 
		Vector3 VPN = target - eye;
		Vector3 n = Vector3::normalized(VPN);
		Vector3 Vup = Vector3::normalized(up);
		//like X-axis
		Vector3 u = Vector3::normalized(Vector3::cross(n, Vup));
		//like Y 
		Vector3 v = Vector3::normalized(Vector3::cross(u, n));

		Matrix mat;
		float invser[] = {
			u.x,  v.x, -n.x, 0,
			u.y,  v.y, -n.y, 0,
			u.z,  v.z, -n.z, 0,
			-Vector3::dot(eye,u),-Vector3::dot(eye,v),  Vector3::dot(eye,n),1.0
		};
		mat = invser;
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