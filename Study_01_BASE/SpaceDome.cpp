#include "SpaceDome.h"
#include "AsoUtility.h"

SpaceDome::SpaceDome(SceneManager* manager)
{
	
}

void SpaceDome::Init(void)
{
	mTransform.SetModel(MV1LoadModel("Model/SkyDome/SkyDome.mv1"));
	float scale = 1.0;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = AsoUtility::VECTOR_ZERO;

	mTransform.Update();
}

void SpaceDome::Update(void)
{
}

void SpaceDome::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void SpaceDome::Release(void)
{
	MV1DeleteModel(mTransform.modelId);
}
