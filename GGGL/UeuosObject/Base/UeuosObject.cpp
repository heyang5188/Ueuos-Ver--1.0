#include "UeuosObject.h"
using namespace Ueuos;
using namespace Math;

UeuosObject::UeuosObject() :
	transform(),
	isModelDirty(true)
{
	updateModeMatrix();
}

Matrix & Ueuos::UeuosObject::getModelMatrix()
{
	if (isModelDirty)
	{
		updateModeMatrix();
		isModelDirty = false;
	}
	return modelMatrix;
}

void UeuosObject::updateModeMatrix() {
	transform.getModelMatrix(modelMatrix);
}

void UeuosObject::setPostion(const Vector3& newPostion) {
	isModelDirty = true;
	transform.position = newPostion;
}

void UeuosObject::setRotation(const Vector3& euler) {
	isModelDirty = true;
	transform.rotation = euler;
}

void UeuosObject::setScale(const Vector3& scale) {
	isModelDirty = true;
	transform.scale = scale;
}


