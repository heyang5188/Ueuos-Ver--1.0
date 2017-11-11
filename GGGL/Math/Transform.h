#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Math {
	class Transform {
	public:
		Transform(Vector3 pos,Vector3 rot,Vector3 scl):position(pos),rotation(Quaternion::identity), scale(scl) {

		}

		void addTo(Transform* trans);
		Transform* getParent();

		void doTranslate(Vector3 vec);
		void doTotate();
		void doScale(Vector3 scale);

	private:
		Matrix getModelView();
	private:
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		Transform* parentTransform;


		friend class AbstractDrawCommand;
	};
}