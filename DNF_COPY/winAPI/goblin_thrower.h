#pragma once
#include "goblin_base.h"
extern struct projectile;
class goblin_thrower :public goblin_base
{
public:

	HRESULT init();
	HRESULT init(int x, int z);
	void reset();
	void update();
	void render();
	void renderdc();
	void setAttack();

	goblin_thrower();
	~goblin_thrower();
};

