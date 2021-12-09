#include "EventScene.h"
#include "SpaceDome.h"
#include "BossShip.h"
#include "SceneManager.h"
#include "Camera.h"
#include "TimeCount.h"
#include "BulletManager.h"

EventScene::EventScene(SceneManager* manager):SceneBase(manager)
{
}

void EventScene::Init(void)
{
	mSpaceDome = new SpaceDome(mSceneManager);
	mSpaceDome->Init();
	mBulletManager = std::make_shared<BulletManager>();

	bossShip_ = std::make_shared<BossShip>(VGet(0,0,-1500),*mBulletManager);

	mSceneManager->GetCamera()->ChangeMode(CAMERA_MODE::FIXED);
}

void EventScene::Update(void)
{
	bossShip_->EventUpdate();
	mBulletManager->Update();

	cnt_ += TimeCount::GetDeltaTime();

	if (cnt_ > 5.0f)
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
	}
}

void EventScene::Draw(void)
{
	mSpaceDome->Draw();
	bossShip_->Draw();
	mBulletManager->Draw();

}

void EventScene::Release(void)
{
	mSpaceDome->Release();
}
