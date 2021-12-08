#include "Player.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "AsoUtility.h"

namespace
{
	constexpr float move_speed = 500.0f;
	constexpr float rotate_speed = 90.0f;
}

void Player::Rotate()
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
	auto degree = mTransform.quaRot.ToEuler();
	auto x = min(AsoUtility::Deg2RadF(76.0f), max(-AsoUtility::Deg2RadF(76.0f), angle.x + degree.x));
	mTransform.quaRot = Quaternion::Euler(VGet(x, angle.y + degree.y, 0));
}

Player::Player(SceneManager* sceneManager):mSceneManager(sceneManager)
{
	mTransform.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));
	float scale = 50.0f;
	mTransform.scl = { scale,scale,scale };
	mTransform.quaRot = Quaternion::Euler(0.0f,0.0f, 0.0f);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = AsoUtility::VECTOR_ZERO;

	mTransform.Update();
}

Player::~Player()
{
}

void Player::Update()
{
	Rotate();
	mTransform.pos = VAdd(mTransform.pos,VScale(mTransform.GetForward(),move_speed * mSceneManager->GetDeltaTime()));
	mTransform.Update();
}

void Player::Draw()
{
	MV1DrawModel(mTransform.modelId);

	auto degree = mTransform.quaRot.ToEuler();
	DrawFormatString(0, 0, 0xffffff, "%.1f : %.1f : %.1f", AsoUtility::Rad2DegF(degree.x), AsoUtility::Rad2DegF(degree.y), AsoUtility::Rad2DegF(degree.z));
}

const Transform& Player::GetTransform() const
{
	return mTransform;
}
