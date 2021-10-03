#include "DxLib.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "Stage.h"
#include "Unit.h"
#include "Camera.h"
#include "SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mStage = new Stage(mSceneManager);
	mStage->Init();

	mUnit = new Unit(mSceneManager);
	mUnit->Init();
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

	mStage->Update();
	mUnit->Update();
}

void TitleScene::Draw(void)
{
	mStage->Draw();
	mUnit->Draw();
	DrawDebug();
}

void TitleScene::DrawDebug(void)
{
	auto camera = mSceneManager->GetCamera();

	auto pos = camera->GetPosition();
	auto angles = camera->GetAngle();

	DrawFormatString(0, 10, 0xffffff, "カメラ座標：(%.1f,%.1f,%.1f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 30, 0xffffff, 
		"カメラ角度：(%.1f,%.1f,%.1f)", AsoUtility::Rad2DegF(angles.x), AsoUtility::Rad2DegF(angles.y), AsoUtility::Rad2DegF(angles.z));
}

void TitleScene::Release(void)
{
	mStage->Release();
	mUnit->Release();
	delete mStage;
}
