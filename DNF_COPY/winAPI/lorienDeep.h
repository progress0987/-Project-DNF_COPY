#pragma once
#include "DungeonBase.h"

class lorienDeep :public MapBase
{
private:
	vector<MapBase*>Maps;
public:
	HRESULT init();
	void update();
	void render();
	void renderz();
	void renderdc();
	void resetDungeon();

	lorienDeep();
	~lorienDeep();
};

class lorienDeepMap : public MapBase
{
private:

	MonsterBase * Boss;
	bool movable;
public:
	bool isBossMap;
	HRESULT init();
	void update();
	void render();
	void renderz();
	void renderdc();
	void setBoss(MonsterBase *b) { Boss = b; isBossMap = true; };
	void resetMonsters();
	void resetDungeon();
	void addMonster(MonsterBase* m) { monsterList.push_back(m); monsterBackup.push_back(m); }
	void setMap(const char* tileName, int x, int y);
};