//#pragma once
#include <chrono>
#include "TitleScene.h"
class SceneBase;
class Fader;
class Camera;
class MiniCamera;

// �V�[���Ǘ��p
enum class SCENE_ID
{
	NONE
	, TITLE
};

class SceneManager
{

public:

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Release(void);

	void ChangeScene(SCENE_ID nextId, bool isFading);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void);

	Camera* GetCamera();

private:

	SCENE_ID mSceneID;
	SCENE_ID mWaitSceneID;

	SceneBase* mScene;
	Fader* mFader;
	Camera* mCamera;
	MiniCamera* mMiniCamera;

	bool mIsSceneChanging;

	// �f���^�^�C��
	std::chrono::system_clock::time_point mTickCount;
	float mDeltaTime;

	void DoChangeScene(void);

};