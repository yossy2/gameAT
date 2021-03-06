#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"

enum class CAMERA_MODE
{
	NONE,
	FREE,
	FIXED,
	CHASE
};

class SceneManager;
class Player;

class Camera
{

public:

	// カメラの初期座標
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };


	// カメラ位置と注視点との相対座標
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -300.0f, 1000.0f };
	
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
	void SetPlayer(std::shared_ptr<Player> player);

private:

	SceneManager* mSceneManager;

	CAMERA_MODE mMode;
	// カメラの位置
	VECTOR mPos;
	// 注視点
	VECTOR mTargetPos;
	VECTOR mVelocity;
	// カメラの上方向
	VECTOR mCameraUp;
	// カメラ角度
	Quaternion mQuaRot;
	std::shared_ptr<Player> mPlayer_;

	void Move();
	void Rotate();
	void Chase();

	void SetBeforeDrawFree();
	void SetBeforeDrawFixed();
};

