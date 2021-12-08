#pragma once
#include <DxLib.h>
#include <memory>
#include <list>

class SpaceDebri;

class DebriManager
{
private:
	std::list<std::shared_ptr<SpaceDebri>> debris_;

public:
	DebriManager();
	void MakeDebri(const VECTOR& playerPos);
};

