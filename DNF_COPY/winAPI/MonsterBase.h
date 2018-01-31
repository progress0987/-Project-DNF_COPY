#pragma once
#include "MapBase.h"

class MapBase;
struct MonSkill;
extern struct HitQueue;
extern struct projectile;
enum monStatus {
	mon_Idle,
	mon_Attack,
	mon_Hit,
	mon_Falldown,
	mon_Wakeup,
	mon_Walk,
	mon_onDeadProcess,
	mon_onDead,
	mon_Skill1,
	mon_Skill2,
	mon_Skill3,
};
struct monStat {
	int maxHP, curHP;
	char name[50];
	int level;
	int dmgmin;
	int dmgmax;
};
class MonsterBase
{
protected:
	vector<projectile> projectiles;
	monStat stat;
	FLOAT x, y, z;
	FLOAT fromX, fromY, fromZ;//스킬사용시 이동하는것
	FLOAT backupx, backupz;
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
	bool onAttack;
	bool onSkill;
	bool found;
	bool curDir;
	bool hitAvail;

	int abnormalType;
	int abnormalStage;
	int abnormalCount;
	int abnormalFrame;

	int goldAmount;
	int aggressive;		//0~100;
	int curskillnum;	//1~3
	int atkCount;
	int hitAvailCount;
	int atkcooldown;
	int curatkcooldown;
	int frame;
	int actionTick;
	int actionIndicate;
	int tick;
	int idlefrom, attackfrom, hitfrom, wakeupfrom, walkfrom, falldownfrom,skill1from,skill2from,skill3from;
	int idleto, attackto, hitto, wakeupto, walkto,falldownto,skill1to,skill2to,skill3to;
	int deadcount;
	int bloodframe;
	int effectframeMax;
	int effectframe1;
	int expamount;								//죽었을때 주는 경험치 양

	monStatus curStatus;
	MapBase* curMap;
	RECT terColRect;
	bool printblood;
	vector<string> effectNames;
	list<HitQueue> hitQueue;
	vector<Item> dropItems;
public:
	bool isDead;
	virtual HRESULT init();
	virtual void reset() {};
	virtual void update();
	virtual void render();
	virtual void renderdc();
	virtual bool isdetected();
	virtual void setAttack();
	virtual void castskill1() {};
	virtual void castskill2() {};
	virtual void castskill3() {};
	virtual void onskill1() {};
	virtual void onskill2() {};
	virtual void onskill3() {};



	//////////////////////////////////////////////////////Getter
	const char* getName() { return stat.name; }
	int getLvl() { return stat.level; }
	int getCurHP() { return stat.curHP; }
	int getMaxHP() { return stat.maxHP; }
	FLOAT getX() { return x; }
	FLOAT getY() { return y; }
	FLOAT getZ() { return z; }
	monStatus getCurStat() { return curStatus; }


	/////////////////////////////////////////////////////Setter
	void setCurmap(MapBase* m) { curMap = m; }
	void setCurStat(monStatus m) { curStatus = m; }

	MonsterBase();
	~MonsterBase();
};

struct MonSkill {
	int curFrame;
	bool isFinished;
	MonsterBase* mon;
	virtual HRESULT init(MonsterBase* m) { mon = m; return S_OK; }
	virtual void cast(FLOAT x, FLOAT z) {};
	virtual void update() {};
};
