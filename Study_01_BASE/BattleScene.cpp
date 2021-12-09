#include "BattleScene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "SpaceDome.h"
#include "Player.h"
#include "DebriManager.h"
#include "BossShip.h"
#include "BulletManager.h"

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
	if (bossShip_->CollisionCheck(mPlayer))
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
		return;
	}

	mBulletManager->Update();

	// ƒfƒuƒŠ¶¬
	mDebriManager->MakeDebri(mPlayer->GetTransform().pos);
}

void BattleScene::Draw(void)
{
	mSpaceDome->Draw();
	mPlayer->Draw();
	mBulletManager->Draw();

	bossShip_->Draw();
	mDebriManager->Draw(mPlayer->GetTransform().pos);
}

void BattleScene::Release(void)
{
	mSpaceDome->Release();
}
