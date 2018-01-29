#pragma once
#include "Tau_Base.h"

class TauAssaulter:public Tau_Base
{
public:
	HRESULT init();
	HRESULT init(int x, int z);
	void update();
	void render();
	void renderdc();
	void setAttack();
	TauAssaulter();
	~TauAssaulter();
};

