#include "stdafx.h"
#include "NPC_Linus.h"


HRESULT NPC_Linus::init()
{
	idlefrom = 0;
	idleto = 3;
	actionfrom = 0;
	actionto = 11;
	tick = 0;
	curStatus = npc_idle;
	frame = 0;

	isMerchant = false;
	Merchant.clear();
	x = 1821;
	y = 325;
	pointRC = RectMakeCenter(x,y-50,50,100);
	return S_OK;
}

void NPC_Linus::update()
{
	tick++;
	switch (curStatus) {
	case npc_idle:
		if (tick % 30 == 0) {
			frame++;
			if (frame > idleto) {
				if (rand() % 100 > 70) {
					curStatus = npc_action;
					frame = actionfrom;
				}
				else {
					curStatus = npc_idle;
					frame = idlefrom;
				}
			}
		}
		break;
	case npc_action:
		if (tick % 20 == 0) {
			frame++;
			if (frame > actionto) {
				curStatus = npc_idle;
				frame = idlefrom;
			}
		}
		break;
	}
	POINT t = ptMouse;
	t.x += cam.x;
	t.y += cam.y;
	if (PtInRect(&pointRC, t)) {
		if (clicked) {
			//pl->getUI()->openShop(Merchant);
		}
	}
}

void NPC_Linus::render()
{
	char tmp[50];
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, y - cam.y, 300, 50, 0.3f, 0xAA);
	sprintf(tmp, "NPC_라이너스_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, y - cam.y, 100, 166);
}

void NPC_Linus::renderdc()
{
	Rectangle(hdc, pointRC.left - cam.x, pointRC.top - cam.y, pointRC.right - cam.x, pointRC.bottom - cam.y);
}

NPC_Linus::NPC_Linus()
{
}


NPC_Linus::~NPC_Linus()
{
}
