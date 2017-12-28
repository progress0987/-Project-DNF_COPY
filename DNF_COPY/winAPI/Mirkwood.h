#pragma once
#include "green_goblin.h"

class Mirkwood :public MapBase
{
private:
public:
	void init();
	void update();
	void render();
	void renderz();
	void renderdc();


	Mirkwood();
	~Mirkwood();

};

class MirkwoodMap : public MapBase
{
public:
	void init();
	void update();
	void render();
	void renderz();
	void renderdc();
	void addMonster(MonsterBase* m) { monsterList.push_back(m); }
	void setMap(const char* tileName,int x, int y);
};
