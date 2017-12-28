#pragma once
#include "MonsterBase.h"

class goblin_base :public MonsterBase
{
public:
	goblin_base();
	~goblin_base();
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void renderdc();

};

