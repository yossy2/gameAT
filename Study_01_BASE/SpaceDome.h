#pragma once
#include "Transform.h"
#include <memory>

class SceneManager;
class Player;

class SpaceDome
{
public:

	SpaceDome(SceneManager* manager);
	~SpaceDome();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void SetPlayer(std::shared_ptr<Player> player);

private:
	SceneManager* mSceneManager;
	std::weak_ptr<Player> mPlayer;

	// モデル制御の基本情報
	Transform mTransform;
};

