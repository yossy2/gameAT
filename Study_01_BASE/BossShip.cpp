#include "BossShip.h"

BossShip::BossShip()
{
	mTransform.SetModel(MV1LoadModel("Model/BossShip/BossShip.mv1"));

	float scale = 1.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0, 0, 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = VGet(800, 14000.0f, -800.0f);

	mTransform.Update();
}

BossShip::~BossShip()
{
	MV1DeleteModel(mTransform.modelId);
}

void BossShip::Draw()
{
	MV1DrawModel(mTransform.modelId);
}
