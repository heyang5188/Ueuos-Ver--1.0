#pragma once
#include "AbstractDrawCommand.h"


class QuadCommand : public AbstractDrawCommand
{
public:

	QuadCommand(Vector3 origin, Vector3 end);
	QuadCommand(Vector3 topLeft, Vector3 bottomLeft, Vector3 topRight, Vector3 bottomRight);
	~QuadCommand();
	virtual void doDraw() override;
protected:
	virtual void applyVertexData();
};

