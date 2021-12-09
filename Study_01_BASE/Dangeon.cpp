#include "Dangeon.h"

Dangeon::Dangeon()
{
	mTransform.SetModel(MV1LoadModel("Model/Rock/Dungeon.mv1"));

	float scale = 1.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(DX_PI_F / 2.0f, -DX_PI_F / 2.0f, 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = VGet(-0,-3000.0f,0);

	mTransform.Update();
}

Dangeon::~Dangeon()
{
	MV1DeleteModel(mTransform.modelId);
}

void Dangeon::Draw()
{
	MV1DrawModel(mTransform.modelId);
}
