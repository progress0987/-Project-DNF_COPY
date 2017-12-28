#pragma once
#include "MapBase.h"

class MapBase;
enum monStatus {
	mon_Idle,
	mon_Attack,
	mon_Hit,
	mon_Falldown,
	mon_Wakeup,
	mon_Walk,
};
class MonsterBase
{
protected:
	char *name;
	int level;
	int maxHP, curHP;
	FLOAT x, y, z;
	FLOAT moveSpeedX, moveSpeedZ;
	FLOAT moveSpeedMaxX, moveSpeedMaxZ;
	FLOAT probeX, probeZ;
	bool onAir;
	bool found;
	bool curDir;
	int frame;
	int actionTick;
	int actionIndicate;
	int tick;
	monStatus curStatus;
	MapBase* curMap;
	RECT terColRect;
	int idlefrom, attackfrom, hitfrom, wakeupfrom, walkfrom, falldownfrom;
	int idleto, attackto, hitto, wakeupto, walkto,falldownto;
public:
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void renderdc();
	virtual bool isdetected();

	//////////////////////////////////////////////////////Getter
	const char* getName() { return name; }
	int getLvl() { return level; }
	int getCurHP() { return curHP; }
	int getMaxHP() { return maxHP; }
	FLOAT getX() { return x; }
	FLOAT getY() { return y; }
	FLOAT getZ() { return z; }
	monStatus getCurStat() { return curStatus; }


	/////////////////////////////////////////////////////Setter
	void setCurmap(MapBase* m) { curMap = m; }
	MonsterBase();
	~MonsterBase();
};

