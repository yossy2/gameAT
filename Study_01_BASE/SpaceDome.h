#pragma once
#include "Transform.h"
#include <memory>

class SceneManager;
class Player;

class SpaceDome
{
public:

	SpaceDome(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetPlayer(std::shared_ptr<Player> player);

private:
	SceneManager* mSceneManager;
	std::weak_ptr<Player> mPlayer;

	// ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ
	Transform mTransform;
};

