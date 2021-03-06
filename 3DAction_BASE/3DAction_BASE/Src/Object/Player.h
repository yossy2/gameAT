#pragma once
#include <DxLib.h>
#include "Common/Transform.h"
class SceneManager;
class ResourceManager;
class GravityManager;
class AnimationController;
class Capsule;
class Collider;

class Player
{

public:

	// 状態
	enum class STATE
	{
		NONE,
		PLAY,
		WARP_RESERVE,
		WARP_MOVE,
		DEAD,
		VICTORY,
		END
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		IDLE,
		RUN,
		FAST_RUN,
		JUMP,
		WARP_PAUSE,
		FLY,
		FALLING,
		VICTORY
	};

	Player(SceneManager* manager);
	void Init(void);
	void InitAnimation(void);
	void Update(void);
	void UpdatePlay(void);
	void Draw(void);
	void DrawDebug(void);
	void Release(void);

	Transform* GetTransform(void);

	void AddCollider(Collider* collider);
	void ClearCollider(void);

private:

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	// アニメーション
	AnimationController* mAnimationController;

	// 状態
	STATE mState;
	bool mIsGround = false;

	// 移動
	float mSpeed;
	VECTOR mMoveDir;
	VECTOR mMovePow;
	VECTOR mMovedPos;

	// 回転
	float mStepRotTime;
	Quaternion mGoalQuaRot;
	Quaternion mPlayerRotY;

	// ジャンプ
	float mStepJump;
	VECTOR mJumpPow;

	// 衝突判定
	std::vector<Collider*> mColliders;

	// 衝突チェック線分
	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	int mImgShadow;

	// 状態遷移
	void ChangeState(STATE state);

	void ProcessMove();
	void ProcessJump();
	void CalcGravityPow();
	void Collision();
	void CollisionGravity();

	bool IsEndLanding();
	void DrawShadow();
};

