#pragma once
#include "UI.h"
#include "MapBase.h"
#include "skills.h"

#define KEYDELAY 30
class UI;
class MapBase;
extern struct Item;


struct effected {
	FLOAT maxx, minx;
	FLOAT maxy, miny;
	FLOAT maxz, minz;
};
struct effectedOnTime {
	int mindmg;									//대미지
	int maxdmg;
	int dmgTick;								//대미지가 얼마마다 들어올지(틱/시간)
	effected area;								//대미지 타격 범위

	DWORD time;									//공격 대미지 시작시간
	unsigned int staytime;						//공격 대미지 유지시간

	bool isProjectile;							//투사체인지
	bool isOnetime;								//지속적으로 남는건지(필요할지?)
	bool isHold;								//홀딩상태로 만드는건지
	bool isMove;								//강제로 이동시키는지
	bool isAbnormal;							//상태이상인지
	bool isCrit;								//크리티컬인지
	int abnormal;								//어떤 상태이상인지 0-빙결 9-홀딩 10-화염 50-거리로 이동시키기

	FLOAT pushX, pushY,pushZ;							//각 축으로 밀어내는 정도
	FLOAT attr1,attr2,attr3,attr4;						//받아오는 정보
	vector<string> effectNames;							//홀딩시 프린트시킬 이름
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

struct status {			//스텟, a붙은건 추가분
	int level;
	int maxHP, curHP;
	int a_maxHP;
	int maxMP, curMP;
	int a_maxMP;
	int str, intel, health, spirit;
	int a_str, a_intel, a_health, a_spirit;
	int phyAtt, magAtt;
	int a_phyAtt, a_magAtt;
	int phyDef, magDef;
	int a_phyDef, a_magDef;
	int curEXP, reqEXP;
	float phycritrate, magcritrate;//안쓸거임
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
	bool onSuperarmor;
	DWORD Time;
	DWORD tick;
	
	bool curDir;							//현재 방향
	bool onAttack;							//공격 상태인지
	bool onSkill;
	bool onJump;							//점프상태인지
	bool onHit;								//맞는상태인지
	bool printblood;

	bool onLevelup;
	bool levelupEffect;
	int levelupTick;


	int Coin;
	int deadTick;

	int onHeal;								//0 없음 1 체력 2 마력 3 둘다
	int onHealFrame;
	int bloodframe;

	int hitcount;

	int movestatus;							//가만히있을시 : 0 걷기 : 1 뛰기 : 2
	float jumpPow;
	FLOAT x, y, z;

	//////////////////////////스킬들
	vector<Skill*> skills;
	wave* skill_wave;
	upper* skill_upper;
	icewave* skill_icewave;
	firewave* skill_firewave;
	vacslash* skill_vacslash;
	releasewave* skill_releasewave;
	wavespin* skill_wavespin;
	Skill* QSkill;
	Skill* WSkill;
	Skill* ASkill;
	Skill* SSkill;
	Skill* DSkill;
	Skill* FSkill;
	Skill* GSkill;



	STANCE prevStance;
	STANCE curStance;
	STANCE nextStance;
	MapBase* curMap;

	Skill* curSkill;

	UI* ui;
	list<effectedOnTime> attackQueue;
	list<inputStruct> inputQueue;
	list<effectedOnTime> hitQueue;
	list<HitQueue> dmgShow;


	/////////////////////////////////장비///////////////////////

	Item Weapon;
	Item Armor;
	Item Shoulder;
	Item Pants;
	Item Belt;
	Item Boots;
	Item Necklece;
	Item Ring;
	Item Bracelet;

	Item q1, q2, q3, q4, q5, q6;


	long movebegin;
public:
	bool reset;
	Item emptyWeapon;
	Item empty;
	status Stat;									//스텟
	int gold;
	vector<Item> equipments;
	vector<Item> consume;
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);
	void gainEXP(int amount);



	void setCurScene(MapBase* map, FLOAT x = 0.f, FLOAT z = 0.f);
	void setOnCombat(bool oncombat);
	void setDirection(bool dir) { curDir = dir; }
	void addAttack(effectedOnTime attack) { attackQueue.push_back(attack); }
	void setSkills();
	void updateSkills();
	void printSkillb();
	void printSkillf();
	void hitDmg(int amount);


	void useItem(int tab, int x,int y);
	void useIteminQS(int qs);
	void rootItem(Item it);
	void sellItem(int tab, int index);
	void unequip(int);
	Item setquickslot(int index, Item it);



	FLOAT getX() { return x; }
	FLOAT getY() { return y; }
	FLOAT getZ() { return z; }
	bool getCurDir() { return curDir; }
	
	Item getWeapon() { return Weapon; }
	Item getArmor() { return Armor; }
	Item getCoat() { return Armor; }
	Item getShoulder() { return Shoulder; }
	Item getPants() { return Pants; }
	Item getBelt() { return Belt; }
	Item getBoots() { return Boots; }
	Item getShoes() { return Boots; }
	Item getQuick1() { return q1; }
	Item getQuick2() { return q2; }
	Item getQuick3() { return q3; }
	Item getQuick4() { return q4; }
	Item getQuick5() { return q5; }
	Item getQuick6() { return q6; }
	Item getItem(int curTab, int x, int y);

	Skill* getQSkill() { return QSkill; }
	Skill* getASkill() { return ASkill; }
	Skill* getSSkill() { return SSkill; }
	Skill* getDSkill() { return DSkill; }
	Skill* getFSkill() { return FSkill; }
	Skill* getGSkill() { return GSkill; }


	list<effectedOnTime> getAttackQueue() { return attackQueue; }
	list<effectedOnTime>::iterator getAttackQueueBegin() { return attackQueue.begin(); }
	list<effectedOnTime>::iterator getAttackQueueEnd() { return attackQueue.end(); }


	MapBase* getCurMap() { return curMap; }
	UI* getUI() { return ui; }
	status getStatus() { return Stat; }

	void hit(effectedOnTime h) { hitQueue.push_back(h); }

	player();
	~player();
};

