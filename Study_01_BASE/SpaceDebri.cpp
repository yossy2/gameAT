#include "SpaceDebri.h"
#include <DxLib.h>

SpaceDebri::SpaceDebri(int modelID, const Transform& transform):mTransform(transform)
{
	mModelID = MV1DuplicateModel(modelID);

	mTransform.SetModel(mModelID);
	mTransform.Update();
}

SpaceDebri::~SpaceDebri()
{
	MV1DeleteModel(mModelID);
}

void SpaceDebri::Draw()
{
	MV1DrawModel(mModelID);
}
