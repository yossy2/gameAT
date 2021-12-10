#include "BattleScene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "SpaceDome.h"
#include "Player.h"
#include "DebriManager.h"
#include "BossShip.h"
#include "BulletManager.h"
#include "TimeCount.h"
BattleScene::BattleScene(SceneManager* manager):SceneBase(manager)
{
}

void BattleScene::Init(void)
{
	mSpaceDome = new SpaceDome(mSceneManager);
	mSpaceDome->Init();
	mBulletManager = std::make_shared<BulletManager>();
	mPlayer = std::make_shared<Player>(mSceneManager,*mBulletManager);

	mSceneManager->GetCamera()->SetPlayer(mPlayer);
	mSpaceDome->SetPlayer(mPlayer);
	mDebriManager = std::make_shared<DebriManager>();
	mDebriManager->MakeDebri(mPlayer->GetTransform().pos);
	bossShip_ = std::make_shared<BossShip>(VGet(0, -1000, 3000),*mBulletManager);
}

void BattleScene::Update(void)
{
	mPlayer->Update();
	mSpaceDome->Update();
	bossShip_->Update();
	mBulletManager->Update();

	if (restartCnt > 0)
	{
		restartCnt -= TimeCount::GetDeltaTime();

		if (restartCnt <= 0)
		{
			mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
		}
		return;
	}

	if (bossShip_->CollisionCheck(mPlayer))
	{
		mPlayer->Dead();
		restartCnt = 2.0f;
		return;
	}


	// ƒfƒuƒŠ¶¬
	mDebriManager->MakeDebri(mPlayer->GetTransform().pos);
}

void BattleScene::Draw(void)
{
	mSpaceDome->Draw();
	mBulletManager->Draw();

	bossShip_->Draw();
	mDebriManager->Draw(mPlayer->GetTransform().pos);
	mPlayer->Draw();
}

void BattleScene::Release(void)
{
	mSpaceDome->Release();
}
