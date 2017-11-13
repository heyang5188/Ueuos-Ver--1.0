#pragma once

//#include ""
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>
#include <memory>
#include <GL/glew.h>

namespace Ueuos {
	using namespace Math;

	struct Color3F
	{
		Color3F(float rr, float gg, float bb) :_r(rr), _g(gg), _b(bb) {
		}
		Color3F(){
			memset(this,0,sizeof(Color3F));
		}
		float _r;
		float _g;
		float _b;
	};
	struct Color4F : public Color3F
	{
		Color4F(float rr, float gg, float bb, float aa) :Color3F(rr, gg, bb), _alpha(aa) {}
		Color4F() {
			memset(this, 0, sizeof(Color4F));
		}
		float   _alpha;
	};
	struct VertexInfo
	{
		VertexInfo(const Math::Vector3& vec, const Color4F& col):position(vec),color(col) {}
		Math::Vector3 position;
		Color4F color;
	};
	class IVertexInterface {
	public:
		//virtu
		virtual ~IVertexInterface() {}
		virtual void buferData(std::vector<VertexInfo>& data)=0;
		virtual void onDraw()=0;
	protected:
		std::vector<VertexInfo> _verties;
		GLuint vao;
	};
}