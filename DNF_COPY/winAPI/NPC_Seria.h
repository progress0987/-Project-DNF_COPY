#pragma once
#include "NPC_Base.h"

class NPC_Seria : public NPC_Base
{
public:

	HRESULT init();
	void update();
	void render();
	void renderdc();

	NPC_Seria();
	~NPC_Seria();
};

