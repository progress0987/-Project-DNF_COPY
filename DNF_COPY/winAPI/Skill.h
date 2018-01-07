#pragma once

extern struct effectedOnTime;



class Skill////////////////��ų �� ��
{
protected:

	int count;
	int framecount;
	int effect;

	int curAction;													//���� ���ϰ��ִ� �׼��� ������
	
	int reqMana;

	bool isbuff;

	FLOAT x, y, z;													//�÷��̾��� ������

	DWORD cooldownstartfrom;													//��Ÿ��
	int cooldownTick;

	bool isChargable;												//����������
	int chargemax;
	int curcharge;
	int chargeamount;												//ƽ�� �󸶳� ������
	int chargetick;													//��ƽ�� ��������

	int staytime;													//�����ð� -�ʿ�?

	bool isSpot;													//�������ִ���
	POINT spot;														//�������� �ִ� ��ų�߿� ���� ��ǥ�� �����°�


public:
	bool oncast,finished;
	bool onCooldown;
	virtual HRESULT init();
	virtual void cast(FLOAT x, FLOAT y, FLOAT z);
	virtual void update();
	virtual void renderb();
	virtual void renderf();

	int getCurAction() { return curAction; }
	Skill();
	~Skill();
};
