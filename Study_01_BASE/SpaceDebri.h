#pragma once
#include "Transform.h"

class SpaceDebri
{
private:
	Transform mTransform;
	int mModelID;

public:
	SpaceDebri(int modelID,const Transform& transform);
	~SpaceDebri();
	void Draw();
};

