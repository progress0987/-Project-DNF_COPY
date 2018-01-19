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
	showInv = showStat = showPopup = false;
	popupItem = &pl->empty;
	inv = RectMake(WINSIZEX - 300, 50, 270, 400);
	stat = RectMake(inv.left - 270, 50, 260, 400);
	q1 = RectMake(100, 518 + 42, 30, 30);
	q2 = RectMake(130, 518 + 42, 30, 30);
	q3 = RectMake(160, 518 + 42, 30, 30);
	q4 = RectMake(170, 518 + 42, 30, 30);
	q5 = RectMake(210, 518 + 42, 30, 30);
	q6 = RectMake(240, 518 + 42, 30, 30);
	tabEquip = RectMake(520, 210 - 21, 62, 21);
	tabConsume = RectMake(520 + 65, 210 - 21, 62, 21);
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

	onHold = new Item();
	onHold = &pl->empty;

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
		TEXT("돋움"),
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
	//SAFE_DELETE(onHold);
	d3dFont->Release();
	d3dFont = NULL;
}

void UI::update(void)
{
	showPopup = false;
	popupItem = &pl->empty;

	///////////퀵슬롯에서 우클릭
	{
		if (PtInRect(&q1, ptMouse)) {
			if (rclicked) {
				pl->useItem(-1, 1, -1);
				rclicked = false;
			}
		}
		if (PtInRect(&q2, ptMouse)) {
			if (rclicked) {
				pl->useItem(-1, 2, -1);
				rclicked = false;
			}
		}
		if (PtInRect(&q3, ptMouse)) {
			if (rclicked) {
				pl->useItem(-1, 3, -1);
				rclicked = false;
			}
		}
		if (PtInRect(&q4, ptMouse)) {
			if (rclicked) {
				pl->useItem(-1, 4, -1);
				rclicked = false;
			}
		}
		if (PtInRect(&q5, ptMouse)) {
			if (rclicked) {
				pl->useItem(-1, 5, -1);
				rclicked = false;
			}
		}
		if (PtInRect(&q6, ptMouse)) {
			if (rclicked) {
				pl->useItem(-1, 6, -1);
				rclicked = false;
			}
		}
	}

	if (showInv) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				if (PtInRect(&itemrects[j][i], ptMouse)) {//아이템 팝업
					switch (curActiveTab) {
					case 0:
						if (!clicked && (pl->equipments[j + i * 8].id > 0)) {
							showPopup = true;
							popupItem = &pl->equipments[j + i * 8];
						}
						break;
					case 1:
						if (!clicked && (pl->consume[j + i * 8].id > 0)) {
							showPopup = true;
							popupItem = &pl->consume[j + i * 8];
						}
						break;
					case 2:
						break;
					}
					if (rclicked) {
						pl->useItem(curActiveTab, j,i);
						rclicked = false;
						showPopup = false;
						popupItem = &pl->empty;
					}
					if (clicked) {//아이템 클릭																	인벤창에서 마우스 끌면 아이템 셔플됨
						switch (curActiveTab) {
						case 0:
							if (pl->equipments[j + i * 8].id > 0) {
								onHold = &pl->equipments[j + i * 8];
								onHoldPosX = j;
								onHoldPosY = i;
							}
							break;
						case 1:
							if (pl->consume[j + i * 8].id > 0) {
								//memcpy(&onHold,&(pl->consume[j + i * 8]),sizeof(Item));
								onHold = &pl->consume[j + i * 8];
								onHoldPosX = j;
								onHoldPosY = i;
							}
							break;
						}
					}
				}
			}
		}

		if (!clicked) {										//마우스를뗐을때
			if (onHold->id > 0) {													//잡고있는게 아이템일경우
																					//마우스를 놓은 지점이 놓아도 되는곳이 아닌경우
				if (!(PtInRect(&inv, ptMouse) || PtInRect(&q1, ptMouse) || PtInRect(&q2, ptMouse) || PtInRect(&q3, ptMouse) || PtInRect(&q4, ptMouse) || PtInRect(&q5, ptMouse) || PtInRect(&q6, ptMouse))) {
				
					if (pl->getCurMap()->isPeaceful()) {
						onHold = &pl->empty;
					}
					else {															//아이템드롭!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						DropItemStruct t;
						//Item* tmp = new Item;
						//memcpy(tmp,&pl->equipments[onHoldPosX + onHoldPosY * 8],sizeof(Item));
						//t.item = tmp;
						t.item = pl->getCurMap()->adddroppedItem(pl->equipments[onHoldPosX + onHoldPosY * 8]);
						t.xVel = t.yVel = t.Tick = t.isGold = t.goldamount = 0;
						t.x = pl->getX();
						t.z = pl->getZ();
						t.y = -100;
						t.angle = 0;
						pl->getCurMap()->DropItem(t);
						if (onHold->type == item_consume) {
							pl->consume[onHoldPosX + onHoldPosY * 8] = pl->empty;
							onHold = &pl->empty;
						}
						else if (onHold->type == item_etc) {

						}
						else {
							pl->equipments[onHoldPosX + onHoldPosY * 8] = pl->empty;
							onHold = &pl->empty;
						}
					}
				}
				else if (PtInRect(&this->inv, ptMouse)) {
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 8; j++) {
							if (PtInRect(&itemrects[j][i], ptMouse)) {
								if (onHold->type == item_consume) {
									Item t = *onHold;
									pl->consume[onHoldPosX + onHoldPosY * 8] = pl->consume[j + i * 8];
									pl->consume[j + i * 8] = t;
									onHold = &pl->empty;
								}
								else {
									Item t = *onHold;
									pl->equipments[onHoldPosX + onHoldPosY * 8] = pl->equipments[j + i * 8];
									pl->equipments[j + i * 8] = t;
									onHold = &pl->empty;
								}
							}
						}
					}
				}
				else if (PtInRect(&q1, ptMouse)) {
					if (onHold->type == item_consume) {
						pl->consume[onHoldPosX + onHoldPosY * 8] = pl->setquickslot(1, *onHold);
					}
				}
				else if (PtInRect(&q2, ptMouse)) {
					if (onHold->type == item_consume) {
						pl->consume[onHoldPosX + onHoldPosY * 8] = pl->setquickslot(2, *onHold);
					}
				}
				else if (PtInRect(&q3, ptMouse)) {
					if (onHold->type == item_consume) {
						pl->consume[onHoldPosX + onHoldPosY * 8] = pl->setquickslot(3, *onHold);
					}
				}
				else if (PtInRect(&q4, ptMouse)) {
					if (onHold->type == item_consume) {
						pl->consume[onHoldPosX + onHoldPosY * 8] = pl->setquickslot(4, *onHold);
					}
				}
				else if (PtInRect(&q5, ptMouse)) {
					if (onHold->type == item_consume) {
						pl->consume[onHoldPosX + onHoldPosY * 8] = pl->setquickslot(5, *onHold);
					}
				}
				else if (PtInRect(&q6, ptMouse)) {
					if (onHold->type == item_consume) {
						pl->consume[onHoldPosX + onHoldPosY * 8] = pl->setquickslot(6, *onHold);
					}
				}
				onHold = &pl->empty;
				onHoldPosX = -1;
				onHoldPosY = -1;
			}
		}

		if (onHold->id > 0) {
			switch (onHold->type) {
			case item_consume:
				curActiveTab = 1;
				break;
			case item_etc:
				curActiveTab = 2;
				break;
			default:
				curActiveTab = 0;
				break;
			}
		}

		if (PtInRect(&tabEquip, ptMouse)) {
			if (clicked) {
				curActiveTab = 0;
			}
		}

		if (PtInRect(&tabConsume, ptMouse)) {
			if (clicked) {
				curActiveTab = 1;
			}
		}

		if (PtInRect(&Weapon, ptMouse)) {
			if (rclicked && pl->getWeapon().id != -1) {
				pl->unequip(5);
			}
		}
		if (PtInRect(&Armor, ptMouse)) {
			if (rclicked && pl->getArmor().id != -1) {
				pl->unequip(0);
			}
		}
		if (PtInRect(&Pants, ptMouse)) {
			if (rclicked && pl->getPants().id != -1) {
				pl->unequip(1);
			}
		}
		if (PtInRect(&Shoulder, ptMouse)) {
			if (rclicked && pl->getShoulder().id != -1) {
				pl->unequip(2);
			}
		}
		if (PtInRect(&Belt, ptMouse)) {
			if (rclicked && pl->getBelt().id != -1) {
				pl->unequip(3);
			}
		}
		if (PtInRect(&Shoes, ptMouse)) {
			if (rclicked && pl->getShoes().id != -1) {
				pl->unequip(4);
			}
		}
	}
}

void UI::render(void)
{
	char tmp[50];
	int invcount=0;
	int UI_top = WINSIZEY - IMAGEMANAGER->findImage("UI_하단_기본창")->getHeight();
	IMAGEMANAGER->findImage("UI_하단_기본창_조각")->DFuirender(0, WINSIZEY- IMAGEMANAGER->findImage("UI_하단_기본창_조각")->getHeight());
	IMAGEMANAGER->findImage("UI_하단_기본창")->DFuirender(0, UI_top);
	IMAGEMANAGER->findImage("UI_하단_기본창_확장")->DFuirender(508, UI_top);

	IMAGEMANAGER->findImage("UI_HP")->render(35, UI_top+9 + (IMAGEMANAGER->findImage("UI_HP")->getHeight() *(1-(float)pl->Stat.curHP / (float)pl->Stat.maxHP)),0,IMAGEMANAGER->findImage("UI_HP")->getHeight() * (1.f-((float)pl->Stat.curHP/(float)pl->Stat.maxHP)),0, IMAGEMANAGER->findImage("UI_HP")->getHeight() * (float)pl->Stat.curHP/(float)pl->Stat.maxHP);
	IMAGEMANAGER->findImage("UI_MP")->render(730, UI_top+9 + (IMAGEMANAGER->findImage("UI_MP")->getHeight() *(1 - (float)pl->Stat.curMP / (float)pl->Stat.maxMP)), 0, IMAGEMANAGER->findImage("UI_MP")->getHeight() * (1.f - ((float)pl->Stat.curMP / (float)pl->Stat.maxMP)), 0, IMAGEMANAGER->findImage("UI_MP")->getHeight() * (float)pl->Stat.curMP / (float)pl->Stat.maxMP);
	if (pl->getQuick1().id > 0) {
		sprintf(tmp, "소모_%d", pl->getQuick1().id);
		IMAGEMANAGER->findImage(tmp)->render(q1.left+1,q1.top+1);
	}
	if (pl->getQuick2().id > 0) {
		sprintf(tmp, "소모_%d", pl->getQuick2().id);
		IMAGEMANAGER->findImage(tmp)->render(q2.left + 1, q2.top + 1);
	}
	if (pl->getQuick3().id > 0) {
		sprintf(tmp, "소모_%d", pl->getQuick3().id);
		IMAGEMANAGER->findImage(tmp)->render(q3.left + 1, q3.top + 1);
	}
	if (pl->getQuick4().id > 0) {
		sprintf(tmp, "소모_%d", pl->getQuick4().id);
		IMAGEMANAGER->findImage(tmp)->render(q4.left + 1, q4.top + 1);
	}
	if (pl->getQuick5().id > 0) {
		sprintf(tmp, "소모_%d", pl->getQuick5().id);
		IMAGEMANAGER->findImage(tmp)->render(q5.left + 1, q5.top + 1);
	}
	if (pl->getQuick6().id > 0) {
		sprintf(tmp, "소모_%d", pl->getQuick6().id);
		IMAGEMANAGER->findImage(tmp)->render(q6.left + 1, q6.top + 1);
	}
	


	if (showInv) {
		char tmp[50];
		drawWindow(inv.left, inv.top, inv.right - inv.left, inv.bottom - inv.top);
		IMAGEMANAGER->findImage("UI_인벤토리_기본창")->DFuirender(inv.left+12,inv.top +25);
		IMAGEMANAGER->findImage("UI_인벤토리_장비베이스")->DFuirender(inv.left + 12+3,inv.top+25+5);
		IMAGEMANAGER->findImage("UI_인벤토리_하단")->DFuirender(inv.left + 12, inv.bottom - IMAGEMANAGER->findImage("UI_인벤토리_하단")->getHeight() - 25);
		

		if (pl->getArmor().id != -1) {
			switch (pl->getArmor().detail) {
			case arm_plate:
				sprintf(tmp, "판금_상의_%d", pl->getArmor().id);
				IMAGEMANAGER->findImage(tmp)->render(Armor.left, Armor.top);
				break;
			}
		}

		if (pl->getPants().id != -1) {
			switch (pl->getPants().detail) {
			case arm_plate:
				sprintf(tmp, "판금_바지_%d", pl->getPants().id);
				IMAGEMANAGER->findImage(tmp)->render(Pants.left, Pants.top);
				break;
			}
		}

		if (pl->getShoulder().id != -1) {
			switch (pl->getShoulder().detail) {
			case arm_plate:
				sprintf(tmp, "판금_어깨_%d", pl->getShoulder().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoulder.left, Shoulder.top);
				break;
			}
		}

		if (pl->getBelt().id != -1) {
			switch (pl->getBelt().detail) {
			case arm_plate:
				sprintf(tmp, "판금_벨트_%d", pl->getBelt().id);
				IMAGEMANAGER->findImage(tmp)->render(Belt.left, Belt.top);
				break;
			}
		}

		if (pl->getShoes().id != -1) {
			switch (pl->getShoes().detail) {
			case arm_plate:
				sprintf(tmp, "판금_신발_%d", pl->getShoes().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoes.left, Shoes.top);
				break;
			}
		}

		if (pl->getWeapon().id != -1) {
			switch (pl->getWeapon().detail) {
			case wp_sswd:
				sprintf(tmp, "소검_%d", pl->getWeapon().id);
				IMAGEMANAGER->findImage(tmp)->render(Weapon.left,Weapon.top);
				break;
			case wp_kat:
				break;
			}
		}

		if (curActiveTab == 0) {
			IMAGEMANAGER->findImage("UI_인벤토리_활성탭")->render(tabEquip.left, tabEquip.top);
		}
		else {
			IMAGEMANAGER->findImage("UI_인벤토리_비활성탭")->render(tabEquip.left+1, tabEquip.top+1);
		}

		if (curActiveTab == 1) {
			IMAGEMANAGER->findImage("UI_인벤토리_활성탭")->render(tabConsume.left, tabConsume.top);
		}
		else {
			IMAGEMANAGER->findImage("UI_인벤토리_비활성탭")->render(tabConsume.left+1, tabConsume.top+1);
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				IMAGEMANAGER->findImage("UI_인벤토리_아이템_개별")->DFuirender(inv.left + 13+ j*30,inv.top + 162 + i * 30);
			}
		}
		switch (curActiveTab) {
		case 0:								//장비
			for (vector<Item>::iterator i =pl->equipments.begin(); i !=pl->equipments.end(); i++) {
				if (onHold->id > 0 && i == (pl->equipments.begin() + onHoldPosX + onHoldPosY * 8)) {
					invcount++;
					switch (i->type) {
					case item_weapon:
						if (!i->equipped) {
							switch (i->detail) {
							case wp_sswd:
								sprintf(tmp, "소검_%d", i->id);
								break;
							case wp_kat:
								break;
							}
						}
						break;
					case item_coat:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "판금_상의_%d", i->id);
								break;
							}
						}
						break;
					case item_shoulder:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "판금_어깨_%d", i->id);
								break;
							}
						}
						break;
					case item_belt:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "판금_벨트_%d", i->id);
								break;
							}
						}
						break;
					case item_pants:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "판금_바지_%d", i->id);
								break;
							}
						}
						break;
					case item_shoes:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "판금_신발_%d", i->id);
								break;
							}
						}
						break;
					case -1:
						break;
					}
					IMAGEMANAGER->findImage(tmp)->render(ptMouse.x, ptMouse.y);
					continue; 
				}
				switch (i->type) {
				case item_weapon:
					if (!i->equipped) {
						switch (i->detail) {
						case wp_sswd:
							sprintf(tmp, "소검_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount%8][invcount/8].left-1,itemrects[invcount%8][invcount/8].top-1);
							break;
						case wp_kat:
							break;
						}
					}
					break;
				case item_coat:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "판금_상의_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount%8][invcount/8].left-1,itemrects[invcount%8][invcount/8].top-1);
							break;
						}
					}
					break;
				case item_shoulder:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "판금_어깨_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount%8][invcount/8].left-1,itemrects[invcount%8][invcount/8].top-1);
							break;
						}
					}
					break;
				case item_belt:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "판금_벨트_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount%8][invcount/8].left-1,itemrects[invcount%8][invcount/8].top-1);
							break;
						}
					}
					break;
				case item_pants:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "판금_바지_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount%8][invcount/8].left-1,itemrects[invcount%8][invcount/8].top-1);
							break;
						}
					}
					break;
				case item_shoes:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "판금_신발_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount%8][invcount/8].left-1,itemrects[invcount%8][invcount/8].top-1);
							break;
						}
					}
					break;
				case -1:
					break;
				}
				invcount++;
			}
			break;
		case 1:								//소모품
			for (vector<Item>::iterator i = pl->consume.begin(); i != pl->consume.end(); i++) {
				if (i->id > 0) {
					if (onHold->id>0&&i == (pl->consume.begin() + onHoldPosX + onHoldPosY * 8)) {
						sprintf(tmp, "소모_%d", i->id);
						IMAGEMANAGER->findImage(tmp)->render(ptMouse.x,ptMouse.y);
						invcount++;
					}
					else {
						sprintf(tmp, "소모_%d", i->id);
						IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left - 1, itemrects[invcount % 8][invcount / 8].top - 1);
						invcount++;
					}
				}
				else {
					invcount++;
				}
			}
			break;
		case 2:								//기타템
			break;
		}
		if (showPopup) {//팝업 보여주는거면
			drawWindow(ptMouse.x, ptMouse.y, 200, 200);
			switch (curActiveTab) {
			case 0:								//장비
				switch (popupItem->type) {
				case item_weapon:
					switch (popupItem->detail) {
					case wp_sswd:
						sprintf(tmp, "소검_%d", popupItem->id);
						break;
					case wp_kat:
						break;
					}
					break;
				case item_coat:
					switch (popupItem->detail) {
					case arm_plate:
						sprintf(tmp, "판금_상의_%d", popupItem->id);
						break;
					}
					break;
				case item_shoulder:
				
					switch (popupItem->detail) {
					case arm_plate:
						sprintf(tmp, "판금_어깨_%d", popupItem->id);
						break;
					}
				
					break;
				case item_belt:
					switch (popupItem->detail) {
					case arm_plate:
						sprintf(tmp, "판금_벨트_%d", popupItem->id);
						break;
					}
					break;
				case item_pants:
					switch (popupItem->detail) {
					case arm_plate:
						sprintf(tmp, "판금_바지_%d", popupItem->id);
						break;
					}
					break;
				case item_shoes:
					switch (popupItem->detail) {
					case arm_plate:
						sprintf(tmp, "판금_신발_%d", popupItem->id);
						break;
					}
					break;
				case -1:
					break;
				}
				IMAGEMANAGER->findImage(tmp)->render(ptMouse.x + 15, ptMouse.y + 15);
				break;
			case 1:								//소모품
				sprintf(tmp, "소모_%d", popupItem->id);
				IMAGEMANAGER->findImage(tmp)->render(ptMouse.x+15, ptMouse.y+15);
				invcount++;
				break;
			case 2:								//기타템
				break;
			}
		}
	}
	if (showStat) {
		drawWindow(stat.left, stat.top, stat.right - stat.left, stat.bottom - stat.top);
		IMAGEMANAGER->findImage("UI_스텟_기본")->render(stat.left+8+6, stat.top+28+25);
		IMAGEMANAGER->findImage("UI_인벤토리_기본창")->render(stat.left+6, stat.top+25,0,0,246,112);
		IMAGEMANAGER->findImage("UI_인벤토리_장비베이스")->render(stat.left  + 8, stat.top + 26);
		if (pl->getArmor().id != -1) {
			switch (pl->getArmor().detail) {
			case arm_plate:
				sprintf(tmp, "판금_상의_%d", pl->getArmor().id);
				IMAGEMANAGER->findImage(tmp)->render(Armor.left-278, Armor.top-3);
				break;
			}
		}
		if (pl->getPants().id != -1) {
			switch (pl->getPants().detail) {
			case arm_plate:
				sprintf(tmp, "판금_바지_%d", pl->getPants().id);
				IMAGEMANAGER->findImage(tmp)->render(Pants.left-278, Pants.top-3);
				break;
			}
		}
		if (pl->getShoulder().id != -1) {
			switch (pl->getShoulder().detail) {
			case arm_plate:
				sprintf(tmp, "판금_어깨_%d", pl->getShoulder().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoulder.left - 278, Shoulder.top - 3);
				break;
			}
		}
		if (pl->getBelt().id != -1) {
			switch (pl->getBelt().detail) {
			case arm_plate:
				sprintf(tmp, "판금_벨트_%d", pl->getBelt().id);
				IMAGEMANAGER->findImage(tmp)->render(Belt.left - 278, Belt.top - 3);
				break;
			}
		}
		if (pl->getShoes().id != -1) {
			switch (pl->getShoes().detail) {
			case arm_plate:
				sprintf(tmp, "판금_신발_%d", pl->getShoes().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoes.left - 278, Shoes.top - 3);
				break;
			}
		}
		if (pl->getWeapon().id != -1) {
			switch (pl->getWeapon().detail) {
			case wp_sswd:
				sprintf(tmp, "소검_%d", pl->getWeapon().id);
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
		//sprintf(test, "테스트중임");
		//d3dFont->DrawTextA(
		//	NULL,
		//	test,
		//	-1,
		//	&RectMake(350, 350, 500, 50),
		//	DT_LEFT,
		//	D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		//Rectangle(hdc, inv.left, inv.top, inv.right, inv.bottom);

		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 8; j++) {
		//		Rectangle(hdc, itemrects[j][i].left, itemrects[j][i].top, itemrects[j][i].right, itemrects[j][i].bottom);
		//	}
		//}

//#pragma region 돈 출력부분
		//돈 출력부분
		{
			sprintf(test, "%d", pl->gold);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(inv.left + 12 + 25, inv.bottom - IMAGEMANAGER->findImage("UI_인벤토리_하단")->getHeight() - 24, 77, 21),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}
//#pragma endregion
		//장비
		{
			sprintf(test, "장비");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&tabEquip,
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}
		//소모품
		{
			sprintf(test, "소모품");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&tabConsume,
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}

		if (showPopup) {//팝업출력(아이템 이름등등
			switch (popupItem->type) {
			case item_weapon:
			{
				sprintf(test, "%s", popupItem->name.c_str());
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 60, ptMouse.y + 15, 150, 28),
					DT_LEFT | DT_TOP,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				sprintf(test, "물리공격 +%d\n마법공격 +%d", popupItem->phydmgmin, popupItem->magdmgmin);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
					DT_LEFT,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
			}
			break;
			case item_coat:
			case item_pants:
			case item_belt:
			case item_shoulder:
			case item_shoes:
				sprintf(test, "%s", popupItem->name.c_str());
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 60, ptMouse.y + 15, 150, 28),
					DT_LEFT | DT_TOP,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "물리방어 +%d", popupItem->phydef);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
					DT_LEFT | DT_TOP,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "힘 +%d", popupItem->gainStr);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 80, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "지능 +%d", popupItem->gainInt);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 95, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "체력 +%d", popupItem->gainHealth);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 110, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "정신력 +%d", popupItem->gainSpirit);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 125, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				break;
			case item_consume:
				sprintf(test, "%s", popupItem->name.c_str());//이름
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 60, ptMouse.y + 15, 150, 28),
					DT_LEFT|DT_TOP,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				if (popupItem->gainHP > 0 && popupItem->gainMP > 0) {
					sprintf(test, "체력 +%d%c\n마나 +%d%c", popupItem->gainHP, popupItem->detail > 0 ? '%' : ' ', popupItem->gainMP, popupItem->detail > 0 ? '%' : ' ');
					d3dFont->DrawTextA(
						NULL,
						test,
						-1,
						&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
						DT_LEFT,
						D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				}
				else if (popupItem->gainHP > 0) {
					sprintf(test, "체력 +%d%c", popupItem->gainHP, popupItem->detail > 0 ? '%' : ' ');
					d3dFont->DrawTextA(
						NULL,
						test,
						-1,
						&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
						DT_LEFT,
						D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				}
				else if (popupItem->gainMP > 0) {
					sprintf(test, "마나 +%d%c", popupItem->gainMP, popupItem->detail > 0 ? '%' : ' ');
					d3dFont->DrawTextA(
						NULL,
						test,
						-1,
						&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
						DT_LEFT,
						D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				}
				break;
			}
		}

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
	SAFE_DELETE(onHold);
}
