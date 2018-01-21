#pragma once
#include "NPC_Base.h"
class NPC_Kanna :public NPC_Base
{
public:
	HRESULT init();
	void update();
	void render();
	void renderdc();
	NPC_Kanna();
	~NPC_Kanna();
};

