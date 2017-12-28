#pragma once
#include "MapBase.h"
#include "MonsterBase.h"
class DungeonBase :public MapBase
{
protected:
	vector<MapBase*> Maps;
public:
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void renderz();
	virtual void renderdc();
	virtual void resetMonsters();
	int getWidth() { return curMap->getWidth(); }
	int getHeight() { return curMap->getHeight(); }
	vector<MapTile> getTiles() { return curMap->getTiles(); }

	DungeonBase();
	~DungeonBase();
};

