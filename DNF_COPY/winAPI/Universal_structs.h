#pragma once


static struct Item {
	string name;
	char imgName[50];
	int branch;							//���ο��� ����� �������ִ���, ������������ �������(������ 0);
	int id;								//������ �̹��� id
	int onfieldid;
	int type;							//������ ������ �� ��
	int detail;							//������ ���λ���

	int stack;							//�Ҹ�/��Ÿ ������ ����

	int phydmgmin;							//��������
	int magdmgmin;
	int phydmgmax;
	int magdmgmax;

	int phydef;
	int magdef;

	int reachx;							//���⿡ ������
	int reachz;							//���⿡ ������

	int gainStr;
	int gainInt;
	int gainHealth;
	int gainSpirit;

	int gainHP;
	int gainMP;

	int reqlvl;

	bool equipped;

	int price;

	string description;
};

static struct DropItemStruct {
	Item item;
	bool isGold;
	int goldamount;
	FLOAT xVel, yVel;
	FLOAT x, y, z;
	int Tick;
	FLOAT angle;
};