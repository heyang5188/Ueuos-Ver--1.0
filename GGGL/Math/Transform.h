#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <assert.h>
#include <vector>

namespace Math {
	//class Ueuos::UeuosObject;
	class Transform {
	public:
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		Matrix	   modelMatrix;
		Transform* parentTransform;
		void*	   object;
		//Ueuos::UeuosObject* object;
	public:
		Transform():
			position(0,0,0),
			parentTransform(nullptr),
			rotation(Quaternion::identity),
			scale(Vector3::one)
		{
			updateModleMatrix();
		}

		Transform(Vector3 pos,Vector3 rot,Vector3 scl):
			position(pos),
			rotation(Quaternion(rot)),
			scale(scl)
		{
			updateModleMatrix();
		}

		void addTo(Transform* trans);
		void addChild(Transform* child);
		Transform* getParent();
		std::vector<Transform*> getChildren();

		void doTranslate(Vector3 vec);
		void doRotate(Vector3 euler);
		void doScale(Vector3 scale);


		Vector3 getUp();
		Vector3 getRight();
		Vector3 getForward();

	public:
		Matrix getModelMatrix();
		Matrix& getModelMatrix(Matrix& out);
		void updateModleMatrix();
	private:
		std::vector<Transform*> children;

		void makeScaleMatrix(Matrix& scaleMatrix);
		void makeTranslationMatrix(Matrix& transMatrix);
		void makeRotationMatrix(Matrix& rotMatrix);

		friend class AbstractDrawCommand;
	};
}