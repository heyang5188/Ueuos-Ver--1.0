#include "Transform.h"

namespace Math {
	void Transform::addTo(Transform * trans)
	{
		//assert(parentTransform ==0 £¬"ParentTransform Must Be Null");
		parentTransform = trans;
	}

	Transform * Transform::getParent()
	{
		return parentTransform;
		return nullptr;
	}

	void Transform::doTranslate(Vector3 vec)
	{
		position = vec;
	}

	void Transform::doRotate(Vector3 euler)
	{
		rotation = Quaternion(euler);
	}

	void Transform::doScale(Vector3 scale)
	{
		this->scale = scale;
	}

	Vector3 Transform::getUp()
	{
		return Vector3(modelMatrix[4],modelMatrix[5],modelMatrix[6]);
	}

	Vector3 Transform::getRight()
	{
		return Vector3(modelMatrix[0], modelMatrix[1], modelMatrix[2]);
	}

	Vector3 Transform::getForward()
	{
		return Vector3(modelMatrix[8], modelMatrix[9], modelMatrix[10]);
	}

	Matrix Transform::getModelMatrix()
	{
		Matrix scaleMat = Matrix();
		makeScaleMatrix(scaleMat);
		Matrix transMat = Matrix(Matrix::indentity);
		makeTranslationMatrix(transMat);
		Matrix rotMat = Matrix();
		makeRotationMatrix(rotMat);
		modelMatrix = scaleMat*rotMat*transMat;
		return modelMatrix;
	}

	Matrix & Transform::getModelMatrix(Matrix & out)
	{
		memcpy(&out, &modelMatrix, sizeof(modelMatrix));
		return out;
	}

	void Transform::updateModleMatrix()
	{

		Matrix scaleMat = Matrix();
		makeScaleMatrix(scaleMat);
		Matrix transMat = Matrix(Matrix::indentity);
		makeTranslationMatrix(transMat);
		Matrix rotMat = Matrix();
		makeRotationMatrix(rotMat);
		modelMatrix = scaleMat*rotMat*transMat;
		
	}

	void Transform::makeScaleMatrix(Matrix & scaleMatrix)
	{
		scaleMatrix[0] = scale[0];
		scaleMatrix[5] = scale[1];
		scaleMatrix[10] = scale[2];
		scaleMatrix[15] = 1.0;
	}

	void Transform::makeTranslationMatrix(Matrix & transMatrix)
	{

		transMatrix[12] = position.x;
		transMatrix[13] = position.y;
		transMatrix[14] = position.z;
		transMatrix[15] = 1.0;
	}

	void Transform::makeRotationMatrix(Matrix & rotMatrix)
	{
		rotMatrix = Quaternion(rotation).getRotationMatrix();
	}

}
