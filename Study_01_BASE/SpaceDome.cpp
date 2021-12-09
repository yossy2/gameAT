#include "SpaceDome.h"
#include "AsoUtility.h"
#include "Player.h"

SpaceDome::SpaceDome(SceneManager* manager)
{
	
}

void SpaceDome::Init(void)
{
	mTransform.SetModel(MV1LoadModel("Model/SkyDome/SkyDome.mv1"));
	float scale = 2.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = AsoUtility::VECTOR_ZERO;

	mTransform.Update();
}

void SpaceDome::Update(void)
{
	if (mPlayer.expired()) return;
	mTransform.pos = mPlayer.lock()->GetTransform().pos;
	mTransform.Update();
}

void SpaceDome::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void SpaceDome::Release(void)
{
	MV1DeleteModel(mTransform.modelId);
}

void SpaceDome::SetPlayer(std::shared_ptr<Player> player)
{
	mPlayer = player;
}
