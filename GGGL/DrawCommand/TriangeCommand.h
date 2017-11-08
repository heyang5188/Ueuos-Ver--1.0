#pragma once
#include "AbstractDrawCommand.h"
class TriangeCommand :
	public AbstractDrawCommand
{
public:
	TriangeCommand();
	~TriangeCommand();
	virtual void doDraw();
protected:
	virtual void applyVertexData();


};

