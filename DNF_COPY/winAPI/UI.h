#pragma once
static struct Item {
	string name;
	char imgName[50];
	int branch;							//���ο��� ����� �������ִ���, ������������ �������(������ 0);
	int id;								//������ �̹��� id
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
	Item* item;
	bool isGold;
	int goldamount;
	FLOAT xVel, yVel;
	FLOAT x, y, z;
	int Tick;
	FLOAT angle;
};

class UI
{
private:
	bool showPopup;
	Item* popupItem;
	bool showInv;
	bool showStat;
	RECT inv,stat;
	RECT Weapon, Armor, Shoulder, Pants, Belt, Shoes;
	RECT q1, q2, q3, q4, q5, q6;
	RECT tabEquip, tabConsume;
	void drawWindow(int destX, int destY,int width, int height, int alpha = 0xFF);
	int curActiveTab;
	RECT itemrects[8][4];
	bool test;
	LPD3DXFONT d3dFont;
	Item* onHold;
	int onHoldPosX, onHoldPosY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);

	void showinv() { showInv = !showInv; }
	void showstat() { showStat = !showStat; }
	void setCurActiveTab(int active = 0) { curActiveTab = active; }

	UI();
	~UI();
};

