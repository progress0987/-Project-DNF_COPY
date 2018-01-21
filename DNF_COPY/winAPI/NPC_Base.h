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

	bool isMerchant;				//��������
	vector<Item> Merchant;			//�����̸� ����������
	RECT pointRC;					//�����̸� Ŭ���� �� �ִ� ��Ʈ
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

