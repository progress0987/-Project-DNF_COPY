#pragma once
#include "Skill.h"

struct slash {
	int dmg;
	FLOAT x, y, z;
	int dmgtick;
	bool onshow;
};

class vacslash :public Skill
{
private:
	bool onCharge;
	int chargeStatus;			//0 ������ 1 �����Ϸ� 2 �����Ϸ� ����Ʈ�Ϸ�
	int chargeFrame;
	int fullchargeFrame;
	int travelDist;
	bool head;
	bool playedchargesound;
	slash sl;
public:
	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();

	vacslash();
	~vacslash();
};

