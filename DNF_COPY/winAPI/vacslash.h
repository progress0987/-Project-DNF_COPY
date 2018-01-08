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
	int chargeStatus;			//0 충전중 1 충전완료 2 충전완료 프린트완료
	int chargeFrame;
	int fullchargeFrame;
	int travelDist;
	bool head;
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

