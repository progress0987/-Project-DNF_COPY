#pragma once
#include "Universal_structs.h"

static LPD3DXFONT d3dFont;

static void drawWindow(int destX, int destY, int width, int height, int alpha =0xff);
class UI
{
private:
	bool showPopup;
	Item* popupItem;
	bool showInv;
	bool showStat;
	bool showShop;
	RECT inv, stat, shop;
	RECT shopClose;
	RECT shopItemRC[12];
	RECT Weapon, Armor, Shoulder, Pants, Belt, Shoes;
	RECT q1, q2, q3, q4, q5, q6;
	RECT qa, qs, qd, qf, qg, qh, qq, qw, qe, qr, qt;
	RECT tabEquip, tabConsume;
	int curActiveTab;
	RECT itemrects[8][4];
	bool test;
	Item* onHold;
	int onHoldPosX, onHoldPosY;
	vector<Item> merch;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);

	void showinv() { showInv = !showInv; }
	void showstat() { showStat = !showStat; }
	void openShop(vector<Item> merchandices);
	void setCurActiveTab(int active = 0) { curActiveTab = active; }

	UI();
	~UI();
};

