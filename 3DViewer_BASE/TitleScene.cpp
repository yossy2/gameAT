#include "DxLib.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "Stage.h"
#include "Unit.h"
#include "Camera.h"
#include "SceneManager.h"
#include "TitleScene.h"

VERTEX3DSHADER Vert[6];
int vs_, ps_,g_;

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mStage = new Stage(mSceneManager);
	mStage->Init();

	mUnit = new Unit(mSceneManager);
	mUnit->Init();

	auto camera = mSceneManager->GetCamera();
	camera->SetTarget(mUnit);

	vs_ = LoadVertexShader("ShaderPolygon3DTestVS.vso");
	ps_ = LoadPixelShader("ShaderPolygon3DTestPS.pso");

	Vert[0].pos = VGet(100.0f, 356.0f, 0.0f);
	Vert[1].pos = VGet(356.0f, 356.0f, 0.0f);
	Vert[2].pos = VGet(100.0f, 100.0f, 0.0f);
	Vert[3].pos = VGet(356.0f, 100.0f, 0.0f);
	Vert[0].dif = GetColorU8(255, 255, 255, 255);
	Vert[1].dif = GetColorU8(255, 255, 255, 255);
	Vert[2].dif = GetColorU8(255, 255, 255, 255);
	Vert[3].dif = GetColorU8(255, 255, 255, 255);
	Vert[0].u = 0.0f; Vert[0].v = 0.0f;
	Vert[1].u = 1.0f; Vert[1].v = 0.0f;
	Vert[2].u = 0.0f; Vert[3].v = 1.0f;
	Vert[3].u = 1.0f; Vert[2].v = 1.0f;
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	g_ = LoadGraph("icon.png");
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
	//mStage->Draw();
	mUnit->Draw();
	DrawDebug();

	SetUseVertexShader(vs_);
	SetUsePixelShader(ps_);
	SetUseTextureToShader(0, g_);
	//DrawPolygonIndexed3D(vertexes_.data(), vertexes_.size(), indexes_.data(), vertexes_.size() - 2, DX_NONE_GRAPH, TRUE);
	//DrawPolygonIndexed3DToShader(vertexes_.data(), vertexes_.size(), indexes_.data(), vertexes_.size() - 2);
	DrawPolygon3DToShader(Vert, 2);
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
