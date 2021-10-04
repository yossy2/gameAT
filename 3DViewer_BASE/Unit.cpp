#include "Unit.h"
#include "SceneManager.h"
#include "Camera.h"
#include "AsoUtility.h"
#include "RollBall.h"

namespace
{
	float moveSpeed = 200.0f;
}

Unit::Unit(SceneManager* manager)
{
	mSceneManager = manager;
}

void Unit::Init()
{
	mModelID = MV1LoadModel("Model/Human.mv1");
	mPos = { 0.0f,0.0f,0.0f };
	MV1SetPosition(mModelID, mPos);

	// 再生するアニメーションの設定
	mAnimWalk = MV1AttachAnim(mModelID, 1);
	
	// アニメーション総再生時間の取得
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModelID, mAnimWalk);
	mStepAnim = 0.0f;
	MV1SetAttachAnimTime(mModelID, mAnimWalk, mStepAnim);

	mAnimSpeed = 50.0f;

	mBall = new RollBall(mSceneManager, this);
	mBall->Init();
}

void Unit::Update()
{
	float deltaTime = mSceneManager->GetDeltaTime();

	mStepAnim += deltaTime * mAnimSpeed;

	if (mStepAnim > mTimeTotalAnimWalk)
	{
		mStepAnim = 0.0f;
	}

	MV1SetAttachAnimTime(mModelID, mAnimWalk, mStepAnim);

	Move();
	mBall->Update();
}

void Unit::Draw()
{
	MV1DrawModel(mModelID);

	DrawFormatString(0, 50, 0xffffff, "キャラ座標：(%.1f,%.1f,%.1f)", mPos.x, mPos.y, mPos.z);
	DrawFormatString(0, 70, 0xffffff, "キャラ回転：(%.1f,%.1f,%.1f)", mAngles.x, mAngles.y, mAngles.z);

	mBall->Draw();
}

void Unit::Release()
{
	MV1DeleteModel(mModelID);
	mBall->Release();
	delete mBall;
}

VECTOR Unit::GetPos() const
{
	return mPos;
}

VECTOR Unit::GetForward() const
{
	VECTOR ret;
	VECTOR forward = { 0.0,0.0,-1.0f };

	VectorRotationY(&ret, &forward, -mAngles.y);

	return ret;
}

void Unit::Move()
{
	auto camera = mSceneManager->GetCamera();
	const auto& angle = camera->GetAngle();
	float deltatime = mSceneManager->GetDeltaTime();
	VECTOR move = {0,0,0};

	if (CheckHitKey(KEY_INPUT_W))
	{
		VECTOR add = {0,0,1.0f};
		VECTOR tmp = {0,0,0};
		VectorAdd(&tmp, &move, &add);

		move = tmp;

	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		VECTOR add = { 0,0,-1.0f };
		VECTOR tmp = { 0,0,0 };

		VectorAdd(&tmp, &move, &add);

		move = tmp;
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		VECTOR add = { 1.0f,0,0 };
		VECTOR tmp = { 0,0,0 };

		VectorAdd(&tmp, &move, &add);

		move = tmp;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		VECTOR add = { -1.0f,0,0 };
		VECTOR tmp = { 0,0,0 };

		VectorAdd(&tmp, &move, &add);

		move = tmp;
	}

	if (move.x == 0 && move.y == 0 && move.z == 0) return;

	VECTOR normal,rot,scale,add;
	VECTOR dir;

	// カメラの方向から移動方向を算出
	VECTOR targetToCamera = camera->GetVecTargetToCamera();
	targetToCamera.y = 0;
	normal = targetToCamera;
	VectorNormalize(&targetToCamera, &normal);
	rot = targetToCamera;
	VectorRotationY(&targetToCamera,&rot, atan2f(move.z, move.x) + DX_PI_F / 2.0f);
	scale = targetToCamera;
	VectorScale(&targetToCamera, &scale, moveSpeed * deltatime);
	add = mPos;
	VectorAdd(&mPos, &add, &targetToCamera);

	/*mAngles.y = atan2f(-move.z,move.x) + DX_PI_F / 2.0f;

	VectorNormalize(&normal, &move);
	VectorRotationY(&rot, &normal, -angle.y);
	VectorScale(&scale, &rot, moveSpeed * deltatime);

	

	VectorAdd(&add, &mPos, &scale);*/

	//mPos = targetToCamera;

	MV1SetPosition(mModelID, mPos);

	mAngles.y = atan2f(targetToCamera.z, -targetToCamera.x) + DX_PI_F / 2.0f;
	MV1SetRotationXYZ(mModelID, mAngles);
}
