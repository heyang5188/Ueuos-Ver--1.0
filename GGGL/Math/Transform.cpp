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
		//this->rotation = Quaternion::identity;
		rotation = Quaternion(euler);
	}

	void Transform::doScale(Vector3 scale)
	{
		this->scale = scale;
	}

	Matrix Transform::getModelMatrix()
	{
		//all zero 
		Matrix scaleMat = Matrix();
		makeScaleMatrix(scaleMat);
		Matrix transMat = Matrix(Matrix::indentity);
		makeTranslationMatrix(transMat);
		Matrix rotMat = Matrix();
		makeRotationMatrix(rotMat);

		return transMat*rotMat*scaleMat;			
	}

	Matrix & Transform::getModelMatrix(Matrix & out)
	{
		memset(&out,0,sizeof(out));
		Matrix scaleMat = Matrix();
		makeScaleMatrix(scaleMat);
		Matrix transMat = Matrix(Matrix::indentity);
		makeTranslationMatrix(transMat);
		Matrix rotMat = Matrix();
		makeRotationMatrix(rotMat);
		out = transMat*rotMat*scaleMat;
		return out;
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

		transMatrix[3] = position.x;
		transMatrix[7] = position.y;
		transMatrix[11] = position.z;
		// TODO: insert return statement here
	}

	void Transform::makeRotationMatrix(Matrix & rotMatrix)
	{
		rotMatrix = Quaternion(rotation).getRotationMatrix();
		// TODO: insert return statement here
	}

}
