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

GameScene::GameScene(SceneManager* manager) : SceneBase(manager)
{
}

void GameScene::Init(void)
{
	mSpaceDome = new SpaceDome(mSceneManager);
	mSpaceDome->Init();

	mStage = new Stage(mSceneManager);
	mStage->Init();

	mPlayer = std::make_shared<Player>(mSceneManager);

	mSceneManager->GetCamera()->SetPlayer(mPlayer);
	mSpaceDome->SetPlayer(mPlayer);
}

void GameScene::Update(void)
{
	mPlayer->Update();
	mSpaceDome->Update();

	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}

}

void GameScene::Draw(void)
{
	mSpaceDome->Draw();
	mStage->Draw();
	mPlayer->Draw();
}

void GameScene::Release(void)
{
	mSpaceDome->Release();
}
