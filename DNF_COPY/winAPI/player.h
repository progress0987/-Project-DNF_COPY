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
	int mindmg;									//�����
	int maxdmg;
	int dmgTick;								//������� �󸶸��� ������(ƽ/�ð�)
	effected area;								//����� Ÿ�� ����

	DWORD time;									//���� ����� ���۽ð�
	unsigned int staytime;						//���� ����� �����ð�

	bool isProjectile;							//����ü����
	bool isOnetime;								//���������� ���°���(�ʿ�����?)
	bool isHold;								//Ȧ�����·� ����°���
	bool isMove;								//������ �̵���Ű����
	bool isAbnormal;							//�����̻�����
	bool isCrit;								//ũ��Ƽ������
	int abnormal;								//� �����̻����� 0-���� 9-Ȧ�� 10-ȭ�� 50-�Ÿ��� �̵���Ű��

	FLOAT pushX, pushY,pushZ;							//�� ������ �о�� ����
	FLOAT attr1,attr2,attr3,attr4;						//�޾ƿ��� ����
	vector<string> effectNames;							//Ȧ���� ����Ʈ��ų �̸�
};

enum STANCE {
	stance_NULL				 = -1,				//�ڼ�������
	stance_norm_1			 = 0,				//��Ÿ 1��
	stance_norm_2			 = 9,				//��Ÿ 2��
	stance_norm_3			 = 33,				//��Ÿ 3��
	stance_upper			 = 42,				//���۽�����
	stance_thrust			 = 65,				//������Ʈ
	stance_handup			 = 75,				//�յ��
	stance_ready			 = 90,				//�����غ��ڼ�
	stance_hit				 = 96,				//�´��ڼ�
	stance_down				 = 100,				//���������ڼ�
	stance_run				 = 105,				//�ٴ��ڼ�
	stance_jump_up			 = 125,				//�����ö󰡴��ڼ�
	stance_jump_down		 = 128,				//�������������ڼ�
	stance_areal_att		 = 133,				//���߰���
	stance_sit				 = 157,				//�ɱ�(�ݱ��)
	stance_handfront		 = 159,				//�վ����λ���
	stance_idle				 = 176,				//�⺻�ڼ�(�����ڼ�)
	stance_walk				 = 180,				//�ȴ��ڼ�
	stance_onSkill			 = 9999,			//��ų����(�ش� ��ų�κ��� �ڼ��� �޾ƿ;���)
};
enum SKILLS {
	//����� ��ų�� �̸� / ��Ȳó��
	skill_NULL,
	skill_norm_1,
	skill_norm_2,
	skill_norm_3,
	skill_upper,
	skill_areal_Atk,
};

struct status {			//����, a������ �߰���
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
	float phycritrate, magcritrate;//�Ⱦ�����
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
	
	bool curDir;							//���� ����
	bool onAttack;							//���� ��������
	bool onSkill;
	bool onJump;							//������������
	bool onHit;								//�´»�������
	bool printblood;

	bool onLevelup;
	bool levelupEffect;
	int levelupTick;


	int Coin;
	int deadTick;

	int onHeal;								//0 ���� 1 ü�� 2 ���� 3 �Ѵ�
	int onHealFrame;
	int bloodframe;

	int hitcount;

	int movestatus;							//������������ : 0 �ȱ� : 1 �ٱ� : 2
	float jumpPow;
	FLOAT x, y, z;

	//////////////////////////��ų��
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


	/////////////////////////////////���///////////////////////

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

	bool test;
public:
	bool reset;
	Item emptyWeapon;
	Item empty;
	status Stat;									//����
	int gold;
	vector<Item> equipments;
	vector<Item> consume;
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);
	void gainEXP(int amount);
	void resetPlayer();



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
	Item getNecklace() { return Necklece; }
	Item getBraclet() { return Bracelet; }
	Item getRing() { return Ring; }
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

