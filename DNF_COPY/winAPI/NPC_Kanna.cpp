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


	Merchant.push_back(itemList.find("��纣��")->second);
	Merchant.push_back(itemList.find("���ȭ ��")->second);
	Merchant.push_back(itemList.find("Ÿ�ھ߳�")->second);
	Merchant.push_back(itemList.find("������")->second);
	Merchant.push_back(itemList.find("��Ʈ��Ű")->second);
	Merchant.push_back(itemList.find("�������̵�")->second);

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
	IMAGEMANAGER->findImage("�׸���")->DFpointrender(x - cam.x, y - cam.y, 300, 50, 0.3f, 0xAA);
	sprintf(tmp, "NPC_ĭ��_%d", frame);
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
