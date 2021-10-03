#pragma once
#include <DxLib.h>

class SceneManager;

class Unit
{
public:
	Unit(SceneManager* manager);
	void Init();
	void Update();
	void Draw();
	void Release();

private:
	SceneManager* mSceneManager;
	int mModelID;
	int mAnimWalk;

	float mTimeTotalAnimWalk = 0;	// �A�j���[�V�����̑��Đ�����
	float mStepAnim = 0;			//
	float mAnimSpeed = 1.0f;

	VECTOR mPos;
	VECTOR mAngles;

	void Move();
};

