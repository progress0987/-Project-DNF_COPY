#include "stdafx.h"
#include "UI.h"

void drawWindow(int destX, int destY,int width, int height, int alpha)
{
		//0, 3, 6 11x, 1,4,7 - 12x, 2,5,8 - 10x

		//0,1,2 ,6,7,8 - 11y
		//3,4,5 - 13y
		FLOAT Xmul = (width - 21.f) /12.f;					//x�������� Ȯ����
		FLOAT Ymul = (height - 22.f) /13.f;					//y�������� Ȯ����

		IMAGEMANAGER->findImage("â_0")->render(destX, destY);		//������

		IMAGEMANAGER->findImage("â_1")->scaledrender(destX+11, destY, Xmul);

		IMAGEMANAGER->findImage("â_2")->render(destX + 12 * Xmul+11, destY);
		//////////////////////////////////////////
		IMAGEMANAGER->findImage("â_3")->scaledrender(destX, destY+11,1.f, Ymul);

		IMAGEMANAGER->findImage("â_4")->scaledrender(destX + 11,destY+11,Xmul,Ymul);//�����߿�

		IMAGEMANAGER->findImage("â_5")->scaledrender(destX + 12 * Xmul +11, destY+11, 1.f, Ymul);
		//////////////////////////////////////////////////////////
		IMAGEMANAGER->findImage("â_6")->render(destX , destY+ 13 * Ymul + 11);

		IMAGEMANAGER->findImage("â_7")->scaledrender(destX + 11,destY + 13*Ymul+11,Xmul);

		IMAGEMANAGER->findImage("â_8")->render(destX + 12 * Xmul+11 , destY+ 13 * Ymul + 11);
}

HRESULT UI::init(void)
{
	showInv = showStat = showPopup = showShop = false;
	popupItem = &pl->empty;
	inv = RectMake(WINSIZEX - 300, 50, 270, 400);
	stat = RectMake(inv.left - 270, 50, 260, 400);
	shop = RectMake(inv.left - 370, 50, 360, 430);
	shopClose = RectMake(shop.right - 25, shop.top + 10, 15, 15);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			shopItemRC[i * 2 + j] = RectMake(shop.left + 10 + 175 * j, shop.top + 40 + i * 60, 165, 57);
		}
	}

	q1 = RectMake(100, 518 + 42, 30, 30);
	q2 = RectMake(130, 518 + 42, 30, 30);
	q3 = RectMake(160, 518 + 42, 30, 30);
	q4 = RectMake(190, 518 + 42, 30, 30);
	q5 = RectMake(220, 518 + 42, 30, 30);
	q6 = RectMake(250, 518 + 42, 30, 30);
	int fromx = 0;
	qa = RectMake(540+fromx++*30+1, 561, 28, 28);
	qs = RectMake(540+fromx++*30+1, 561, 28, 28);
	qd = RectMake(540+fromx++*30+1, 561, 28, 28);
	qf = RectMake(540+fromx++*30+1, 561, 28, 28);
	qg = RectMake(540+fromx++*30+1, 561, 28, 28);
	qh = RectMake(540+fromx*30+1, 561, 28, 28);
	fromx = 0;
	qq = RectMake(540+fromx++*30+1, 531, 28, 28);
	qw = RectMake(540+fromx++*30+1, 531, 28, 28);
	qe = RectMake(540+fromx++*30+1, 531, 28, 28);
	qr = RectMake(540+fromx++*30+1, 531, 28, 28);
	qt = RectMake(540+fromx++*30+1, 531, 28, 28);
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
		TEXT("����"),
		&d3dFont))) {
		return E_FAIL;
	}

	/*D3DXFONT_DESC desc;
	desc.CharSet = HANGUL_CHARSET;
	strcpy(desc.FaceName, "����");
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
	if(onHoldPosX==-1||onHoldPosY==-1)
	popupItem = &pl->empty;

	///////////�����Կ��� ��Ŭ��
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
				if (PtInRect(&itemrects[j][i], ptMouse)) {//������ �˾�
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
						if (!showShop) {
							pl->useItem(curActiveTab, j, i);
							rclicked = false;
							showPopup = false;
							popupItem = &pl->empty;
						}
						else if (showShop) {
							showPopup = false;
							rclicked = false;
							pl->sellItem(curActiveTab, j + i * 8);
						}
					}
					if (clicked) {//������ Ŭ��
						switch (curActiveTab) {
						case 0:
							if (pl->equipments[j + i * 8].id > 0) {
								onHold = &pl->equipments[j + i * 8];
								onHoldPosX = j;
								onHoldPosY = i;
								clicked = false;
							}
							break;
						case 1:
							if (pl->consume[j + i * 8].id > 0) {
								onHold = &pl->consume[j + i * 8];
								onHoldPosX = j;
								onHoldPosY = i;
								clicked = false;
							}
							break;
						}
					}
				}
			}
		}

		if (!lstay) {										//���콺��������
			if (onHold->id > 0) {													//����ִ°� �������ϰ��
																					//���콺�� ���� ������ ���Ƶ� �Ǵ°��� �ƴѰ��
				if (!(PtInRect(&inv, ptMouse) || PtInRect(&q1, ptMouse) || PtInRect(&q2, ptMouse) || PtInRect(&q3, ptMouse) || PtInRect(&q4, ptMouse) || PtInRect(&q5, ptMouse) || PtInRect(&q6, ptMouse))) {
				
					if (pl->getCurMap()->isPeaceful()) {
						onHold = &pl->empty;
					}
					else {															//�����۵��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						DropItemStruct t;
						//Item* tmp = new Item;
						//memcpy(tmp,&pl->equipments[onHoldPosX + onHoldPosY * 8],sizeof(Item));
						//t.item = tmp;
						t.item = onHold->type == item_consume?pl->consume[onHoldPosX+onHoldPosY*8]:onHold->type == item_etc?Item(): pl->equipments[onHoldPosX + onHoldPosY * 8];
						t.xVel = t.yVel = t.zVel = t.Tick = t.isGold = t.goldamount = 0;
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
	if (showShop) {
		showInv = true;
		if (PtInRect(&shopClose, ptMouse)) {
			if (clicked) {
				showShop = false;
			}
		}
		for (int i = 0; i < 12; i++) {
			if (PtInRect(&shopItemRC[i], ptMouse)&&i<merch.size()) {
				showPopup = true;
				popupItem = &merch[i];
				if (rclicked) {
					if (merch[i].price <= pl->gold) {
						pl->rootItem(merch[i]);
						pl->gold -= merch[i].price;
						rclicked = false;
					}
				}
			}
		}
	}
	if (pl->getCurMap()->showresult) {
		if (PtInRect(&RectMake(WINSIZEX - 300 + 67, 167, 165, 23), ptMouse)&&clicked) {
			pl->reset = true;
			playBGM("BGM_����");
		}
	}
}

void UI::render(void)
{
	char tmp[50];
	int invcount=0;
	int UI_top = WINSIZEY - IMAGEMANAGER->findImage("UI_�ϴ�_�⺻â")->getHeight();
	IMAGEMANAGER->findImage("UI_�ϴ�_�⺻â_����")->DFuirender(0, WINSIZEY- IMAGEMANAGER->findImage("UI_�ϴ�_�⺻â_����")->getHeight());
	IMAGEMANAGER->findImage("UI_�ϴ�_�⺻â")->DFuirender(0, UI_top);
	IMAGEMANAGER->findImage("UI_�ϴ�_�⺻â_Ȯ��")->DFuirender(508, UI_top);
	float t_width = (((float)pl->getStatus().curEXP / (float)pl->getStatus().reqEXP) + 0.000000001f)*IMAGEMANAGER->findImage("UI_�ϴ�_����ġ")->getWidth();
	IMAGEMANAGER->findImage("UI_�ϴ�_����ġ")->render(102,WINSIZEY - 6,0,0, t_width,3);

	IMAGEMANAGER->findImage("UI_HP")->render(35, UI_top+9 + (IMAGEMANAGER->findImage("UI_HP")->getHeight() *(1-(float)pl->Stat.curHP / (float)pl->Stat.maxHP)),0,IMAGEMANAGER->findImage("UI_HP")->getHeight() * (1.f-((float)pl->Stat.curHP/(float)pl->Stat.maxHP)),0, IMAGEMANAGER->findImage("UI_HP")->getHeight() * (float)pl->Stat.curHP/(float)pl->Stat.maxHP);
	IMAGEMANAGER->findImage("UI_MP")->render(730, UI_top+9 + (IMAGEMANAGER->findImage("UI_MP")->getHeight() *(1 - (float)pl->Stat.curMP / (float)pl->Stat.maxMP)), 0, IMAGEMANAGER->findImage("UI_MP")->getHeight() * (1.f - ((float)pl->Stat.curMP / (float)pl->Stat.maxMP)), 0, IMAGEMANAGER->findImage("UI_MP")->getHeight() * (float)pl->Stat.curMP / (float)pl->Stat.maxMP);
	if (pl->getQuick1().id > 0) {
		sprintf(tmp, "�Ҹ�_%d", pl->getQuick1().id);
		IMAGEMANAGER->findImage(tmp)->render(q1.left+1,q1.top+1);
	}
	if (pl->getQuick2().id > 0) {
		sprintf(tmp, "�Ҹ�_%d", pl->getQuick2().id);
		IMAGEMANAGER->findImage(tmp)->render(q2.left + 1, q2.top + 1);
	}
	if (pl->getQuick3().id > 0) {
		sprintf(tmp, "�Ҹ�_%d", pl->getQuick3().id);
		IMAGEMANAGER->findImage(tmp)->render(q3.left + 1, q3.top + 1);
	}
	if (pl->getQuick4().id > 0) {
		sprintf(tmp, "�Ҹ�_%d", pl->getQuick4().id);
		IMAGEMANAGER->findImage(tmp)->render(q4.left + 1, q4.top + 1);
	}
	if (pl->getQuick5().id > 0) {
		sprintf(tmp, "�Ҹ�_%d", pl->getQuick5().id);
		IMAGEMANAGER->findImage(tmp)->render(q5.left + 1, q5.top + 1);
	}
	if (pl->getQuick6().id > 0) {
		sprintf(tmp, "�Ҹ�_%d", pl->getQuick6().id);
		IMAGEMANAGER->findImage(tmp)->render(q6.left + 1, q6.top + 1);
	}
	if (pl->getASkill() != nullptr) {
		sprintf(tmp, "��ų_������_%d", pl->getASkill()->skillInactive);
		IMAGEMANAGER->findImage(tmp)->render(qa.left, qa.top);
		if (pl->getStatus().curMP > pl->getASkill()->reqMana) {
			sprintf(tmp, "��ų_������_%d", pl->getASkill()->skillActive);
			IMAGEMANAGER->findImage(tmp)->render(qa.left, qa.top, 0, 0, 28, 28 - (28 * pl->getASkill()->getremainCooldown()));
		}
	}
	if (pl->getSSkill() != nullptr) {
		sprintf(tmp, "��ų_������_%d", pl->getSSkill()->skillInactive);
		IMAGEMANAGER->findImage(tmp)->render(qs.left, qs.top);
		if (pl->getStatus().curMP > pl->getSSkill()->reqMana) {
			sprintf(tmp, "��ų_������_%d", pl->getSSkill()->skillActive);
			IMAGEMANAGER->findImage(tmp)->render(qs.left, qs.top, 0, 0, 28, 28 - (28 * pl->getSSkill()->getremainCooldown()));
		}
	}
	if (pl->getDSkill() != nullptr) {
		sprintf(tmp, "��ų_������_%d", pl->getDSkill()->skillInactive);
		IMAGEMANAGER->findImage(tmp)->render(qd.left, qd.top);
		if (pl->getStatus().curMP > pl->getDSkill()->reqMana) {
			sprintf(tmp, "��ų_������_%d", pl->getDSkill()->skillActive);
			IMAGEMANAGER->findImage(tmp)->render(qd.left, qd.top, 0, 0, 28, 28 - (28 * pl->getDSkill()->getremainCooldown()));
		}
	}
	if (pl->getFSkill() != nullptr) {
		sprintf(tmp, "��ų_������_%d", pl->getFSkill()->skillInactive);
		IMAGEMANAGER->findImage(tmp)->render(qf.left, qf.top);
		if (pl->getStatus().curMP > pl->getFSkill()->reqMana) {
			sprintf(tmp, "��ų_������_%d", pl->getFSkill()->skillActive);
			IMAGEMANAGER->findImage(tmp)->render(qf.left, qf.top, 0, 0, 28, 28 - (28 * pl->getFSkill()->getremainCooldown()));
		}
	}
	if (pl->getGSkill() != nullptr) {
		sprintf(tmp, "��ų_������_%d", pl->getGSkill()->skillInactive);
		IMAGEMANAGER->findImage(tmp)->render(qg.left, qg.top);
		if (pl->getStatus().curMP > pl->getGSkill()->reqMana) {
			sprintf(tmp, "��ų_������_%d", pl->getGSkill()->skillActive);
			IMAGEMANAGER->findImage(tmp)->render(qg.left, qg.top, 0, 0, 28, 28 - (28 * pl->getGSkill()->getremainCooldown()));
		}
	}
	if (pl->getQSkill() != nullptr) {
		sprintf(tmp, "��ų_������_%d", pl->getQSkill()->skillInactive);
		IMAGEMANAGER->findImage(tmp)->render(qq.left, qq.top);
		if (pl->getStatus().curMP > pl->getQSkill()->reqMana) {
			sprintf(tmp, "��ų_������_%d", pl->getQSkill()->skillActive);
			IMAGEMANAGER->findImage(tmp)->render(qq.left, qq.top, 0, 0, 28, 28 - (28 * pl->getQSkill()->getremainCooldown()));
		}
	}



	if (showInv) {
		char tmp[50];
		drawWindow(inv.left, inv.top, inv.right - inv.left, inv.bottom - inv.top);
		IMAGEMANAGER->findImage("UI_�κ��丮_�⺻â")->DFuirender(inv.left+12,inv.top +25);
		IMAGEMANAGER->findImage("UI_�κ��丮_����̽�")->DFuirender(inv.left + 12+3,inv.top+25+5);
		IMAGEMANAGER->findImage("UI_�κ��丮_�ϴ�")->DFuirender(inv.left + 12, inv.bottom - IMAGEMANAGER->findImage("UI_�κ��丮_�ϴ�")->getHeight() - 25);
		
		sprintf(tmp, "%s_��_176", pl->getWeapon().name.c_str());
		if (pl->getWeapon().id == -1) {
			sprintf(tmp, "��յ�_176");
		}
		IMAGEMANAGER->findImage(tmp)->render(inv.left + 12 + 3 +93 - 200, inv.top + 25 + 5 + 21 - 223,0,0,264,308);

		sprintf(tmp, "ĳ����_176");
		IMAGEMANAGER->findImage(tmp)->render(inv.left + 12 + 3 + 93 - 200, inv.top + 25 + 5 + 21 - 223, 0, 0, 264, 308);

		sprintf(tmp, "%s_��_176", pl->getWeapon().name.c_str());
		if (pl->getWeapon().id == -1) {
			sprintf(tmp, "��վ�_176");
		}
		IMAGEMANAGER->findImage(tmp)->render(inv.left + 12 + 3 + 93 - 200, inv.top + 25 + 5 + 21 - 223, 0, 0, 264, 308);



		if (pl->getArmor().id != -1) {
			switch (pl->getArmor().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_����_%d", pl->getArmor().id);
				IMAGEMANAGER->findImage(tmp)->render(Armor.left, Armor.top);
				break;
			}
		}

		if (pl->getPants().id != -1) {
			switch (pl->getPants().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_����_%d", pl->getPants().id);
				IMAGEMANAGER->findImage(tmp)->render(Pants.left, Pants.top);
				break;
			}
		}

		if (pl->getShoulder().id != -1) {
			switch (pl->getShoulder().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_���_%d", pl->getShoulder().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoulder.left, Shoulder.top);
				break;
			}
		}

		if (pl->getBelt().id != -1) {
			switch (pl->getBelt().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_��Ʈ_%d", pl->getBelt().id);
				IMAGEMANAGER->findImage(tmp)->render(Belt.left, Belt.top);
				break;
			}
		}

		if (pl->getShoes().id != -1) {
			switch (pl->getShoes().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_�Ź�_%d", pl->getShoes().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoes.left, Shoes.top);
				break;
			}
		}

		if (pl->getWeapon().id != -1) {
			switch (pl->getWeapon().detail) {
			case wp_sswd:
				sprintf(tmp, "�Ұ�_%d", pl->getWeapon().id);
				IMAGEMANAGER->findImage(tmp)->render(Weapon.left,Weapon.top);
				break;
			case wp_kat:
				break;
			}
		}

		if (curActiveTab == 0) {
			IMAGEMANAGER->findImage("UI_�κ��丮_Ȱ����")->render(tabEquip.left, tabEquip.top);
		}
		else {
			IMAGEMANAGER->findImage("UI_�κ��丮_��Ȱ����")->render(tabEquip.left+1, tabEquip.top+1);
		}

		if (curActiveTab == 1) {
			IMAGEMANAGER->findImage("UI_�κ��丮_Ȱ����")->render(tabConsume.left, tabConsume.top);
		}
		else {
			IMAGEMANAGER->findImage("UI_�κ��丮_��Ȱ����")->render(tabConsume.left+1, tabConsume.top+1);
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				IMAGEMANAGER->findImage("UI_�κ��丮_������_����")->DFuirender(itemrects[j][i].left-1,itemrects[j][i].top-1);
			}
		}
		switch (curActiveTab) {
		case 0:								//���
			for (vector<Item>::iterator i =pl->equipments.begin(); i !=pl->equipments.end(); i++) {
				if (onHold->id > 0 && i == (pl->equipments.begin() + onHoldPosX + onHoldPosY * 8)) {
					invcount++;
					switch (i->type) {
					case item_weapon:
						if (!i->equipped) {
							switch (i->detail) {
							case wp_sswd:
								sprintf(tmp, "�Ұ�_%d", i->id);
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
								sprintf(tmp, "�Ǳ�_����_%d", i->id);
								break;
							}
						}
						break;
					case item_shoulder:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "�Ǳ�_���_%d", i->id);
								break;
							}
						}
						break;
					case item_belt:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "�Ǳ�_��Ʈ_%d", i->id);
								break;
							}
						}
						break;
					case item_pants:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "�Ǳ�_����_%d", i->id);
								break;
							}
						}
						break;
					case item_shoes:
						if (!i->equipped) {
							switch (i->detail) {
							case arm_plate:
								sprintf(tmp, "�Ǳ�_�Ź�_%d", i->id);
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
							sprintf(tmp, "�Ұ�_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left+1, itemrects[invcount % 8][invcount / 8].top+1);
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
							sprintf(tmp, "�Ǳ�_����_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left + 1, itemrects[invcount % 8][invcount / 8].top + 1);
							break;
						}
					}
					break;
				case item_shoulder:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "�Ǳ�_���_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left + 1, itemrects[invcount % 8][invcount / 8].top + 1);
							break;
						}
					}
					break;
				case item_belt:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "�Ǳ�_��Ʈ_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left + 1, itemrects[invcount % 8][invcount / 8].top + 1);
							break;
						}
					}
					break;
				case item_pants:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "�Ǳ�_����_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left + 1, itemrects[invcount % 8][invcount / 8].top + 1);
							break;
						}
					}
					break;
				case item_shoes:
					if (!i->equipped) {
						switch (i->detail) {
						case arm_plate:
							sprintf(tmp, "�Ǳ�_�Ź�_%d", i->id);
							IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left + 1, itemrects[invcount % 8][invcount / 8].top + 1);
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
		case 1:								//�Ҹ�ǰ
			for (vector<Item>::iterator i = pl->consume.begin(); i != pl->consume.end(); i++) {
				if (i->id > 0) {
					if (onHold->id>0&&i == (pl->consume.begin() + onHoldPosX + onHoldPosY * 8)) {
						sprintf(tmp, "�Ҹ�_%d", i->id);
						IMAGEMANAGER->findImage(tmp)->render(ptMouse.x,ptMouse.y);
						invcount++;
					}
					else {
						sprintf(tmp, "�Ҹ�_%d", i->id);
						IMAGEMANAGER->findImage(tmp)->render(itemrects[invcount % 8][invcount / 8].left + 1, itemrects[invcount % 8][invcount / 8].top + 1);
						invcount++;
					}
				}
				else {
					invcount++;
				}
			}
			break;
		case 2:								//��Ÿ��
			break;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				if (PtInRect(&itemrects[j][i], ptMouse) && (curActiveTab == 0 ? pl->equipments[j + i * 8].id > 0:(curActiveTab == 1 ? pl->consume[j + i * 8].id > 0:false)))
					IMAGEMANAGER->findImage("UI_�����ۼ���")->render(itemrects[j][i].left, itemrects[j][i].top);
			}
		}
	}
	if (showStat) {
		drawWindow(stat.left, stat.top, stat.right - stat.left, stat.bottom - stat.top);
		IMAGEMANAGER->findImage("UI_����_�⺻")->render(stat.left+8+6, stat.top+28+25);
		IMAGEMANAGER->findImage("UI_�κ��丮_�⺻â")->render(stat.left+6, stat.top+25,0,0,246,112);
		IMAGEMANAGER->findImage("UI_�κ��丮_����̽�")->render(stat.left  + 8, stat.top + 26);
		if (pl->getArmor().id != -1) {
			switch (pl->getArmor().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_����_%d", pl->getArmor().id);
				IMAGEMANAGER->findImage(tmp)->render(Armor.left-278, Armor.top-3);
				break;
			}
		}
		if (pl->getPants().id != -1) {
			switch (pl->getPants().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_����_%d", pl->getPants().id);
				IMAGEMANAGER->findImage(tmp)->render(Pants.left-278, Pants.top-3);
				break;
			}
		}
		if (pl->getShoulder().id != -1) {
			switch (pl->getShoulder().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_���_%d", pl->getShoulder().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoulder.left - 278, Shoulder.top - 3);
				break;
			}
		}
		if (pl->getBelt().id != -1) {
			switch (pl->getBelt().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_��Ʈ_%d", pl->getBelt().id);
				IMAGEMANAGER->findImage(tmp)->render(Belt.left - 278, Belt.top - 3);
				break;
			}
		}
		if (pl->getShoes().id != -1) {
			switch (pl->getShoes().detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_�Ź�_%d", pl->getShoes().id);
				IMAGEMANAGER->findImage(tmp)->render(Shoes.left - 278, Shoes.top - 3);
				break;
			}
		}
		if (pl->getWeapon().id != -1) {
			switch (pl->getWeapon().detail) {
			case wp_sswd:
				sprintf(tmp, "�Ұ�_%d", pl->getWeapon().id);
				IMAGEMANAGER->findImage(tmp)->render(Weapon.left - 278, Weapon.top - 3);
				break;
			case wp_kat:
				break;
			}
		}
	}
	if (showShop) {
		drawWindow(shop.left, shop.top, shop.right - shop.left, shop.bottom - shop.top);
		if (PtInRect(&shopClose, ptMouse)) {
			if (clicked) {
			IMAGEMANAGER->findImage("UI_�ݱ�_Ŭ��")->render(shopClose.left,shopClose.top);
			}
			else {
			IMAGEMANAGER->findImage("UI_�ݱ�_����")->render(shopClose.left,shopClose.top);
			}
		}
		else {
			IMAGEMANAGER->findImage("UI_�ݱ�_�⺻")->render(shopClose.left,shopClose.top);
		}
		for (int i = 0; i < 12; i++) {
			IMAGEMANAGER->findImage("UI_����_����")->render(shopItemRC[i].left, shopItemRC[i].top);
			if (i < merch.size()) {
				char tmp[50];
				switch (merch[i].type) {
				case item_consume:
					sprintf(tmp, "�Ҹ�_%d", merch[i].id);
					break;
				case item_weapon:
					switch (merch[i].detail) {
					case wp_sswd:
						sprintf(tmp, "�Ұ�_%d", merch[i].id);
						break;
					case wp_kat:
						break;
					}
					break;
				case item_coat:
					switch (merch[i].detail) {
					case arm_plate:
						sprintf(tmp, "�Ǳ�_����_%d", merch[i].id);
						break;
					}
					break;
				case item_shoulder:

					switch (merch[i].detail) {
					case arm_plate:
						sprintf(tmp, "�Ǳ�_���_%d", merch[i].id);
						break;
					}

					break;
				case item_belt:
					switch (merch[i].detail) {
					case arm_plate:
						sprintf(tmp, "�Ǳ�_��Ʈ_%d", merch[i].id);
						break;
					}
					break;
				case item_pants:
					switch (merch[i].detail) {
					case arm_plate:
						sprintf(tmp, "�Ǳ�_����_%d", merch[i].id);
						break;
					}
					break;
				case item_shoes:
					switch (merch[i].detail) {
					case arm_plate:
						sprintf(tmp, "�Ǳ�_�Ź�_%d", merch[i].id);
						break;
					}
					break;
				default:
					break;
				}
				IMAGEMANAGER->findImage(tmp)->render(shopItemRC[i].left + 5, shopItemRC[i].top + 6);
			}
		}
	}
	if (showPopup) {//�˾� �����ִ°Ÿ�
		drawWindow(ptMouse.x, ptMouse.y, 200, 200);
		switch (popupItem->type) {
		case item_weapon:
			switch (popupItem->detail) {
			case wp_sswd:
				sprintf(tmp, "�Ұ�_%d", popupItem->id);
				break;
			case wp_kat:
				break;
			}
			break;
		case item_coat:
			switch (popupItem->detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_����_%d", popupItem->id);
				break;
			}
			break;
		case item_shoulder:

			switch (popupItem->detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_���_%d", popupItem->id);
				break;
			}

			break;
		case item_belt:
			switch (popupItem->detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_��Ʈ_%d", popupItem->id);
				break;
			}
			break;
		case item_pants:
			switch (popupItem->detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_����_%d", popupItem->id);
				break;
			}
			break;
		case item_shoes:
			switch (popupItem->detail) {
			case arm_plate:
				sprintf(tmp, "�Ǳ�_�Ź�_%d", popupItem->id);
				break;
			}
			break;
		case item_consume:
			sprintf(tmp, "�Ҹ�_%d", popupItem->id);
		}
		IMAGEMANAGER->findImage(tmp)->render(ptMouse.x + 15, ptMouse.y + 15);
	}

	IMAGEMANAGER->findImage("Ű����_����_1")->render(q1.left+1, q1.top+1);
	IMAGEMANAGER->findImage("Ű����_����_2")->render(q2.left+1, q2.top+1);
	IMAGEMANAGER->findImage("Ű����_����_3")->render(q3.left+1, q3.top+1);
	IMAGEMANAGER->findImage("Ű����_����_4")->render(q4.left+1, q4.top+1);
	IMAGEMANAGER->findImage("Ű����_����_5")->render(q5.left+1, q5.top+1);
	IMAGEMANAGER->findImage("Ű����_����_6")->render(q6.left+1, q6.top+1);

	IMAGEMANAGER->findImage("Ű����_����_A")->render(qa.left, qa.top);
	IMAGEMANAGER->findImage("Ű����_����_S")->render(qs.left, qs.top);
	IMAGEMANAGER->findImage("Ű����_����_D")->render(qd.left, qd.top);
	IMAGEMANAGER->findImage("Ű����_����_F")->render(qf.left, qf.top);
	IMAGEMANAGER->findImage("Ű����_����_G")->render(qg.left, qg.top);
	IMAGEMANAGER->findImage("Ű����_����_H")->render(qh.left, qh.top);
	IMAGEMANAGER->findImage("Ű����_����_Q")->render(qq.left, qq.top);
	IMAGEMANAGER->findImage("Ű����_����_W")->render(qw.left, qw.top);
	IMAGEMANAGER->findImage("Ű����_����_E")->render(qe.left, qe.top);
	IMAGEMANAGER->findImage("Ű����_����_R")->render(qr.left, qr.top);
	IMAGEMANAGER->findImage("Ű����_����_T")->render(qt.left, qt.top);

	if (pl->getCurMap()->showresult) {//������������
		int rl = WINSIZEX - 300;
		IMAGEMANAGER->findImage("���������_���")->render(rl, 0);
		IMAGEMANAGER->findImage("���������")->render(rl + 13, 53);
		IMAGEMANAGER->findImage("�絵��_��Ȱ")->render(rl + 21, 107);
		IMAGEMANAGER->findImage("�ٸ�����_��Ȱ")->render(rl + 21, 137);
		IMAGEMANAGER->findImage("������_��Ȱ")->render(rl + 21, 167);
		if (PtInRect(&RectMake(rl + 67, 107, 165, 23), ptMouse)) {
			IMAGEMANAGER->findImage("�絵��_����_���")->render(rl + 16, 71);
			if (clicked) {
				IMAGEMANAGER->findImage("�絵��_Ŭ��")->render(rl + 21, 107);
			}
			else {
				IMAGEMANAGER->findImage("�絵��_����")->render(rl + 21, 107);
			}
		}
		if (PtInRect(&RectMake(rl + 67, 137, 165, 23), ptMouse)) {
			IMAGEMANAGER->findImage("�ٸ�����_����_���")->render(rl + 16, 101);
			if (clicked) {
				IMAGEMANAGER->findImage("�ٸ�����_Ŭ��")->render(rl + 21, 137);
			}
			else {
				IMAGEMANAGER->findImage("�ٸ�����_����")->render(rl + 21, 137);
			}
		}
		if (PtInRect(&RectMake(rl + 67, 167, 165, 23), ptMouse)) {
			IMAGEMANAGER->findImage("������_����_���")->render(rl + 16, 131);
			if (clicked) {
				IMAGEMANAGER->findImage("������_Ŭ��")->render(rl + 21, 167);
			}
			else {
				IMAGEMANAGER->findImage("������_����")->render(rl + 21, 167);
			}
		}
	}
}

void UI::renderdc(void)
{
	char test[200];

	//Rectangle(hdc, qa.left, qa.top, qa.right, qa.bottom);
	//Rectangle(hdc, qq.left, qq.top, qq.right, qq.bottom);

	if (!showStat&&!showShop) {
		sprintf(test, "lv %d %s", pl->getStatus().level, "�׽�Ʈ");
		d3dFont->DrawTextA(
			NULL,
			test,
			-1,
			&RectMakeCenter(pl->getX() - cam.x, pl->getY() + translate(pl->getZ()) - 120 - cam.y, strlen(test) * 10, 10),
			DT_CENTER | DT_VCENTER,
			D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	int UI_top = WINSIZEY - IMAGEMANAGER->findImage("UI_�ϴ�_�⺻â")->getHeight();
	sprintf(test, "%d / %d",pl->getStatus().curEXP,pl->getStatus().reqEXP);
	d3dFont->DrawTextA(
		NULL,
		test,
		-1,
		&RectMakeCenter(WINSIZEX / 2, WINSIZEY - 10, strlen(test)*10, 10),
		DT_CENTER | DT_VCENTER,
		D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

	int amount = ((float)pl->getStatus().curHP / (float)pl->getStatus().maxHP) * 100;
	sprintf(test, "%d%%", amount);
	d3dFont->DrawTextA(
		NULL,
		test,
		-1,
		&RectMake(40, UI_top + 17, 45, 44),
		DT_CENTER|DT_VCENTER,
		D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
	amount = ((float)pl->getStatus().curMP / (float)pl->getStatus().maxMP) * 100;
	sprintf(test, "%d%%", amount);
	d3dFont->DrawTextA(
		NULL,
		test,
		-1,
		&RectMake(736,UI_top + 17,45,44),
		DT_CENTER|DT_VCENTER,
		D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));


	if (showInv) {

#pragma region �� ��ºκ�
		//�� ��ºκ�
		{
			sprintf(test, "%d", pl->gold);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(inv.left + 12 + 25, inv.bottom - IMAGEMANAGER->findImage("UI_�κ��丮_�ϴ�")->getHeight() - 24, 77, 21),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}
#pragma endregion
		//���
		{
			sprintf(test, "���");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&tabEquip,
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}
		//�Ҹ�ǰ
		{
			sprintf(test, "�Ҹ�ǰ");
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&tabConsume,
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}

		if (showPopup) {//�˾����(������ �̸����
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
				sprintf(test, "�������� +%d\n�������� +%d", popupItem->phydmgmin, popupItem->magdmgmin);
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

				sprintf(test, "������� +%d", popupItem->phydef);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
					DT_LEFT | DT_TOP,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "�� +%d", popupItem->gainStr);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 80, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "���� +%d", popupItem->gainInt);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 95, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "ü�� +%d", popupItem->gainHealth);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 110, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));

				sprintf(test, "���ŷ� +%d", popupItem->gainSpirit);
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 10, ptMouse.y + 125, 110, 15),
					DT_LEFT | DT_VCENTER,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				break;
			case item_consume:
				sprintf(test, "%s", popupItem->name.c_str());//�̸�
				d3dFont->DrawTextA(
					NULL,
					test,
					-1,
					&RectMake(ptMouse.x + 60, ptMouse.y + 15, 150, 28),
					DT_LEFT|DT_TOP,
					D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				if (popupItem->gainHP > 0 && popupItem->gainMP > 0) {
					sprintf(test, "ü�� +%d%c\n���� +%d%c", popupItem->gainHP, popupItem->detail > 0 ? '%' : ' ', popupItem->gainMP, popupItem->detail > 0 ? '%' : ' ');
					d3dFont->DrawTextA(
						NULL,
						test,
						-1,
						&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
						DT_LEFT,
						D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				}
				else if (popupItem->gainHP > 0) {
					sprintf(test, "ü�� +%d%c", popupItem->gainHP, popupItem->detail > 0 ? '%' : ' ');
					d3dFont->DrawTextA(
						NULL,
						test,
						-1,
						&RectMake(ptMouse.x + 10, ptMouse.y + 50, 110, 25),
						DT_LEFT,
						D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
				}
				else if (popupItem->gainMP > 0) {
					sprintf(test, "���� +%d%c", popupItem->gainMP, popupItem->detail > 0 ? '%' : ' ');
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

			sprintf(test, "%d ���", popupItem->price);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&RectMake(ptMouse.x, ptMouse.y+175, 190, 20),
				DT_RIGHT | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}
		if (curActiveTab == 1) {//�Ҹ�ǰ�϶�
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 8; j++) {
					if (pl->consume[j + i * 8].id > 0) {		//�������� ������ �������
						if (pl->consume[j + i * 8].stack > 1) {	//2���̻� ���
							sprintf(test, "%d", pl->consume[j + i*8].stack);
							d3dFont->DrawTextA(
								NULL,
								test,
								-1,
								&itemrects[j][i],
								DT_RIGHT | DT_BOTTOM,
								D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
						}
					}
				}
			}
		}

	}
	if (showStat) {
		//29,118,48,15


		/*
		118-137
		19 - Y������ �Ÿ�

		29 - 143

		114 - X������ �Ÿ�
		*/
		int t = 0;
		//HP��ºκ�
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
		//MP��ºκ�
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

		//��
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
		//����
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

		//ü��
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
		//���ŷ�
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

		//�������ݷ�
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
		//�������
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

		//�������ݷ�
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
		//�������
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
	if (showShop) {
		//for (int i = 0; i < 12; i++) {
		//	Rectangle(hdc, shopItemRC[i].left, shopItemRC[i].top, shopItemRC[i].right, shopItemRC[i].bottom);
		//}
	}

	if (pl->getQuick1().id > 0) {
		if (pl->getQuick1().stack > 1) {	//2���̻� ���
			sprintf(test, "%d", pl->getQuick1().stack);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&q1,
				DT_RIGHT | DT_TOP,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		}
	}
	if (pl->getQuick2().id > 0) {
		if (pl->getQuick2().stack > 1) {	//2���̻� ���
			sprintf(test, "%d", pl->getQuick2().stack);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&q2,
				DT_RIGHT | DT_TOP,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		}
	}
	if (pl->getQuick3().id > 0) {
		if (pl->getQuick3().stack > 1) {	//2���̻� ���
			sprintf(test, "%d", pl->getQuick3().stack);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&q3,
				DT_RIGHT | DT_TOP,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		}
	}
	if (pl->getQuick4().id > 0) {
		if (pl->getQuick4().stack > 1) {	//2���̻� ���
			sprintf(test, "%d", pl->getQuick4().stack);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&q4,
				DT_RIGHT | DT_TOP,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		}
	}
	if (pl->getQuick5().id > 0) {
		if (pl->getQuick5().stack > 1) {	//2���̻� ���
			sprintf(test, "%d", pl->getQuick5().stack);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&q5,
				DT_RIGHT | DT_TOP,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		}
	}
	if (pl->getQuick6().id > 0) {
		if (pl->getQuick6().stack > 1) {	//2���̻� ���
			sprintf(test, "%d", pl->getQuick6().stack);
			d3dFont->DrawTextA(
				NULL,
				test,
				-1,
				&q6,
				DT_RIGHT | DT_TOP,
				D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		}
	}
}

void UI::openShop(vector<Item> merchandices)
{
	showShop = true;
	merch = merchandices;
}

UI::UI()
{
}


UI::~UI()
{
	SAFE_DELETE(onHold);
}