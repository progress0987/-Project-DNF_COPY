#pragma once
#include "MapBase.h"
#include "NPC_Seria.h"
class Seria :public MapBase
{
private:
	NPC_Seria seria;
public:
	Seria();
	~Seria();

	HRESULT init();
	void update();
	void render();
	void renderz();
	void renderdc();
};

