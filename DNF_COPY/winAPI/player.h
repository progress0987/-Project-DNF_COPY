#pragma once
#include "gameNode.h"
#include "MapBase.h"
#include "UI.h"

#define KEYDELAY 200
class UI;
class MapBase;
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
	stance_empowered_norm_1	 , 	//��ȭ��Ÿ1��
	stance_empowered_norm_2	 ,	//��ȭ��Ÿ2��
	stance_empowered_norm_3	 ,	//��ȭ��Ÿ3��
};
enum SKILLS {
	//����� ��ų�� �̸� / ��Ȳó��
	skill_NULL,
	skill_norm_1,
	skill_norm_2,
	skill_norm_3,
	skill_upper,
};

struct status {//���� - �߰��Ұ�

};

struct dmgstruct {
	int dmg;									//�����
	unsigned long time;							//������ �� ���� �ð�
	unsigned int staytime;						//���� ����� �����ð�
	bool isProjectile;							//����ü����
	bool isOnetime;								//���������� ���°���(�ʿ�����?)
	int dmgFrame;								//������� �� ������ - ��ų�ܿ��� �� ����(�Ⱦ�����)
	int maxz, minz;								//�ִ�/�ּ� z����� ����
	int maxx, minx;								//�ִ�/�ּ� x����� ����
	int maxy, miny;								//�ִ�/�ּ� y����� ����
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
	
	bool curDir;							//���� ����
	bool onAttack;							//���� ��������
	bool onSkill;
	bool onJump;							//������������
	int movestatus;							//������������ : 0 �ȱ� : 1 �ٱ� : 2
	float jumpPow;
	FLOAT x, y, z;
	bool onDebug;

	status Stat;
	STANCE prevStance;
	STANCE curStance;
	STANCE nextStance;
	SKILLS curSkill;
	SKILLS nextSkill;
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



	FLOAT getX() { return x; }
	FLOAT getY() { return y; }
	FLOAT getZ() { return z; }
	list<dmgstruct> getAttackQueue() { return attackQueue; }
	MapBase* getCurMap() { return curMap; }
	UI* getUI() { return ui; }

	player();
	~player();
};

