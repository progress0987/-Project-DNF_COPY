#pragma once
#include "Tau_Base.h"
class Tau :public Tau_Base
{
public:
	HRESULT init();
	HRESULT init(int x, int z);
	void update();
	void render();
	void renderdc();
	void setAttack();
	Tau();
	~Tau();
};

