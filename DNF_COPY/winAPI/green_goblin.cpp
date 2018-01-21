#include "stdafx.h"
#include "green_goblin.h"

HRESULT green_goblin::init()
{
	goblin_base::init();
	x = rand() % curMap->getWidth();
	y = 0;
	int range = WINSIZEY - 350;
	z = (rand() % range + 350) * 2;
	frame = 0;
	actionTick = 0;
	actionIndicate = rand() % 500+300;
	monHeight = 51;
	curStatus = mon_Idle;
	moveSpeedMaxX = moveSpeedMaxZ = 6.0f;
	onAbnormal = false;
	abnormalCount = abnormalFrame = abnormalStage = abnormalType = -1;
	hitXvel = hitYvel = hitZvel = 0.f;
	probeX = 500;
	probeZ = 350;
	found = onAir = onHold = false;
	printblood = bloodframe = onAbnormal = false;
	hitAvail = -1;
	stat.maxHP = stat.curHP = 500;
	stat.dmg = 30;

	return S_OK;
}

HRESULT green_goblin::init(int x, int z)
{
	green_goblin::init();
	this->x = x;
	this->z = z;
	y = 0;

	return S_OK;
}

void green_goblin::update()
{
	MonsterBase::update();
}

void green_goblin::render()
{
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.25, 0xAA);
	char tmp[50];
	sprintf(tmp, "고블린_초록_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);

	sprintf(tmp, "고블린_무기_클럽_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);

	if (onAbnormal) {
		switch (abnormalType) {
		case 0:
			frame = hitfrom;
			switch (abnormalStage) {
			case 0:
				sprintf(tmp, "빙결_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir?-15:15), (y + translate(z) -5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			case 1:
				sprintf(tmp, "빙결_해제_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir?-15:15), (y + translate(z) -5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			}
			break;
		}
	}
	if (onHold) {
		char tmp[50];
		for (vector<string>::iterator i = effectNames.begin(); i != effectNames.end(); i++) {
			sprintf(tmp, "%s%d",(*i).c_str(), effectframe1);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(x-60 - cam.x, (y + translate(z) -80) - cam.y, 0, 0);
		}
	}
	if (printblood) {
		char tmp[50];
		if (bloodframe/4 > 6) {
			bloodframe = 0;
			printblood = false;
		}
		sprintf(tmp, "혈흔_%d", bloodframe/4);
		IMAGEMANAGER->findImage(tmp)->render(x - 50 -cam.x, (y + translate(z) - 80) -cam.y);
	}
	
	MonsterBase::render();
}

void green_goblin::renderdc()
{
	char tmp[200];
	sprintf(tmp, "%d / %d", stat.curHP, stat.maxHP);

	TextOut(hdc, 500, 500, tmp, strlen(tmp));
	//Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom -cam.y);
}

green_goblin::green_goblin()
{
}


green_goblin::~green_goblin()
{
}
