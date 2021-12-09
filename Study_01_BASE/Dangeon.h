#pragma once
#include "Transform.h"
#include <memory>

class Player;

class Dangeon
{
private:
	Transform mTransform;
public:
	Dangeon();
	~Dangeon();
	void Draw();

	bool CollisionCheck(std::shared_ptr<Player> player);
};

