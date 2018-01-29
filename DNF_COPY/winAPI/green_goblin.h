#pragma once
#include "goblin_base.h"

class green_goblin :public goblin_base
{
public:

	HRESULT init();
	HRESULT init(int x, int z);
	void update();
	void render();
	void renderdc();
	void setAttack();

	green_goblin();
	~green_goblin();
};

