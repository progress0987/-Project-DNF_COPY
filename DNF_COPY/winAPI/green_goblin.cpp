#include "stdafx.h"
#include "green_goblin.h"

HRESULT green_goblin::init()
{
	goblin_base::init();
	sprintf(stat.name,"초록 고블린");
	x = rand() % curMap->getWidth();
	y = 0;
	int range = WINSIZEY - 350;
	z = (rand() % range + 350) * 2;

	aggressive = 60;
	atkcooldown =1000;
	goldAmount = 10;
	expamount = 50;

	actionIndicate = rand() % 200+200;
	monHeight = 51;
	moveSpeedMaxX = moveSpeedMaxZ = 6.0f;
	probeX = 500;
	probeZ = 350;
	stat.maxHP = stat.curHP = 500;
	stat.dmgmin = 100;
	stat.dmgmax = 150;

	Item it = itemList.find("블루베리")->second;
	it.stack = 1;
	dropItems.push_back(it);
	it = itemList.find("라미화 잎")->second;
	it.stack = 1;
	dropItems.push_back(it);
	return S_OK;
}

HRESULT green_goblin::init(int x, int z)
{
	green_goblin::init();
	this->x = x;
	this->z = z;
	backupx = x;
	backupz = z;
	y = 0;

	return S_OK;
}

void green_goblin::reset()
{
	x = backupx;
	z = backupz;
	stat.curHP = stat.maxHP;
	curStatus = mon_Idle;
}

void green_goblin::update()
{
	MonsterBase::update();
	//공격
	if (curatkcooldown <= 0&&!onAttack) {
		if (x - 30 < curMap->getPlayer()->getX() && curMap->getPlayer()->getX() < x + 30 &&
			z - 40 < curMap->getPlayer()->getZ() && curMap->getPlayer()->getZ() < z + 40) {
			int atk = rand() % 99 + 1;
			if (atk < aggressive) {
				curStatus = mon_Attack;
				curatkcooldown = atkcooldown;
				onAttack = true;
			}
		}
	}
}

void green_goblin::render()
{
	char tmp[50];
	if (curStatus == mon_onDeadProcess) {
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.25, (0xAA - deadcount*2>0? 0xAA-deadcount*2:0));
	sprintf(tmp, "고블린_초록_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, (0xFF - deadcount * 2>0 ? 0xFF - deadcount * 2 : 0), curDir);
	}
	else {
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.25, 0xAA);
	sprintf(tmp, "고블린_초록_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);
	}
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

	for (list<HitQueue>::iterator i = hitQueue.begin(); i != hitQueue.end(); i++) {
		printNumber(*i);
	}
	MonsterBase::render();
}

void green_goblin::renderdc()
{
	//char tmp[200];
	//sprintf(tmp, "%d / %d", stat.curHP, stat.maxHP);

	//TextOut(hdc, 500, 500, tmp, strlen(tmp));
	//Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom -cam.y);
}

void green_goblin::setAttack() {

	effectedOnTime a;
	a.abnormal = -1;
	a.area.minx = x - 50;
	a.area.maxx = x + 50;
	a.area.miny = -50;
	a.area.maxy = 0;
	a.area.minz = z - 40;
	a.area.maxz = z + 40;

	a.isAbnormal = a.isHold = a.isMove = a.isProjectile = false;
	a.isOnetime = true;
	a.isCrit = rand() % 100 > 80 ? true : false;
	a.time = GetTickCount();
	a.staytime = 30;

	a.mindmg = a.isCrit ? stat.dmgmin*1.5 : stat.dmgmin;
	a.maxdmg = a.isCrit ? stat.dmgmax*1.5 : stat.dmgmax;
	a.pushX = curDir ? 5.f : -5.f;
	a.pushY = 0;
	a.pushZ = 0;
	pl->hit(a);
}
green_goblin::green_goblin()
{
}


green_goblin::~green_goblin()
{
}
