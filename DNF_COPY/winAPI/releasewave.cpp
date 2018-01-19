#include "stdafx.h"
#include "releasewave.h"


HRESULT releasewave::init()
{
	reqMana = 100;
	onCooldown = false;
	oncast = false;
	cooldownTick = 4000;
	return S_OK;
}

void releasewave::cast(FLOAT x, FLOAT y, FLOAT z)
{
	count = framecount = 0;
	curAction = 75;
	this->x = x;
	this->y = y;
	this->z = z;
	finished = false;
	oncast = true;
	isbuff = false;
	cooldownstartfrom = GetTickCount();
	onCooldown = true;
	curcharge = 0;
}

void releasewave::update()
{
	if (!finished&&oncast) {						//기술사용
		count++;
		if (count % 8 == 0&&curAction<80) {
			curAction++;
		}
		else if (count % 5 == curAction >= 80) {
			curAction++;
			if (curAction == 81) {//공격
				effectedOnTime atk;
				atk.isCrit = rand() % 100 > 90 ? true : false;
				atk.mindmg =atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmin*1.5f)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmin*1.5f;
				atk.maxdmg =atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 3 + pl->getWeapon().magdmgmax*1.5f)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmax*1.5f;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.isHold = false;
				atk.area.miny = -200; atk.area.maxy = 0;
				atk.area.minz = z - 200; atk.area.maxz = z + 200;
				atk.area.maxx = x +200;
				atk.area.minx = x - 200;
				atk.pushX = pl->getCurDir() ? 5.f : -5.f;
				atk.pushY = -6.f;												//추후 스킬레벨에따라 띄우기능력변경
				atk.staytime = 30;
				atk.time = GetTickCount();
				pl->addAttack(atk);
			}
			if (curAction > 89) {
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

void releasewave::renderb()
{
}

void releasewave::renderf()
{
	char tmp[50];
	if (curAction > 80) {
		if (81 <= curAction && curAction <= 86) {
			sprintf(tmp, "파동해제_해골_%d", curAction - 81);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, y + translate(z) - cam.y);
			if (curAction <= 85) {
			sprintf(tmp, "파동해제_효과_%d", curAction - 81);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, y + translate(z) - cam.y);
			}
		}
	}
}

releasewave::releasewave()
{
}


releasewave::~releasewave()
{
}
