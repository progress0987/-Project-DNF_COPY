#include "stdafx.h"
#include "NPC_Kanna.h"


HRESULT NPC_Kanna::init()
{
	idlefrom = 0;
	idleto = 7;
	actionfrom = actionto = 0;
	tick = 0;
	curStatus = npc_idle;
	frame = 0;

	isMerchant = false;
	Merchant.clear();


	Merchant.push_back(itemList.find("블루베리")->second);
	Merchant.push_back(itemList.find("라미화 잎")->second);
	Merchant.push_back(itemList.find("타코야끼")->second);
	Merchant.push_back(itemList.find("샴페인")->second);
	Merchant.push_back(itemList.find("하트쿠키")->second);
	Merchant.push_back(itemList.find("마나에이드")->second);

	x = 423;
	y = 325;
	pointRC = RectMakeCenter(x, y - 50, 50, 80);
	return S_OK;
}

void NPC_Kanna::update()
{
	tick++;
	if (tick % 30 == 0) {
		frame++;
		if (frame > idleto) {
			frame = idlefrom;
		}
	}
	POINT t = ptMouse;
	t.x += cam.x;
	t.y += cam.y;
	if (PtInRect(&pointRC, t)) {
		if (clicked) {
			pl->getUI()->setCurActiveTab(1);
			pl->getUI()->openShop(Merchant);
		}
	}
}

void NPC_Kanna::render()
{
	char tmp[50];
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, y - cam.y, 300, 50, 0.3f, 0xAA);
	sprintf(tmp, "NPC_칸나_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, y - cam.y, 100, 166);
}

void NPC_Kanna::renderdc()
{
	Rectangle(hdc, pointRC.left - cam.x, pointRC.top - cam.y, pointRC.right - cam.x, pointRC.bottom - cam.y);
}

NPC_Kanna::NPC_Kanna()
{
}


NPC_Kanna::~NPC_Kanna()
{
}
