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
struct monStat {
	int dmg;
	int HP;

};

class MonsterBase
{
protected:
	monStat stat;
	char *name;
	int level;
	int maxHP, curHP;
	FLOAT x, y, z;
	FLOAT destX, destY, destZ;
	FLOAT moveSpeedX, moveSpeedZ;
	FLOAT moveSpeedMaxX, moveSpeedMaxZ;
	FLOAT hitXvel, hitYvel, hitZvel;
	FLOAT monHeight;
	FLOAT probeX, probeZ;
	DWORD onHitCount;
	bool onAir;
	bool onHold;
	bool onAbnormal;
	int abnormalType;
	int abnormalStage;
	int abnormalCount;
	int abnormalFrame;

	bool found;
	bool curDir;
	bool hitAvail;
	int hitAvailCount;
	int frame;
	int actionTick;
	int actionIndicate;
	int tick;
	monStatus curStatus;
	MapBase* curMap;
	RECT terColRect;
	int idlefrom, attackfrom, hitfrom, wakeupfrom, walkfrom, falldownfrom;
	int idleto, attackto, hitto, wakeupto, walkto,falldownto;
	int bloodframe;
	bool printblood;
	vector<string> effectNames;
	int effectframeMax;
	int effectframe1;
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

