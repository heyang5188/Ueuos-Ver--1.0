#pragma once
#include "../../Math/Transform.h"
#include "../../Math/Quaternion.h"
#include "../../Math/Matrix.h"

namespace Ueuos {
	using namespace Math;
	class UeuosObject {
	public:
		UeuosObject();
		
		//set object's postion to newPostion
		void setPostion(const Vector3& newPostion);
		//set object's rotation to newRotation(euler)
		void setRotation(const Vector3&  euler);

		void setScale(const Vector3& scale);
		//
		//void tranlate(const Vector3& deltaPos);
		//void rotate(const Vector3& deltaEuler);
		//void scale(const Vector3& deltaScale);

		Matrix& getModelMatrix();

	protected:
		void updateModeMatrix();
		
	private: 
		Transform transform;
		Matrix modelMatrix;
		bool isModelDirty;
	};

}