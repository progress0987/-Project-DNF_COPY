#include "stdafx.h"
#include "Tauamy.h"


HRESULT Tau::init()
{
	Tau_Base::init();
	sprintf(stat.name, "타우 아미");

	aggressive = 80;
	atkcooldown = 1000;
	goldAmount = 150;
	expamount = 70;

	actionIndicate = rand() % 200 + 200;
	monHeight = 70;
	moveSpeedMaxX = moveSpeedMaxZ = 6.0f;
	abnormalCount = abnormalFrame = abnormalStage = abnormalType = -1;
	probeX = 500;
	probeZ = 350;
	stat.maxHP = stat.curHP = 1500;
	stat.dmgmin = 150;
	stat.dmgmax = 200;

	//드랍아이템 설정

	dropItems.clear();
	Item it = itemList.find("블루베리")->second;
	it.stack = 1;
	dropItems.push_back(it);
	it = itemList.find("라미화 잎")->second;
	it.stack = 1;
	dropItems.push_back(it);
	it = itemList.find("디아볼리카")->second;
	dropItems.push_back(it);
	return S_OK;
}

HRESULT Tau::init(int x, int z)
{
	Tau::init();
	this->x = x;
	this->z = z;
	backupx = x;
	backupz = z;
	y = 0;
	return S_OK;
}

void Tau::update()
{
	MonsterBase::update();
	//공격
	if (curatkcooldown <= 0 && !onAttack&&!onSkill) {
		if (x - 200 < curMap->getPlayer()->getX() && curMap->getPlayer()->getX() < x + 200 &&
			z - 100 < curMap->getPlayer()->getZ() && curMap->getPlayer()->getZ() < z + 100) {
			int atk = rand() % 99 + 1;
			if (atk < aggressive) {
				//curStatus = mon_Attack;
				//curatkcooldown = atkcooldown;
				//onAttack = true;

				onSkill = true;
				curStatus = mon_Skill1;
				curskillnum = 1;
				castskill1();
			}
		}
	}
}

void Tau::render()
{
	char tmp[50];
	if (curStatus == mon_onDeadProcess) {
		IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.5f, (0xAA - deadcount * 2>0 ? 0xAA - deadcount * 2 : 0));
		sprintf(tmp, "타우아미_%d", frame);
		IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x+(curDir? + 40:-40), (y + translate(z)) - cam.y, 500, 344, 1.0f, (0xFF - deadcount * 2>0 ? 0xFF - deadcount * 2 : 0), curDir);
	}
	else {
		IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.5f, 0xAA);
		sprintf(tmp, "타우아미_%d", frame);
		IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x+(curDir? + 40:-40), (y + translate(z)) - cam.y, 500, 344, 1.0f, 255, curDir);
	}
	if (onAbnormal) {
		switch (abnormalType) {
		case 0:
			frame = hitfrom;
			switch (abnormalStage) {
			case 0:
				sprintf(tmp, "빙결_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir ? -65 : 65), (y + translate(z) - 5) - cam.y, 200, 254, 1.f, 1.5f, 255, curDir);
				break;
			case 1:
				sprintf(tmp, "빙결_해제_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir ? -65 : 65), (y + translate(z) - 5) - cam.y, 200, 254, 1.f, 1.5f, 255, curDir);
				break;
			}
			break;
		}
	}
	if (onHold) {
		char tmp[50];
		for (vector<string>::iterator i = effectNames.begin(); i != effectNames.end(); i++) {
			sprintf(tmp, "%s%d", (*i).c_str(), effectframe1);
			IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - 100 - cam.x, (y + translate(z) - 120) - cam.y, 0, 0,1.5f,1.5f);
		}
	}
	if (printblood) {
		char tmp[50];
		if (bloodframe / 4 > 6) {
			bloodframe = 0;
			printblood = false;
		}
		sprintf(tmp, "혈흔_%d", bloodframe / 4);
		IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - 50 - cam.x, (y + translate(z) - 120) - cam.y,0,0,1.5f,1.5f);
	}

	for (list<HitQueue>::iterator i = hitQueue.begin(); i != hitQueue.end(); i++) {
		printNumber(*i);
	}
	MonsterBase::render();
}

void Tau::renderdc()
{
	RECT rc = RectMakeCenter(x -cam.x, translate(z) -cam.y, 120, 60 / 2);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

void Tau::setAttack()
{

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

Tau::Tau()
{
}


Tau::~Tau()
{
}

