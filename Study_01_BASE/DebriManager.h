#pragma once
#include <DxLib.h>
#include <memory>
#include <list>
#include <unordered_map>

class SpaceDebri;

struct DebriMapKey
{
	int x;
	int y;
	int z;

	DebriMapKey(int inx, int iny, int inz):x(inx),y(iny),z(inz)
	{

	}

	inline DebriMapKey GetOffsetKey(int inx, int iny, int inz)
	{
		return DebriMapKey(x + inx, y + iny, z + inz);
	}

	bool operator== (const DebriMapKey& other)const
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}
};

class DebriManager
{
private:
	int baseModelID_[5];
	int oldPlayerKey = -1;
	std::unordered_map<int,std::list<std::shared_ptr<SpaceDebri>>> debriMap_;
	void MakeDebriRandom(const DebriMapKey key,std::list<std::shared_ptr<SpaceDebri>>& list);
	DebriMapKey ConvPlayerPos2Key(const VECTOR& pos);
public:
	DebriManager();
	~DebriManager();
	void MakeDebri(const VECTOR& playerPos);
	void Draw(const VECTOR& playerPos);
};

