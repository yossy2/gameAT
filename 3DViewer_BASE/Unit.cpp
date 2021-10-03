#include "Unit.h"
#include "SceneManager.h"
#include "Camera.h"

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

}

void Unit::Draw()
{
	MV1DrawModel(mModelID);

	DrawFormatString(0, 50, 0xffffff, "キャラ座標：(%.1f,%.1f,%.1f)", mPos.x, mPos.y, mPos.z);
	DrawFormatString(0, 70, 0xffffff, "キャラ回転：(%.1f,%.1f,%.1f)", mAngles.x, mAngles.y, mAngles.z);
}

void Unit::Release()
{
	MV1DeleteModel(mModelID);
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

	mAngles.y = atan2f(-move.z,move.x) - DX_PI_F / 2.0f;

	VectorNormalize(&normal, &move);
	VectorRotationY(&rot, &normal, -angle.y);
	VectorScale(&scale, &rot, moveSpeed * deltatime);

	

	VectorAdd(&add, &mPos, &scale);

	mPos = add;

	MV1SetPosition(mModelID, mPos);
	MV1SetRotationXYZ(mModelID, mAngles);
}
