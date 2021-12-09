#include <cmath>
#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "SpaceDome.h"
#include "Stage.h"
#include "Player.h"
#include "DebriManager.h"
#include "Dangeon.h"
#include "BossShip.h"
#include "BulletManager.h"

namespace
{
	
}

GameScene::GameScene(SceneManager* manager) : SceneBase(manager)
{
}

void GameScene::Init(void)
{
	mSpaceDome = new SpaceDome(mSceneManager);
	mSpaceDome->Init();

	mStage = new Stage(mSceneManager);
	mStage->Init();
	mBulletManager = std::make_shared<BulletManager>();
	mPlayer = std::make_shared<Player>(mSceneManager, *mBulletManager);

	mSceneManager->GetCamera()->SetPlayer(mPlayer);
	mSpaceDome->SetPlayer(mPlayer);
	mDebriManager = std::make_shared<DebriManager>();
	mDebriManager->MakeDebri(mPlayer->GetTransform().pos);
	dangeon_ = std::make_shared<Dangeon>();
	bossShip_ = std::make_shared<BossShip>(VGet(3000,0,3000),*mBulletManager);
}

void GameScene::Update(void)
{
	mPlayer->Update();
	mSpaceDome->Update();
	mBulletManager->Update();
	

	bossShip_->Update();

	if (dangeon_->CollisionCheck(mPlayer))
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::GAME, true);
		return;
	}

	// シーン遷移
	auto& p = mPlayer->GetTransform();
	auto& b = bossShip_->GetTransform();
	if (VSquareSize(VSub(p.pos,b.pos)) < 2500.0f * 2500.0f)
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}

	// デブリ生成
	mDebriManager->MakeDebri(mPlayer->GetTransform().pos);
}

void GameScene::Draw(void)
{
	mSpaceDome->Draw();
	mStage->Draw();
	mPlayer->Draw();
	mBulletManager->Draw();
	dangeon_->Draw();
	bossShip_->Draw();
	mDebriManager->Draw(mPlayer->GetTransform().pos);
}

void GameScene::Release(void)
{
	mSpaceDome->Release();
}
