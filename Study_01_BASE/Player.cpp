#include "Player.h"
#include <memory>
#include <vector>
#include <DxLib.h>
#include "SceneManager.h"
#include "AsoUtility.h"
#include "TimeCount.h"
#include "Effect2D.h"
#include "RandomEngine.h"

namespace
{
	constexpr float move_speed = 4000.0f;
	constexpr float rotate_speed = 90.0f;

	int particle = 0;
	std::vector<std::shared_ptr<Effect2D>> particles_;

	float particleCnt = 0;
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

	particle = LoadGraph("Image/Light.png");
	particles_.reserve(50);
}

Player::~Player()
{
}

void Player::Update()
{
	Rotate();

	if (CheckHitKey(KEY_INPUT_W))
	{
		mTransform.pos = VAdd(mTransform.pos, VScale(mTransform.GetForward(), move_speed * TimeCount::GetDeltaTime()));
	}
	mTransform.Update();

	// パーティクル削除
	for (auto p : particles_)
	{
		p->Update();
	}
	particles_.erase(std::remove_if(particles_.begin(), particles_.end(),
		[](std::shared_ptr<Effect2D> p) {return p->IsDeletable(); }), particles_.end());

	// パーティクル生成
	particleCnt -= TimeCount::GetDeltaTime();
	if (particleCnt > 0) return;

	auto pos = VAdd(mTransform.pos,VScale(mTransform.GetForward(),-150.0f));
	pos = VAdd(pos, VScale(mTransform.GetUp(), 25.0f));
	pos = VAdd(pos, VScale(mTransform.GetRight(), RandomEngine::RandomFloat(-25.0f, 25.0f)));
	pos = VAdd(pos, VScale(mTransform.GetUp(), RandomEngine::RandomFloat(-25.0f, 25.0f)));
	particles_.emplace_back(std::make_shared<Effect2D>(particle, 1.0f, 25.0f, pos));
	particleCnt = 0.1f;
}

void Player::Draw()
{
	MV1DrawModel(mTransform.modelId);
	
	for (auto p : particles_)
	{
		p->Draw();
	}
	auto degree = mTransform.quaRot.ToEuler();
	//DrawFormatString(0, 0, 0xffffff, "%.1f : %.1f : %.1f", AsoUtility::Rad2DegF(degree.x), AsoUtility::Rad2DegF(degree.y), AsoUtility::Rad2DegF(degree.z));
	DrawFormatString(0, 0, 0xffffff, "%.1f : %.1f : %.1f", mTransform.pos.x, mTransform.pos.y, mTransform.pos.z);
}

const Transform& Player::GetTransform() const
{
	return mTransform;
}
