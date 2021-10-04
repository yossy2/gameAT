#pragma once
#include <DxLib.h>

class SceneManager;
class RollBall;

class Unit
{
public:
	Unit(SceneManager* manager);
	void Init();
	void Update();
	void Draw();
	void Release();

	VECTOR GetPos()const;
	VECTOR GetForward()const;

private:
	SceneManager* mSceneManager;
	RollBall* mBall;

	int mModelID;
	int mAnimWalk;

	float mTimeTotalAnimWalk = 0;	// アニメーションの総再生時間
	float mStepAnim = 0;			//
	float mAnimSpeed = 1.0f;

	VECTOR mPos;
	VECTOR mAngles;

	void Move();
};

