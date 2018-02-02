#pragma once
#include "green_goblin.h"
#include "goblin_thrower.h"
#include "Tauamy.h"
#include "TauAssaulter.h"

class Mirkwood :public MapBase
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


	Mirkwood();
	~Mirkwood();

};

class MirkwoodMap : public MapBase
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
	void setBoss(MonsterBase *b) { Boss = b; };
	void resetMonsters();
	void resetDungeon();
	void addMonster(MonsterBase* m) { monsterList.push_back(m); monsterBackup.push_back(m); }
	void setMap(const char* tileName,int x, int y);
};
