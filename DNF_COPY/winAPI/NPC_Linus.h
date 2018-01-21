#pragma once
#include "NPC_Base.h"

class NPC_Linus :public NPC_Base
{
	bool test;
public:

	HRESULT init();
	void update();
	void render();
	void renderdc();

	NPC_Linus();
	~NPC_Linus();
};

