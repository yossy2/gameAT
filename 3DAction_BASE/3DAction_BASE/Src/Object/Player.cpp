#include <string>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "Common/AnimationController.h"
#include "Common/Capsule.h"
#include "Common/Collider.h"
#include "Common/SpeechBalloon.h"
#include "Planet.h"
#include "Player.h"
#include "../Common/TimeCount.h"

namespace
{
	constexpr float walk_speed = 300.0f;
	constexpr float run_speed = 500.0f;
	constexpr float rot_time = 0.1f;
	constexpr float jump_pow = 50.0f;
	constexpr float max_fall_speed = 50.0f;
}

Player::Player(SceneManager* manager)
{
	mSceneManager = manager;
	mResourceManager = manager->GetResourceManager();
	mGravityManager = manager->GetGravityManager();

	mAnimationController = nullptr;
	mState = STATE::NONE;
}

void Player::Init(void)
{
	// モデルの基本設定
	mTransform.SetModel(mResourceManager->LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	mTransform.scl = AsoUtility::VECTOR_ONE;
	mTransform.pos = { 0.0f, -30.0f, 0.0f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = 
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });
	mTransform.Update();
	mPlayerRotY = Quaternion();

	mImgShadow = LoadGraph("Data/Image/Shadow.png");

	mStepJump = 0.0f;
	mJumpPow = VGet(0, 0, 0);
	// アニメーションの設定
	InitAnimation();

	// 初期状態の設定
	ChangeState(STATE::PLAY);
}

void Player::InitAnimation(void)
{

	std::string path = "Data/Model/Player/";
	mAnimationController = new AnimationController(mSceneManager, mTransform.modelId);
	mAnimationController->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::RUN, path + "Run.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::FAST_RUN, path + "FastRun.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::JUMP, path + "Jump.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::WARP_PAUSE, path + "WarpPose.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::FLY, path + "Flying.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::FALLING, path + "Falling.mv1", 80.0f);
	mAnimationController->Add((int)ANIM_TYPE::VICTORY, path + "Victory.mv1", 60.0f);

	mAnimationController->Play((int)ANIM_TYPE::IDLE);

}

void Player::Update(void)
{

	switch (mState)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::PLAY:
		UpdatePlay();
		break;
	case Player::STATE::WARP_RESERVE:
		break;
	case Player::STATE::WARP_MOVE:
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

	mTransform.Update();
	mAnimationController->Update();
	
}

void Player::UpdatePlay(void)
{
	// 移動処理
	ProcessMove();

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		ProcessJump();
	}

	// 重力による移動量計算
	CalcGravityPow();

	Collision();


	mStepRotTime -= TimeCount::GetDeltaTime();

	if (mStepRotTime <= 0)
	{
		mPlayerRotY = mGoalQuaRot;
	}
	else
	{
		mPlayerRotY = Quaternion::Slerp(mPlayerRotY, mGoalQuaRot, (rot_time - mStepRotTime) / rot_time);
	}

	mTransform.quaRot = mGravityManager->GetTransform()->quaRot;
	mTransform.quaRot = mTransform.quaRot.Mult(mPlayerRotY);
}

void Player::Draw(void)
{

	// モデルの描画
	MV1DrawModel(mTransform.modelId);

	// デバッグ用描画
	DrawDebug();

}

void Player::DrawDebug(void)
{

	int white = 0xffffff;
	int black = 0x000000;
	int red = 0xff0000;
	int green = 0x00ff00;
	int blue = 0x0000ff;
	int yellow = 0xffff00;
	int purpl = 0x800080;

	VECTOR v;

	// キャラ基本情報
	//-------------------------------------------------------
	// キャラ座標
	v = mTransform.pos;
	DrawFormatString(20, 60, black, "キャラ座標 ： (%0.2f, %0.2f, %0.2f)",
		v.x, v.y, v.z
	);
	//-------------------------------------------------------

}

void Player::Release(void)
{
}

Transform* Player::GetTransform(void)
{
	return &mTransform;
}

void Player::AddCollider(Collider* collider)
{
	mColliders.emplace_back(collider);
}

void Player::ClearCollider(void)
{
	mColliders.clear();
}

void Player::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::PLAY:
		break;
	case Player::STATE::WARP_RESERVE:
		break;
	case Player::STATE::WARP_MOVE:
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

}

void Player::ProcessMove()
{
	mMoveDir = { 0,0,0 };
	mMovePow = { 0,0,0 };
	auto camera = mSceneManager->GetCamera()->GetQuaRotOutX();
	if (CheckHitKey(KEY_INPUT_W))
	{
		mMoveDir = VAdd(mMoveDir, camera.GetForward());
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		mMoveDir = VAdd(mMoveDir, camera.GetBack());
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		mMoveDir = VAdd(mMoveDir, camera.GetLeft());
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		mMoveDir = VAdd(mMoveDir, camera.GetRight());
	}

	if (AsoUtility::EqualsVZero(mMoveDir))
	{
		mAnimationController->Play((int)ANIM_TYPE::IDLE);
		return;
	}

	auto speed = walk_speed;
	if (CheckHitKey(KEY_INPUT_RSHIFT))
	{
		speed = run_speed;
		mAnimationController->Play((int)ANIM_TYPE::FAST_RUN);
	}
	else
	{
		mAnimationController->Play((int)ANIM_TYPE::RUN);

	}
	mMoveDir = VNorm(mMoveDir);
	mMovePow = VScale(mMoveDir, speed * TimeCount::GetDeltaTime());
	
	// 回転処理
	mStepRotTime = rot_time;
	float rotRad = atan2f(-mMoveDir.z, mMoveDir.x) + DX_PI_F / 2.0f;
	mGoalQuaRot = Quaternion::AngleAxis(rotRad,AsoUtility::AXIS_Y);

	

}

void Player::ProcessJump()
{
	if (!mIsGround) return;

	mJumpPow = VScale(mGravityManager->GetDirUpGravity(), jump_pow);
	mIsGround = false;
}

void Player::CalcGravityPow()
{
	if (VDot(mJumpPow, mGravityManager->GetDirGravity()) > 0)
	{
		if (VSquareSize(mJumpPow) > max_fall_speed * max_fall_speed) return;
	}

	// 重力方向
	auto dir = mGravityManager->GetDirGravity();

	mJumpPow = VAdd(mJumpPow,VScale(dir, mGravityManager->GetPower() * TimeCount::GetDeltaTime()));
}

void Player::Collision()
{
	CollisionGravity();

	mMovedPos = VAdd(mTransform.pos, mMovePow);
	mMovedPos = VAdd(mMovedPos, mJumpPow);
	mTransform.pos = mMovedPos;
}

void Player::CollisionGravity()
{
	// ジャンプパワーが重力と逆向きだったら判定しない
	if (VDot(mJumpPow, mGravityManager->GetDirUpGravity()) > 0) return;

	auto dirDown = mGravityManager->GetDirGravity();
	auto dirUp = mGravityManager->GetDirUpGravity();
	auto gravityPow = VSize(mJumpPow);
	float checkPow = 10.0f;
	mGravHitUp = VAdd(mMovedPos, VScale(dirUp, checkPow * 2.0f));
	mGravHitDown = VAdd(mMovedPos, VScale(dirDown, checkPow + gravityPow));

	auto result = MV1CollCheck_Line(mColliders[0]->mModelId, -1, mGravHitUp, mGravHitDown);
	if (!result.HitFlag)
	{
		mIsGround = false;
		return;
	}

	// 接地してる
	mJumpPow = VGet(0, 0, 0);
	mTransform.pos = result.HitPosition;
	mIsGround = true;
}

bool Player::IsEndLanding()
{
	return false;
}

void Player::DrawShadow()
{
}
