#include "stdafx.h"
#include "wave.h"


HRESULT wave::init()
{

	reqMana  = 50;
	chargeamount = 10;
	onCooldown = false;
	cooldownTick=400;
	skillActive = 6;
	skillInactive = 7;

	return S_OK;
}

void wave::cast(FLOAT x, FLOAT y, FLOAT z)
{
	count=framecount=0;
	curAction = 33;
	this->x = x;
	this->y = y;
	this->z = z;
	finished = false;
	oncast = true;
	isbuff = false;
	cooldownstartfrom = GetTickCount();
	onCooldown = true;
	curcharge = 0;
	SOUNDMANAGER->play("캐릭_스킬_웨이브");
}

void wave::update()
{
	if (!finished&&oncast) {						//기술사용
		count++;
		if (count % 4 == 0) {
			curAction++;
			if (curAction == 35) {//공격
				effectedOnTime atk;
				atk.isCrit = rand() % 100 > 60 ? true : false;
				atk.mindmg =atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmin*1.5f)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmin*1.5f;
				atk.maxdmg =atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 3 + pl->getWeapon().magdmgmax*1.5f)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel) * 3 + pl->getWeapon().magdmgmax*1.5f;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.isHold = false;
				atk.area.miny = -180; atk.area.maxy = 0;
				atk.area.minz = z - 50; atk.area.maxz = z + 50;
				atk.area.maxx = pl->getCurDir() ? x + pl->getWeapon().reachx + 100 : x - 10;
				atk.area.minx = pl->getCurDir() ? x + 10 : x - pl->getWeapon().reachx - 100;
				atk.pushX = pl->getCurDir() ? 3.f : -3.f;
				atk.pushY = -2.f;												//추후 스킬레벨에따라 띄우기능력변경
				atk.staytime = 10;
				atk.time = GetTickCount();
				pl->addAttack(atk);
				SOUNDMANAGER->play("캐릭_스킬사운드_웨이브");
			}
			if (curAction > 41) {
				finished = true;
				oncast = false;
			}
		}
	}
	else if (onCooldown&&cooldownstartfrom + cooldownTick<GetTickCount()) {
		onCooldown = false;
		cooldownstartfrom = 0;
	}
}

void wave::renderb()
{
	if (35 <= curAction && curAction <= 39) {
		char tmp[50];
		sprintf(tmp, "파동검_효과_%d", curAction - 35);
		IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir()?+170:-170) -cam.x, y + translate(z)+100 -cam.y, pl->getCurDir());
	}
}
void wave::renderf()
{
	if (35 <= curAction && curAction <= 39) {
		char tmp[50];
		sprintf(tmp, "파동검_공격_%d", curAction - 35);
		IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +150 : -150) - cam.x, y + translate(z) + 100 - cam.y, pl->getCurDir());
	}
}

wave::wave()
{
}


wave::~wave()
{
}
