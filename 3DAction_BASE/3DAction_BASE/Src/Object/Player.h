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

	// ���
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

	// �A�j���[�V�������
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

	// �A�j���[�V����
	AnimationController* mAnimationController;

	// ���
	STATE mState;
	bool mIsGround = false;

	// �ړ�
	float mSpeed;
	VECTOR mMoveDir;
	VECTOR mMovePow;
	VECTOR mMovedPos;

	// ��]
	float mStepRotTime;
	Quaternion mGoalQuaRot;
	Quaternion mPlayerRotY;

	// �W�����v
	float mStepJump;
	VECTOR mJumpPow;

	// �Փ˔���
	std::vector<Collider*> mColliders;

	// �Փ˃`�F�b�N����
	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	int mImgShadow;

	// ��ԑJ��
	void ChangeState(STATE state);

	void ProcessMove();
	void ProcessJump();
	void CalcGravityPow();
	void Collision();
	void CollisionGravity();

	bool IsEndLanding();
	void DrawShadow();
};

