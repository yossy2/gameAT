#pragma once
#include "Transform.h"
#include <memory>
#include <vector>
#include "Effect2D.h"

class SceneManager;
class BulletManager;

class Player
{
private:
	Transform mTransform;

	SceneManager* mSceneManager;
	BulletManager& mBulletManager;
	int particle = 0;
	std::vector<std::shared_ptr<Effect2D>> particles_;

	float particleCnt = 0;
	float attackInterval_ = 0;
	std::vector<int> explosion_;
	bool isDead_ = false;
	void Rotate();
public:
	Player(SceneManager* sceneManager,BulletManager& bulletManager);
	~Player();
	void Update();
	void Draw();

	const Transform& GetTransform()const;
	void GetCapsule(VECTOR& start, VECTOR& end, float& radius);

	void Dead();
};

