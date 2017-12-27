#pragma once
#include "MapBase.h"
class DungeonBase :public MapBase
{
protected:
	MapBase * curMap;
	vector<MapBase*> Maps;
public:

	void init();
	void update();
	void render();
	void renderz();
	void renderdc();
	void resetMonsters();
	int getWidth() { return curMap->getWidth(); }
	int getHeight() { return curMap->getHeight(); }
	vector<MapTile> getTiles() { return curMap->getTiles(); }

	DungeonBase();
	~DungeonBase();
};

