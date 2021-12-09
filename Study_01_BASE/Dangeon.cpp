#include "Dangeon.h"
#include "Player.h"

Dangeon::Dangeon()
{
	mTransform.SetModel(MV1LoadModel("Model/Rock/Dungeon.mv1"));

	float scale = 1.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(DX_PI_F / 2.0f, -DX_PI_F / 2.0f, 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = VGet(-0,-3000.0f,0);

	mTransform.Update();

	MV1SetupCollInfo(mTransform.modelId, -1, 8, 8, 8);
}

Dangeon::~Dangeon()
{
	MV1DeleteModel(mTransform.modelId);
}

void Dangeon::Draw()
{
	MV1DrawModel(mTransform.modelId);
}

bool Dangeon::CollisionCheck(std::shared_ptr<Player> player)
{
	VECTOR start, end;
	float radius;

	player->GetCapsule(start, end, radius);
	auto hit = MV1CollCheck_Capsule(mTransform.modelId, -1, start, end, radius);

	if (hit.HitNum == 0)
	{
		MV1CollResultPolyDimTerminate(hit);
		return false;
	}
	MV1CollResultPolyDimTerminate(hit);
	return true;
}
