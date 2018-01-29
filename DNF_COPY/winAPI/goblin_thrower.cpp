#include "stdafx.h"
#include "goblin_thrower.h"


HRESULT goblin_thrower::init()
{
	goblin_base::init();
	sprintf(stat.name, "투석 고블린");
	x = rand() % curMap->getWidth();
	y = 0;
	int range = WINSIZEY - 350;
	z = (rand() % range + 350) * 2;

	aggressive = 60;
	atkcooldown = 1000;
	goldAmount = 10;
	expamount = 50;

	actionIndicate = rand() % 200 + 200;
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

HRESULT goblin_thrower::init(int x, int z)
{
	goblin_thrower::init();
	this->x = x;
	this->z = z;
	return S_OK;
}

void goblin_thrower::update()
{
	MonsterBase::update();
	//공격
	if (curatkcooldown <= 0 && !onAttack) {
		if (x - 300 < curMap->getPlayer()->getX() && curMap->getPlayer()->getX() < x + 300 &&
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

void goblin_thrower::render()
{
	char tmp[50];
	if (curStatus == mon_onDeadProcess) {
		IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.25, (0xAA - deadcount * 2>0 ? 0xAA - deadcount * 2 : 0));
		sprintf(tmp, "고블린_투석_%d", frame);
		IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, (0xFF - deadcount * 2>0 ? 0xFF - deadcount * 2 : 0), curDir);
	}
	else {
		IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.25, 0xAA);
		sprintf(tmp, "고블린_투석_%d", frame);
		IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);
	}
	
	if (onAbnormal) {
		switch (abnormalType) {
		case 0:
			frame = hitfrom;
			switch (abnormalStage) {
			case 0:
				sprintf(tmp, "빙결_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir ? -15 : 15), (y + translate(z) - 5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			case 1:
				sprintf(tmp, "빙결_해제_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir ? -15 : 15), (y + translate(z) - 5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			}
			break;
		}
	}
	if (onHold) {
		char tmp[50];
		for (vector<string>::iterator i = effectNames.begin(); i != effectNames.end(); i++) {
			sprintf(tmp, "%s%d", (*i).c_str(), effectframe1);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(x - 60 - cam.x, (y + translate(z) - 80) - cam.y, 0, 0);
		}
	}
	if (printblood) {
		char tmp[50];
		if (bloodframe / 4 > 6) {
			bloodframe = 0;
			printblood = false;
		}
		sprintf(tmp, "혈흔_%d", bloodframe / 4);
		IMAGEMANAGER->findImage(tmp)->render(x - 50 - cam.x, (y + translate(z) - 80) - cam.y);
	}

	for (list<HitQueue>::iterator i = hitQueue.begin(); i != hitQueue.end(); i++) {
		printNumber(*i);
	}
	MonsterBase::render();
}

void goblin_thrower::renderdc()
{
}

void goblin_thrower::setAttack()
{
	projectile p;
	p.accelx = p.accely = p.accelz = 0;
	p.frame = 0;
	p.framemax = 4;
	p.hitCount = 1;
	p.imgName = "고블린_무기_투석_";
	p.sizex = 50;
	p.sizey = 20;
	p.sizez = 60;
	p.speedz = 0;
	p.speedy = 0;
	p.speedx = curDir ? 5 : -5;
	p.x = x;
	p.y = y - 10;
	p.z = z;
	p.imgOffsetX = 0;
	p.imgOffsetY = -50;
	p.distance = 500;
	p.gravity = false;
	p.abnormal = -1;

	effectedOnTime a;
	a.isAbnormal = a.isHold = a.isMove = false;
	a.isProjectile = true;
	a.isOnetime = true;
	a.isCrit = rand() % 100 > 80 ? true : false;
	a.time = GetTickCount();
	a.staytime = 10;

	a.mindmg = a.isCrit ? stat.dmgmin*1.5 : stat.dmgmin;
	a.maxdmg = a.isCrit ? stat.dmgmax*1.5 : stat.dmgmax;
	a.pushX = 0;
	a.pushY = 0;
	a.pushZ = 0;
	p.dmginfo = a;

	projectiles.push_back(p);

}

goblin_thrower::goblin_thrower()
{
}


goblin_thrower::~goblin_thrower()
{
}
