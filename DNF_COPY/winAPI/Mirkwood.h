#pragma once
#include "DungeonBase.h"

class Mirkwood :public DungeonBase
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
	void setMap(const char* tileName,int x, int y);
};
