#include "stdafx.h"
#include "UI.h"

//아이템 팝업 만들것!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void UI::drawWindow(int destX, int destY,int width, int height, int alpha)
{
		//0, 3, 6 11x, 1,4,7 - 12x, 2,5,8 - 10x

		//0,1,2 ,6,7,8 - 11y
		//3,4,5 - 13y
		FLOAT Xmul = (width - 21.f) /12.f;					//x축으로의 확대율
		FLOAT Ymul = (height - 22.f) /13.f;					//y축으로의 확대율

		IMAGEMANAGER->findImage("창_0")->render(destX, destY);		//왼쪽위

		IMAGEMANAGER->findImage("창_1")->scaledrender(destX+11, destY, Xmul);

		IMAGEMANAGER->findImage("창_2")->render(destX + 12 * Xmul+11, destY);
		//////////////////////////////////////////
		IMAGEMANAGER->findImage("창_3")->scaledrender(destX, destY+11,1.f, Ymul);

		IMAGEMANAGER->findImage("창_4")->scaledrender(destX + 11,destY+11,Xmul,Ymul);//제일중요

		IMAGEMANAGER->findImage("창_5")->scaledrender(destX + 12 * Xmul +11, destY+11, 1.f, Ymul);
		//////////////////////////////////////////////////////////
		IMAGEMANAGER->findImage("창_6")->render(destX , destY+ 13 * Ymul + 11);

		IMAGEMANAGER->findImage("창_7")->scaledrender(destX + 11,destY + 13*Ymul+11,Xmul);

		IMAGEMANAGER->findImage("창_8")->render(destX + 12 * Xmul+11 , destY+ 13 * Ymul + 11);
}

HRESULT UI::init(void)
{
	showInv = showStat = showPopup = popupX = popupY = false;
	inv = RectMake(WINSIZEX - 300, 50, 270, 400);
	stat = RectMake(inv.left - 270, 50, 260, 400);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			itemrects[j][i] = RectMake(inv.left + 13 + j * 30, inv.top + 162 + i * 30,28,28);
		}
	}
	Weapon = RectMake(inv.left + 15 + 178, inv.top + 30 + 4, 28, 28);
	Armor = RectMake(inv.left + 51, inv.top + 34, 28, 28);
	Pants = RectMake(inv.left + 15 + 4, inv.top + 30 + 36, 28, 28);
	Shoulder = RectMake(inv.left + 15 + 4, inv.top + 30 + 4, 28, 28);
	Belt = RectMake(inv.left + 15 + 36, inv.top + 30 + 36, 28, 28);
	Shoes = RectMake(inv.left + 15 + 4, inv.top + 30 + 68, 28, 28);
	d3dFont = NULL;
	if (FAILED(D3DXCreateFont(g_pd3dDevice,
		10, 0,
		FW_NORMAL,
		1,
		0,
		HANGUL_CHARSET,
		0,
		0,
		0,
		TEXT("궁서"),
		&d3dFont))) {
		return E_FAIL;
	}

	/*D3DXFONT_DESC desc;
	desc.CharSet = HANGUL_CHARSET;
	strcpy(desc.FaceName, "굴림");
	desc.Height = 15;
	desc.Width = 0;
	desc.Weight = FW_NORMAL;
	desc.Quality = DEFAULT_QUALITY;
	desc.MipLevels = 1;
	desc.Italic = 0;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.PitchAndFamily = FF_DONTCARE;
	D3DXCreateFontIndirect(g_pd3dDevice, &desc, &d3dFont);*/
	return S_OK;
}

void UI::release(void)
{
	d3dFont->Release();
	d3dFont = NULL;
}

void UI::update(void)
{
	if (showInv) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				if (PtInRect(&itemrects[j][i], ptMouse)) {
					if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)&&pl->equipments[j][i]->id !=-1) {
						pl->useItem(curActiveTab, j,i);
					}
				}
			}
		}

		if (PtInRect(&Weapon, ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && pl->getWeapon()->id != -1) {
				pl->unequip(5);
			}
		}
		if (PtInRect(&Armor, ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && pl->getArmor()->id != -1) {
				pl->unequip(0);
			}
		}
		if (PtInRect(&Pants, ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && pl->getPants()->id != -1) {
				pl->unequip(1);
			}
		}
		if (PtInRect(&Shoulder, ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && pl->getShoulder()->id != -1) {
				pl->unequip(2);
			}
		}
		if (PtInRect(&Belt, ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && pl->getBelt()->id != -1) {
				pl->unequip(3);
			}
		}
		if (PtInRect(&Shoes, ptMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && pl->getShoes()->id != -1) {
				pl->unequip(4);
			}
		}
	}
	if(showStat) {

	}
}

void UI::render(void)
{
	char tmp[50];
	int UI_top = WINSIZEY - IMAGEMANAGER->findImage("UI_하단_기본창")->getHeight();
	IMAGEMANAGER->findImage("UI_하단_기본창_조각")->DFuirender(0, WINSIZEY- IMAGEMANAGER->findImage("UI_하단_기본창_조각")->getHeight());
	IMAGEMANAGER->findImage("UI_하단_기본창")->DFuirender(0, UI_top);
	IMAGEMANAGER->findImage("UI_하단_기본창_확장")->DFuirender(508, UI_top);

	IMAGEMANAGER->findImage("UI_HP")->render(35, UI_top+9 + (IMAGEMANAGER->findImage("UI_HP")->getHeight() *(1-(float)pl->Stat.curHP / (float)pl->Stat.maxHP)),0,IMAGEMANAGER->findImage("UI_HP")->getHeight() * (1.f-((float)pl->Stat.curHP/(float)pl->Stat.maxHP)),0, IMAGEMANAGER->findImage("UI_HP")->getHeight() * (float)pl->Stat.curHP/(float)pl->Stat.maxHP);
	IMAGEMANAGER->findImage("UI_MP")->render(730, UI_top+9 + (IMAGEMANAGER->findImage("UI_MP")->getHeight() *(1 - (float)pl->Stat.curMP / (float)pl->Stat.maxMP)), 0, IMAGEMANAGER->findImage("UI_MP")->getHeight() * (1.f - ((float)pl->Stat.curMP / (float)pl->Stat.maxMP)), 0, IMAGEMANAGER->findImage("UI_MP")->getHeight() * (float)pl->Stat.curMP / (float)pl->Stat.maxMP);
	
	

	if (showInv) {
		char tmp[50];
		drawWindow(inv.left, inv.top, inv.right - inv.left, inv.bottom - inv.top);
		IMAGEMANAGER->findImage("UI_인벤토리_기본창")->DFuirender(inv.left+12,inv.top +25);
		IMAGEMANAGER->findImage("UI_인벤토리_장비베이스")->DFuirender(inv.left + 12+3,inv.top+25+5);

		if (pl->getArmor()->id != -1) {
			switch (pl->getArmor()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_상의_%d", pl->getArmor()->id);
				IMAGEMANAGER->findImage(tmp)->render(Armor.left, Armor.top);
				break;
			}
		}

		if (pl->getPants()->id != -1) {
			switch (pl->getPants()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_바지_%d", pl->getPants()->id);
				IMAGEMANAGER->findImage(tmp)->render(Pants.left, Pants.top);
				break;
			}
		}

		if (pl->getShoulder()->id != -1) {
			switch (pl->getShoulder()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_어깨_%d", pl->getShoulder()->id);
				IMAGEMANAGER->findImage(tmp)->render(Shoulder.left, Shoulder.top);
				break;
			}
		}

		if (pl->getBelt()->id != -1) {
			switch (pl->getBelt()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_벨트_%d", pl->getBelt()->id);
				IMAGEMANAGER->findImage(tmp)->render(Belt.left, Belt.top);
				break;
			}
		}

		if (pl->getShoes()->id != -1) {
			switch (pl->getShoes()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_신발_%d", pl->getShoes()->id);
				IMAGEMANAGER->findImage(tmp)->render(Shoes.left, Shoes.top);
				break;
			}
		}

		if (pl->getWeapon()->id != -1) {
			switch (pl->getWeapon()->detail) {
			case wp_sswd:
				sprintf(tmp, "소검_%d", pl->getWeapon()->id);
				IMAGEMANAGER->findImage(tmp)->render(Weapon.left,Weapon.top);
				break;
			case wp_kat:
				break;
			}
		}


		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				IMAGEMANAGER->findImage("UI_인벤토리_아이템_개별")->DFuirender(inv.left + 13+ j*30,inv.top + 162 + i * 30);
			}
		}
		switch (curActiveTab) {
		case 0:								//장비
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 8; j++) {
					switch (pl->equipments[j][i]->type) {
					case item_weapon:
						if (!pl->equipments[j][i]->equipped) {
							switch (pl->equipments[j][i]->detail) {
							case wp_sswd:
								sprintf(tmp, "소검_%d", pl->equipments[j][i]->id);
								IMAGEMANAGER->findImage(tmp)->render(inv.left + 13 + j * 30, inv.top + 162 + i * 30);
								break;
							case wp_kat:
								break;
							}
						}
						break;
					case item_coat:
						if (!pl->equipments[j][i]->equipped) {
							switch (pl->equipments[j][i]->detail) {
							case arm_plate:
								sprintf(tmp, "판금_상의_%d", pl->equipments[j][i]->id);
								IMAGEMANAGER->findImage(tmp)->render(inv.left + 13 + j * 30, inv.top + 162 + i * 30);
								break;
							}
						}
						break;
					case item_shoulder:
						if (!pl->equipments[j][i]->equipped) {
							switch (pl->equipments[j][i]->detail) {
							case arm_plate:
								sprintf(tmp, "판금_어깨_%d", pl->equipments[j][i]->id);
								IMAGEMANAGER->findImage(tmp)->render(inv.left + 13 + j * 30, inv.top + 162 + i * 30);
								break;
							}
						}
						break;
					case item_belt:
						if (!pl->equipments[j][i]->equipped) {
							switch (pl->equipments[j][i]->detail) {
							case arm_plate:
								sprintf(tmp, "판금_벨트_%d", pl->equipments[j][i]->id);
								IMAGEMANAGER->findImage(tmp)->render(inv.left + 13 + j * 30, inv.top + 162 + i * 30);
								break;
							}
						}
						break;
					case item_pants:
						if (!pl->equipments[j][i]->equipped) {
							switch (pl->equipments[j][i]->detail) {
							case arm_plate:
								sprintf(tmp, "판금_바지_%d", pl->equipments[j][i]->id);
								IMAGEMANAGER->findImage(tmp)->render(inv.left + 13 + j * 30, inv.top + 162 + i * 30);
								break;
							}
						}
						break;
					case item_shoes:
						if (!pl->equipments[j][i]->equipped) {
							switch (pl->equipments[j][i]->detail) {
							case arm_plate:
								sprintf(tmp, "판금_신발_%d", pl->equipments[j][i]->id);
								IMAGEMANAGER->findImage(tmp)->render(inv.left + 13 + j * 30, inv.top + 162 + i * 30);
								break;
							}
						}
						break;
					case -1:
						break;
					}
				}
			}
			break;
		case 1:								//소모품
			break;
		case 2:								//기타템
			break;
		}
	}
	if (showStat) {
		drawWindow(stat.left, stat.top, stat.right - stat.left, stat.bottom - stat.top);
		IMAGEMANAGER->findImage("UI_스텟_기본")->render(stat.left+8+6, stat.top+28+25);
		IMAGEMANAGER->findImage("UI_인벤토리_기본창")->render(stat.left+6, stat.top+25,0,0,246,112);
		IMAGEMANAGER->findImage("UI_인벤토리_장비베이스")->render(stat.left  + 8, stat.top + 26);
		if (pl->getArmor()->id != -1) {
			switch (pl->getArmor()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_상의_%d", pl->getArmor()->id);
				IMAGEMANAGER->findImage(tmp)->render(Armor.left-278, Armor.top-3);
				break;
			}
		}
		if (pl->getPants()->id != -1) {
			switch (pl->getPants()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_바지_%d", pl->getPants()->id);
				IMAGEMANAGER->findImage(tmp)->render(Pants.left-278, Pants.top-3);
				break;
			}
		}
		if (pl->getShoulder()->id != -1) {
			switch (pl->getShoulder()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_어깨_%d", pl->getShoulder()->id);
				IMAGEMANAGER->findImage(tmp)->render(Shoulder.left - 278, Shoulder.top - 3);
				break;
			}
		}
		if (pl->getBelt()->id != -1) {
			switch (pl->getBelt()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_벨트_%d", pl->getBelt()->id);
				IMAGEMANAGER->findImage(tmp)->render(Belt.left - 278, Belt.top - 3);
				break;
			}
		}
		if (pl->getShoes()->id != -1) {
			switch (pl->getShoes()->detail) {
			case arm_plate:
				sprintf(tmp, "판금_신발_%d", pl->getShoes()->id);
				IMAGEMANAGER->findImage(tmp)->render(Shoes.left - 278, Shoes.top - 3);
				break;
			}
		}
		if (pl->getWeapon()->id != -1) {
			switch (pl->getWeapon()->detail) {
			case wp_sswd:
				sprintf(tmp, "소검_%d", pl->getWeapon()->id);
				IMAGEMANAGER->findImage(tmp)->render(Weapon.left - 278, Weapon.top - 3);
				break;
			case wp_kat:
				break;
			}
		}
	}
	
}

void UI::renderdc(void)
{
	char test[200];

	if (showInv) {
		sprintf(test, "테스트중임");
		d3dFont->DrawTextA(
			NULL,
			test,
			-1,
			&RectMake(350, 350, 500, 50),
			DT_LEFT,
			D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		//Rectangle(hdc, inv.left, inv.top, inv.right, inv.bottom);
	}
	if (showStat) {
		//29,118,48,15


		/*
		118-137
		19 - Y끼리의 거리

		29 - 143

		114 - X끼리의 거리
		*/
		int t = 0;
		//HP출력부분
		{
			sprintf(test, "%d", pl->getStatus().curHP);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29, stat.top + 25 + 118, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "/");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29+40, stat.top + 25 + 118, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().maxHP);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29+40+10, stat.top + 25 + 118, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		//MP출력부분
		{

			sprintf(test, "%d", pl->getStatus().curMP);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143, stat.top + 25 + 118, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "/");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40, stat.top + 25 + 118, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().maxMP);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40 + 10, stat.top + 25 + 118, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		t++;

		//힘
		{
			sprintf(test, "%d", pl->getStatus().str);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29, stat.top + 25 + 118+19*t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40, stat.top + 25 + 118+19*t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_str);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40 + 10, stat.top + 25 + 118+19*t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		//지능
		{

			sprintf(test, "%d", pl->getStatus().intel);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143, stat.top + 25 + 118+19*t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40, stat.top + 25 + 118+19*t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_intel);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40 + 10, stat.top + 25 + 118+19*t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		t++;

		//체력
		{
			sprintf(test, "%d", pl->getStatus().health);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40, stat.top + 25 + 118 + 19 * t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_health);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40 + 10, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		//정신력
		{

			sprintf(test, "%d", pl->getStatus().spirit);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40, stat.top + 25 + 118 + 19 * t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_spirit);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40 + 10, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		t++;

		//물리공격력
		{
			sprintf(test, "%d", pl->getStatus().phyAtt);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40, stat.top + 25 + 118 + 19 * t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_phyAtt);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40 + 10, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		//물리방어
		{

			sprintf(test, "%d", pl->getStatus().phyDef);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40, stat.top + 25 + 118 + 19 * t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_phyDef);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40 + 10, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		t++;

		//마법공격력
		{
			sprintf(test, "%d", pl->getStatus().magAtt);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40, stat.top + 25 + 118 + 19 * t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_magAtt);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 29 + 40 + 10, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		//마법방어
		{

			sprintf(test, "%d", pl->getStatus().magDef);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));

			sprintf(test, "+");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40, stat.top + 25 + 118 + 19 * t, 10, 15),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

			sprintf(test, "%d", pl->getStatus().a_magDef);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(stat.left + 14 + 143 + 40 + 10, stat.top + 25 + 118 + 19 * t, 40, 15),
				DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		}
		t++;

	}
}

UI::UI()
{
}


UI::~UI()
{
}
