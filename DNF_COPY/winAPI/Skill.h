#pragma once

extern struct effectedOnTime;



class Skill////////////////스킬 할 것
{
protected:

	int count;
	int framecount;
	int effect;

	int curAction;													//현재 취하고있는 액션의 프레임
	

	bool isbuff;

	FLOAT x, y, z;													//플레이어의 포지션

	DWORD cooldownstartfrom;													//쿨타임
	int cooldownTick;

	bool isChargable;												//충전식인지
	int chargemax;
	int curcharge;
	int chargeamount;												//틱당 얼마나 차는지
	int chargetick;													//몇틱당 충전될지

	int staytime;													//유지시간 -필요?

	bool isSpot;													//제어기능있는지
	POINT spot;														//제어기능이 있는 스킬중에 일정 좌표로 모으는것


public:
	int reqMana;
	bool oncast,finished;
	bool onCooldown;
	bool isSuperArmor;
	int skillInactive;
	int skillActive;
	FLOAT getremainCooldown();
	int getremainCooldownTime();
	virtual HRESULT init();
	virtual void cast(FLOAT x, FLOAT y, FLOAT z);
	virtual void update();
	virtual void renderb();
	virtual void renderf();

	int getCurAction() { return curAction; }
	Skill();
	~Skill();
};

