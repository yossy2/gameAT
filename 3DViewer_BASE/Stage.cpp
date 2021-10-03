#include "Stage.h"
#include "SceneManager.h"

Stage::Stage(SceneManager* manager)
{
	mSceneManager = manager;
}

void Stage::Init()
{
	mModelID = MV1LoadModel("Model/Stage.mv1");
	mModelPos = { 0.0f,-100.0f,0.0f };
	MV1SetPosition(mModelID, mModelPos);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	// XYZ‚ÌƒOƒŠƒbƒhü•`‰æ
	for (int i = 0; i <= 10; i++)
	{
		float offset = 100.0f * i;

		// x•ûŒü
		DrawLine3D({ -500.0f,0.0f,-500.0f + offset}, { 500.0f,0.0f,-500.0f + offset }, 0xaa0033);
		DrawLine3D({ -500.0f + offset,0.0f,-500.0f}, { -500.0f + offset,0.0f,500.0f }, 0x0000ff);
	}

	DrawLine3D({ 0.0f,-500.0f,0.0f}, { 0.0f,500.0f,0.0f}, 0x00ff00);

	//MV1DrawModel(mModelID);
}

void Stage::Release()
{
	MV1DeleteModel(mModelID);
}
