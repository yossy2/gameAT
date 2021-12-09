#include "DxLib.h"
#include "AsoUtility.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	constexpr float move_speed = 500.0f;
	constexpr float rotate_speed = 90.0f;
}

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
}

Camera::~Camera()
{
}

void Camera::Init()
{
	ChangeMode(CAMERA_MODE::FREE);
}

void Camera::SetDefault(void)
{

	// カメラの初期設定
	mPos = DEFAULT_CAMERA_POS;
	mTargetPos = VAdd(mPos, RELATIVE_TARGET_POS);
	mCameraUp = { 0.0f, 1.0f, 0.0f };

	// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
	// mQuaRotは回転計算用で、
	// あくまで軸となるのは、カメラ座標と注視点とする
	mQuaRot = Quaternion();

}

void Camera::Update()
{
	if (mMode == CAMERA_MODE::FREE)
	{
		Rotate();
		Move();
	}
	else if (mMode == CAMERA_MODE::CHASE)
	{
		Chase();
	}
}

void Camera::SetBeforeDraw(void)
{

	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(30.0f, 15000.0f);

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		mPos,
		mTargetPos,
		mCameraUp
	);

}

void Camera::Draw()
{
}

void Camera::DrawDebug(void)
{
}

void Camera::DrawUI(void)
{

	// 操作説明
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "　【操作】", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　旋回：↑↓←→", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　加速：Ｂ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　発弾：Ｎ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　シーン遷移：Ｓｐａｃｅ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　1500m以上離れると", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "　ゲームオーバー", 0xffffff);

}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}

VECTOR Camera::GetDir(void)
{
	return VNorm(VSub(mTargetPos, mPos));
}

void Camera::ChangeMode(CAMERA_MODE mode)
{
	mMode = mode;

	if (mode == CAMERA_MODE::FIXED)
	{
		// カメラの初期設定
		mPos = VGet(-2000.0f,2000.0f,2000.0f);
		mTargetPos = VGet(0,0,0);
		mCameraUp = { 0.0f, 1.0f, 0.0f };

		// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
		// mQuaRotは回転計算用で、
		// あくまで軸となるのは、カメラ座標と注視点とする
		mQuaRot = Quaternion();
		return;
	}

	SetDefault();
}

void Camera::SetPlayer(std::shared_ptr<Player> player)
{
	mPlayer_ = player;
	mMode = CAMERA_MODE::CHASE;
	// カメラの初期設定
	mTargetPos = mPlayer_->GetTransform().pos;
	mPos = VSub(mTargetPos, RELATIVE_TARGET_POS);
	mCameraUp = { 0.0f, 1.0f, 0.0f };

	// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
	// mQuaRotは回転計算用で、
	// あくまで軸となるのは、カメラ座標と注視点とする
	mQuaRot = Quaternion();
}

void Camera::Move()
{
	VECTOR move = AsoUtility::VECTOR_ZERO;

	if (CheckHitKey(KEY_INPUT_W)) move.z += 1.0f;
	if (CheckHitKey(KEY_INPUT_S)) move.z -= 1.0f;
	if (CheckHitKey(KEY_INPUT_A)) move.x -= 1.0f;
	if (CheckHitKey(KEY_INPUT_D)) move.x += 1.0f;

	if (move.x == 0 && move.z == 0) return;

	move = VNorm(mQuaRot.PosAxis(move));
	move = VScale(move, move_speed * mSceneManager->GetDeltaTime());
	mPos = VAdd(mPos, move);
	mTargetPos = VAdd(mPos, mQuaRot.PosAxis(RELATIVE_TARGET_POS));

}

void Camera::Rotate()
{
	VECTOR angle = AsoUtility::VECTOR_ZERO;

	if (CheckHitKey(KEY_INPUT_UP)) angle.x -= 1.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) angle.x += 1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) angle.y += 1.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) angle.y -= 1.0f;

	if (angle.x == 0 && angle.y == 0) return;

	angle = VNorm(angle);
	auto rotate = rotate_speed * mSceneManager->GetDeltaTime();

	angle = VGet(AsoUtility::Deg2RadF(angle.x * rotate), AsoUtility::Deg2RadF(angle.y * rotate), 0);
	auto degree = mQuaRot.ToEuler();
	mQuaRot = Quaternion::Euler(VGet(angle.x + degree.x, angle.y + degree.y, 0));

	// 注視点更新
	mTargetPos = VAdd(mPos, mQuaRot.PosAxis(RELATIVE_TARGET_POS));
	//mCameraUp = mQuaRot.PosAxis(AsoUtility::DIR_U);

}

void Camera::Chase()
{
	// カメラの初期設定
	const auto& pTransform = mPlayer_->GetTransform();
	mTargetPos = pTransform.pos;
	auto offset = pTransform.quaRot.PosAxis(RELATIVE_TARGET_POS);

	// 理想位置
	VECTOR idealPos = VSub(mTargetPos, offset);
	// 実際と理想の差
	VECTOR diff = VSub(mPos, idealPos);
	// 力 = -バネの強さ × バネの伸び - 抵抗 × カメラの速度
	VECTOR force = VScale(diff, -10.0f);
	force = VSub(force, VScale(mVelocity, 5.0f));
	// 速度の更新
	mVelocity = VAdd(mVelocity, VScale(force, mSceneManager->GetDeltaTime()));

	mPos = VAdd(mTargetPos, mVelocity);
}

void Camera::SetBeforeDrawFree()
{
}

void Camera::SetBeforeDrawFixed()
{
}
