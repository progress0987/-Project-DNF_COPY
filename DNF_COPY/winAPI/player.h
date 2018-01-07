#pragma once
#include "gameNode.h"
#include "MapBase.h"
#include "UI.h"
#include "skills.h"

#define KEYDELAY 30
class UI;
class MapBase;

struct Item {
	int type;							//������ ������ �� ��
	int dmg;
	int def;

	int reachx;							//���⿡ ������
	int reachz;							//���⿡ ������

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
	int dmg;									//�����
	int dmgTick;								//������� �󸶸��� ������(ƽ/�ð�)
	effected area;								//����� Ÿ�� ����

	DWORD time;									//���� ����� ���۽ð�
	unsigned int staytime;						//���� ����� �����ð�

	bool isProjectile;							//����ü����
	bool isOnetime;								//���������� ���°���(�ʿ�����?)

	FLOAT pushX, pushY;							//�� ������ �о�� ����
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

struct status {//���� - �߰��Ұ�

};

//struct dmgstruct {
//	int dmg;									//�����
//	unsigned long time;							//������ �� ���� �ð�
//	unsigned int staytime;						//���� ����� �����ð�
//	bool isProjectile;							//����ü����
//	bool isOnetime;								//���������� ���°���(�ʿ�����?)
//	int dmgFrame;								//������� �� ������ - ��ų�ܿ��� �� ����(�Ⱦ�����)
//	FLOAT pushX, pushY;							//�� ������ �о�� ����
//	int maxz, minz;								//�ִ�/�ּ� z����� ����
//	int maxx, minx;								//�ִ�/�ּ� x����� ����
//	int maxy, miny;								//�ִ�/�ּ� y����� ����
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
	
	bool curDir;							//���� ����
	bool onAttack;							//���� ��������
	bool onSkill;
	bool onJump;							//������������
	int movestatus;							//������������ : 0 �ȱ� : 1 �ٱ� : 2
	float jumpPow;
	FLOAT x, y, z;
	bool onDebug;

	
	//////////////////////////��ų��
	wave* skill_wave;
	upper* skill_upper;
	icewave* skill_icewave;


	status Stat;
	STANCE prevStance;
	STANCE curStance;
	STANCE nextStance;
	MapBase* curMap;

	Skill* curSkill;

	UI* ui;
	list<effectedOnTime> attackQueue;
	list<inputStruct> inputQueue;

	/////////////////////////////////���///////////////////////
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
	void setSkills();
	void updateSkills();
	void printSkillb();
	void printSkillf();




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

