#pragma once
#include "player.h"

class player;
class UI
{
private:
	bool showPopup;
	int popupX, popupY;
	bool showInv;
	bool showStat;
	RECT inv,stat;
	RECT Weapon, Armor, Shoulder, Pants, Belt, Shoes;
	void drawWindow(int destX, int destY,int width, int height, int alpha = 0xFF);
	int curActiveTab;
	RECT itemrects[8][4];
	bool test;
	LPD3DXFONT d3dFont;
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

