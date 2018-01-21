#pragma once
#include "UI.h"

enum NPC_Status {
	npc_idle,
	npc_action,
};

class NPC_Base
{
protected:
	int idlefrom, idleto;
	int actionfrom, actionto;
	int tick;
	int curStatus;
	int frame;

	bool isMerchant;				//상인인지
	vector<Item> Merchant;			//상인이면 아이템포함
	RECT pointRC;					//상인이면 클릭할 수 있는 렉트
	int x, y;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void renderdc();
	vector<Item> GetItems() { return Merchant; }

	NPC_Base();
	~NPC_Base();
};

