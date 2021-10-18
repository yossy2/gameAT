#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"

enum class CAMERA_MODE
{
	NONE,
	FREE,
	FIXED,
};

class SceneManager;

class Camera
{

public:

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };


	// �J�����ʒu�ƒ����_�Ƃ̑��΍��W
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -100.0f, 500.0f };
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

	void ChangeMode(CAMERA_MODE mode);

private:

	SceneManager* mSceneManager;

	CAMERA_MODE mMode;
	// �J�����̈ʒu
	VECTOR mPos;
	// �����_
	VECTOR mTargetPos;

	// �J�����̏����
	VECTOR mCameraUp;
	// �J�����p�x
	Quaternion mQuaRot;

	void Move();
	void Rotate();

	void SetBeforeDrawFree();
	void SetBeforeDrawFixed();
};

