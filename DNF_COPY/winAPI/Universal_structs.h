#pragma once


static struct Item {
	string name;
	char imgName[50];
	int branch;							//내부에서 몇개까지 갈라져있는지, 갈라져있으면 몇번인지(없으면 0);
	int id;								//아이템 이미지 id
	int onfieldid;
	int type;							//아이템 종류로 할 것
	int detail;							//아이템 세부사항

	int stack;							//소모/기타 아이템 한정

	int phydmgmin;							//무기한정
	int magdmgmin;
	int phydmgmax;
	int magdmgmax;

	int phydef;
	int magdef;

	int reachx;							//무기에 한정됨
	int reachz;							//무기에 한정됨

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