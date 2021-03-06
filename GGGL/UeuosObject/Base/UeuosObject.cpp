#include "UeuosObject.h"
using namespace Ueuos;
using namespace Math;

UeuosObject::UeuosObject():
	transform(),
	isModelDirty(true)
{
	transform.object = this;
	updateModelMatrix();
}

Matrix & Ueuos::UeuosObject::getModelMatrix()
{
	if (isModelDirty)
	{
		updateModelMatrix();
		isModelDirty = false;
	}
	return transform.modelMatrix;
}

void Ueuos::UeuosObject::addChild(Transform * child)
{
	transform.addChild(child);
//	child->addTo(&transform);
	//transform
}

void UeuosObject::updateModelMatrix() {
	transform.updateModleMatrix();
}

void Ueuos::UeuosObject::draw(const Matrix & parentMatrix)
{
	onDraw(Matrix::indentity);
}

void UeuosObject::setPostion(const Vector3& newPostion) {
	isModelDirty = true;
	transform.position = newPostion;
}

Vector3 Ueuos::UeuosObject::getPosition()
{
	return transform.position;
}

void UeuosObject::setRotation(const Vector3& euler) {
	isModelDirty = true;
	transform.rotation = euler;
}

void UeuosObject::setScale(const Vector3& scale) {
	isModelDirty = true;
	transform.scale = scale;
}

void UeuosObject::draw() {
	draw(Matrix::indentity);
}

Transform & Ueuos::UeuosObject::getTransform()
{
	return transform;
}


