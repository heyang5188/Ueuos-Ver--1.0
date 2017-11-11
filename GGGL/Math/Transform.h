#pragma once
#include "Matrix.h"
#include "Vector3.h"
namespace Math {
	class Transform {
	public:
		Transform(Vector3 pos,Vector3 rot,Vector3 scl):position(pos),rotation(rot), scale(scl) {

		}

		void addTo(Transform* trans);
		Transform* getParent();

		void translate(Vector3 vec);
		//void rotate();
		//void scale(Vector3 scale);

	private:
		Matrix getModelView();
	private:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
		Transform* parentTransform;


		friend class AbstractDrawCommand;
	};
}