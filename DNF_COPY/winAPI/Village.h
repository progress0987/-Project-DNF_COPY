#pragma once
#include "MapBase.h"
class Village:public MapBase
{
private:
	int count;
	int flameframe, smokeframe;
	int bgwidth;
	int floortileNum;
	int bgtileNum;
	POINT furnanceLoc;
public:
	void init();
	void update();
	void render();
	void renderz();
	void renderdc();
	void showSmoke();
	void showFlame();

	Village();
	~Village();
};

