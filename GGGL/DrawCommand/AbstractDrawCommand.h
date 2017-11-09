#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
using namespace std;


struct Vector2
{
	explicit Vector2(float xx,float yy):x(xx),y(yy){}
	float x;
	float y;
};

struct Size
{
	explicit Size(float ww, float hh) :_w(ww), _h(hh) {}
	float _w;
	float _h;
};

struct Vector3 : public Vector2
{

	explicit Vector3(float xx,float yy,float zz=0.0):Vector2(xx,yy),_z(zz){}
	float _z;
};

struct Color3F
{
	Color3F(float rr,float gg,float bb):_r(rr),_g(gg),_b(bb) {
	}
	float _r;
	float _g;
	float _b;
};

struct Color4F : public Color3F
{
	Color4F(float rr, float gg, float bb,float aa):Color3F(rr,gg,bb),_alpha(aa){}
	float   _alpha;
};


struct VertexInfo
{
	VertexInfo(float x, float y, float z,float r,float g,float b,float a=1.0):position(x,y,z),color(r,g,b,a){
	}

	VertexInfo(Vector3 pos, Color4F clr = Color4F(1.0,1.0,1.0,1.0)) :position(pos),color(clr){}

	Vector3 position;
	Color4F color;
};


class AbstractDrawCommand
{
public:
	AbstractDrawCommand() : _vao(0){

	}
	virtual ~AbstractDrawCommand() {
		_vao = 0;
		_verties.clear();
	}
	void setVertexData(vector<VertexInfo> verties) {
		vector<VertexInfo>().swap(_verties);
		_verties = vector<VertexInfo>(verties.begin(), verties.end());
		applyVertexData();
	}
	GLuint getVAO() { return _vao; }

	virtual void doDraw() {};
protected:
	virtual void applyVertexData() {};

protected:
	GLuint _vao;
protected:
	vector<VertexInfo> _verties;
};
