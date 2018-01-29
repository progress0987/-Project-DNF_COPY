#pragma once
#include "MonsterBase.h"

struct sk_rush:public MonSkill{
	FLOAT fromX;
	int tick;
	HRESULT init(MonsterBase* m) {
		tick = 0;
		MonSkill::init(m);
		return S_OK;
	}
	void cast(FLOAT x, FLOAT z) {
		fromX = x;
		isFinished = false;
	}
	void update() {
	}
};
class Tau_Base : public MonsterBase
{
protected:
public:
	HRESULT init();
	HRESULT init(int x, int z);
	void castskill1() {
		fromX = x;
		frame = skill1from;
	}
	void onskill1() {
		if (onSkill&&curskillnum ==1&&!onAir&&!onAbnormal) {
			if (tick % 10 == 0) {
				frame++;
				if (frame > skill1to) {
					frame = skill1from;
				}
				x += curDir ? 25 : -25;

				effectedOnTime a;
				a.abnormal = -1;
				a.area.minx = x - 50;
				a.area.maxx = x + 50;
				a.area.miny = -monHeight;
				a.area.maxy = 0;
				a.area.minz = z - 40;
				a.area.maxz = z + 40;

				a.isAbnormal = a.isHold = a.isMove = a.isProjectile = false;
				a.isOnetime = true;
				a.isCrit = rand() % 100 > 80 ? true : false;
				a.time = GetTickCount();
				a.staytime = 30;

				a.mindmg = a.isCrit ? stat.dmgmin*1.5 * 2 : stat.dmgmin * 2;
				a.maxdmg = a.isCrit ? stat.dmgmax*1.5 * 2 : stat.dmgmax * 2;
				a.pushX = curDir ? 5.f : -5.f;
				a.pushY = -3.f;
				a.pushZ = 0;
				pl->hit(a);
				if (abs(x - fromX) > 400) {
					onSkill = false;
					curskillnum = 0;
					curStatus = mon_Idle;
					frame = idlefrom;
				}
			}
		}
	}
	void update();
	void render();
	void renderdc();
	Tau_Base();
	~Tau_Base();
};

