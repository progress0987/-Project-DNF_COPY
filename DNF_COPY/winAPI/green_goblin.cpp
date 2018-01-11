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
	char tmp[50];
	sprintf(tmp, "°íºí¸°_ÃÊ·Ï_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);

	sprintf(tmp, "°íºí¸°_¹«±â_Å¬·´_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);

	if (onAbnormal) {
		switch (abnormalType) {
		case 0:
			frame = hitfrom;
			switch (abnormalStage) {
			case 0:
				sprintf(tmp, "ºù°á_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir?-15:15), (y + translate(z) -5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			case 1:
				sprintf(tmp, "ºù°á_ÇØÁ¦_%d", abnormalFrame);
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
		sprintf(tmp, "Ç÷Èç_%d", bloodframe/4);
		IMAGEMANAGER->findImage(tmp)->render(x - 50 -cam.x, (y + translate(z) - 80) -cam.y);
	}
}

void green_goblin::renderdc()
{
	Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom -cam.y);
}

green_goblin::green_goblin()
{
}


green_goblin::~green_goblin()
{
}
