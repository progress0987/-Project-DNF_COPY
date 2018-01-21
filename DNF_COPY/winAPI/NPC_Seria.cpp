#include "stdafx.h"
#include "NPC_Seria.h"


HRESULT NPC_Seria::init()
{
	idlefrom = 0;
	idleto = 5;
	actionfrom = 0;
	actionto = 11;
	tick=0;
	curStatus = npc_idle;
	frame=0;

	isMerchant = false;
	Merchant.clear();
	pointRC = { 0,0,0,0 };
	x = 475;
	y = 320;
	return S_OK;
}

void NPC_Seria::update()
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
		if (tick % 30 == 0) {
			frame++;
			if (frame > actionto) {
				curStatus = npc_idle;
				frame = idlefrom;
			}
		}
		break;

	}
}

void NPC_Seria::render()
{
	char tmp[50];
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, y - cam.y, 300, 50,0.3f,0x55);
	sprintf(tmp, "NPC_세리아_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x -cam.x, y -cam.y, 100, 166);
}

void NPC_Seria::renderdc()
{
}

NPC_Seria::NPC_Seria()
{
}


NPC_Seria::~NPC_Seria()
{
}
