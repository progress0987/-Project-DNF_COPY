#pragma once
#include "gameNode.h"
#include "MapBase.h"
#include "UI.h"
#include "skills.h"

#define KEYDELAY 30
class UI;
class MapBase;
class Skill;
class wave;

struct Item {
	int type;							//아이템 종류로 할 것
	int dmg;
	int def;

	int reachx;							//무기에 한정됨
	int reachz;							//무기에 한정됨

	int reqStr;
	int reqInt;
	int reqDex;

	int gainStr;
	int gainInt;
	int gainDex;

	string name;
	string description;
};

struct effected {
	FLOAT maxx, minx;
	FLOAT maxy, miny;
	FLOAT maxz, minz;
};
struct effectedOnTime {
	int dmg;									//대미지
	int dmgTick;								//대미지가 얼마마다 들어올지(틱/시간)
	effected area;								//대미지 타격 범위

	DWORD time;									//공격 대미지 시작시간
	unsigned int staytime;						//공격 대미지 유지시간

	bool isProjectile;							//투사체인지
	bool isOnetime;								//지속적으로 남는건지(필요할지?)

	FLOAT pushX, pushY;							//각 축으로 밀어내는 정도
};

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
	stance_onSkill			 = 9999,			//스킬쓸때(해당 스킬로부터 자세를 받아와야함)
};
enum SKILLS {
	//사용할 스킬들 이름 / 상황처리
	skill_NULL,
	skill_norm_1,
	skill_norm_2,
	skill_norm_3,
	skill_upper,
	skill_areal_Atk,
};

struct status {//스텟 - 추가할것

};

//struct dmgstruct {
//	int dmg;									//대미지
//	unsigned long time;							//공격을 할 때의 시간
//	unsigned int staytime;						//공격 대미지 유지시간
//	bool isProjectile;							//투사체인지
//	bool isOnetime;								//지속적으로 남는건지(필요할지?)
//	int dmgFrame;								//대미지가 들어갈 프레임 - 스킬단에서 쓸 예정(안쓸지도)
//	FLOAT pushX, pushY;							//각 축으로 밀어내는 정도
//	int maxz, minz;								//최대/최소 z대미지 범위
//	int maxx, minx;								//최대/최소 x대미지 범위
//	int maxy, miny;								//최대/최소 y대미지 범위
//};

struct inputStruct {
	short key;
	long time;
};
class player
{
private:
	RECT terColRect;

	int frame;
	DWORD Time;
	DWORD tick;
	
	bool curDir;							//현재 방향
	bool onAttack;							//공격 상태인지
	bool onSkill;
	bool onJump;							//점프상태인지
	int movestatus;							//가만히있을시 : 0 걷기 : 1 뛰기 : 2
	float jumpPow;
	FLOAT x, y, z;
	bool onDebug;

	
	//////////////////////////스킬들
	wave* skill_wave;
	upper* skill_upper;


	status Stat;
	STANCE prevStance;
	STANCE curStance;
	STANCE nextStance;
	MapBase* curMap;

	Skill* curSkill;

	UI* ui;
	list<effectedOnTime> attackQueue;
	list<inputStruct> inputQueue;

	/////////////////////////////////장비///////////////////////
	Item* Weapon;

	long movebegin;




	bool test;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);



	void setCurScene(MapBase* map, FLOAT x = 0.f, FLOAT z = 0.f);
	void setOnCombat(bool oncombat);
	void addAttack(effectedOnTime attack) { attackQueue.push_back(attack); }



	FLOAT getX() { return x; }
	FLOAT getY() { return y; }
	FLOAT getZ() { return z; }
	bool getCurDir() { return curDir; }
	Item* getWeapon() { return Weapon; }
	list<effectedOnTime> getAttackQueue() { return attackQueue; }
	list<effectedOnTime>::iterator getAttackQueueBegin() { return attackQueue.begin(); }
	list<effectedOnTime>::iterator getAttackQueueEnd() { return attackQueue.end(); }
	MapBase* getCurMap() { return curMap; }
	UI* getUI() { return ui; }

	player();
	~player();
};

