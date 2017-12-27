#pragma once
#include "gameNode.h"
#include "MapBase.h"
#include "UI.h"

#define KEYDELAY 200
class UI;
class MapBase;
enum STANCE {
	stance_NULL				 = -1,				//자세끝내기
	stance_norm_1			 = 0,				//평타 1번
	stance_norm_2			 = 9,				//평타 2번
	stance_norm_3			 = 33,				//평타 3번
	stance_upper			 = 42,				//어퍼슬래시
	stance_thrust			 = 65,				//쓰러스트
	stance_handup			 = 75,				//손들기
	stance_ready			 = 90,				//전투준비자세
	stance_hit				 = 96,				//맞는자세
	stance_down				 = 100,				//쓰러지는자세
	stance_run				 = 105,				//뛰는자세
	stance_jump_up			 = 125,				//점프올라가는자세
	stance_jump_down		 = 128,				//점프내려가는자세
	stance_areal_att		 = 133,				//공중공격
	stance_sit				 = 157,				//앉기(줍기등)
	stance_handfront		 = 159,				//손앞으로뻗기
	stance_idle				 = 176,				//기본자세(마을자세)
	stance_walk				 = 180,				//걷는자세
	stance_empowered_norm_1	 , 	//강화평타1번
	stance_empowered_norm_2	 ,	//강화평타2번
	stance_empowered_norm_3	 ,	//강화평타3번
};
enum SKILLS {
	//사용할 스킬들 이름 / 상황처리
	skill_NULL,
	skill_norm_1,
	skill_norm_2,
	skill_upper,
};

struct status {//스텟 - 추가할것

};

struct dmgstruct {
	int dmg;
	unsigned long time;
	int dmgFrame;
	int maxz, minz;
	int maxx, minx;
	int maxy, miny;
};

struct inputStruct {
	short key;
	long time;
};
class player
{
private:
	RECT terColRect;

	int frame;
	DWORD beginTime;
	DWORD tick;
	
	bool curDir;							//현재 방향
	bool onAttack;							//공격 상태인지
	bool onSkill;
	bool onJump;							//점프상태인지
	int movestatus;							//가만히있을시 : 0 걷기 : 1 뛰기 : 2
	float jumpPow;
	FLOAT x, y, z;
	bool onDebug;

	status Stat;
	STANCE prevStance;
	STANCE curStance;
	STANCE nextStance;
	MapBase* curMap;
	UI* ui;
	list<dmgstruct> attackQueue;
	list<inputStruct> inputQueue;

	long movebegin;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);
	void setCurScene(MapBase* map, FLOAT x = 0.f, FLOAT z = 0.f);
	void setOnCombat(bool oncombat);
	list<dmgstruct> getAttackQueue() { return attackQueue; }
	FLOAT translate(FLOAT zval);
	MapBase* getCurMap() { return curMap; }
	list<dmgstruct> getAttacks() { return attackQueue; }
	UI* getUI() { return ui; }

	player();
	~player();
};

