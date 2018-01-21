#pragma once
#include "MapBase.h"
#include "NPC_Linus.h"
#include "NPC_Kanna.h"

class Village:public MapBase
{
private:
	NPC_Linus linus;
	NPC_Kanna kanna;
	int count;
	int flameframe, smokeframe;
	int bgwidth;
	int floortileNum;
	int bgtileNum;
	POINT furnanceLoc;
public:
	HRESULT init();
	void update();
	void render();
	void renderz();
	void renderdc();
	void showSmoke();
	void showFlame();

	Village();
	~Village();
};

