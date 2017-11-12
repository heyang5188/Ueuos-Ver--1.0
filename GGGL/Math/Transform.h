#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <assert.h>

namespace Math {
	class Transform {
	public:
		Transform():position(0,0,0),rotation(Quaternion::identity),scale(Vector3::one){}

		Transform(Vector3 pos,Vector3 rot,Vector3 scl):position(pos),rotation(Quaternion(rot)), scale(scl) {

		}

		void addTo(Transform* trans);
		Transform* getParent();

		void doTranslate(Vector3 vec);
		void doRotate(Vector3 euler);
		void doScale(Vector3 scale);

	public:
		Matrix getModelMatrix();
	private:
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		Transform* parentTransform;


		void makeScaleMatrix(Matrix& scaleMatrix);
		void makeTranslationMatrix(Matrix& transMatrix);
		void makeRotationMatrix(Matrix& rotMatrix);


		friend class AbstractDrawCommand;
	};
}