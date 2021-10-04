#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class RollBall
{
public:
	RollBall(SceneManager* manager,Unit* owner);
	~RollBall();

	void Init();
	void Update();
	void Draw();
	void Release();

private:
	VECTOR mPos;
	VECTOR mVecTargetToOwn;

	void RotateAroundTarget();

	SceneManager* mSceneManager;
	Unit* mOwner;
};
