#include "DxLib.h"
#include "AsoUtility.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Camera.h"

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

	auto degree = mQuaRot.ToEuler();
	DrawFormatString(0,0,0xffffff,"%.1f : %.1f : %.1f",AsoUtility::Rad2DegF(degree.x), AsoUtility::Rad2DegF(degree.y), AsoUtility::Rad2DegF(degree.z));
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

	SetDefault();
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

void Camera::SetBeforeDrawFree()
{
}

void Camera::SetBeforeDrawFixed()
{
}
