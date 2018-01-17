#include "stdafx.h"
#include "icewave.h"


HRESULT icewave::init()
{
	reqMana = 150;
	chargeamount = 10;
	onCooldown = false;
	cooldownTick = 7000;			//쿨타임
	numofpillar = 30;
	this->begin = false;
	return S_OK;
}

void icewave::cast(FLOAT x, FLOAT y, FLOAT z)
{
	needles.clear();
	count = framecount = pillarcount = 0;
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
}

void icewave::update()
{
	if (oncast) {						//기술사용
		count++;
		if (count % 10 == 0&&oncast) {
			curAction++;
			if (curAction == 35) {//공격
				begin = true;
				head = pl->getCurDir();
				waveBegin = GetTickCount();
			}
			if (curAction > 41) {
				oncast = false;
			}
		}
	}
	else if (onCooldown&&cooldownstartfrom + cooldownTick<GetTickCount()) {
		onCooldown = false;
		cooldownstartfrom = 0;
	}
	if (begin&&!finished) {							//아이스웨이브 출력
		if ((GetTickCount() - waveBegin) % 5 == 0&& pillarcount<numofpillar) {//0.05초마다 기둥 하나씩 생성
			iceNeedle needle;
			needle.id = (pillarcount++)%11;
			needle.scale = 0.5f + (float)pillarcount * 0.05f;
			needle.curState = 0;
			needle.x = (head ? x + pillarcount * 15 + 100 : x - pillarcount * 15 - 100);
			needle.y = y;
			needle.z = z;
			needle.begintime = GetTickCount();
			needle.fadetime = 100;
			needle.staytime = 1000;
			needles.push_back(needle);
			effectedOnTime atk;
			atk.mindmg = (pl->getStatus().intel + pl->getStatus().a_intel)/2 + pl->getWeapon()->magdmgmin/2;
			atk.maxdmg = (pl->getStatus().intel + pl->getStatus().a_intel)/2 + pl->getWeapon()->magdmgmax/2;
			atk.isOnetime = false;
			atk.isCrit = rand() % 100 > 80 ? true : false;
			atk.isProjectile = false;
			atk.isAbnormal = true;
			atk.isHold = false;
			atk.abnormal = 0;

			atk.area.miny = -180 * needle.scale; atk.area.maxy = 0;
			atk.area.minz = needle.z - 60; atk.area.maxz = needle.z + 60;
			atk.area.maxx = needle.x + 30;
			atk.area.minx = needle.x - 30;
			atk.pushX = pl->getCurDir() ? 0.1f : 0.1f;
			atk.pushY = 0.f;												//추후 스킬레벨에따라 띄우기능력변경
			atk.staytime = 15;
			atk.time = GetTickCount();
			pl->addAttack(atk);

		}
		if (needles.size() == 0&&!oncast) {
			finished = true;
		}
		//atk.dmg = 5;
		//atk.isOnetime = true;
		//atk.isProjectile = false;
		//atk.area.miny = -180; atk.area.maxy = 0;
		//atk.area.minz = z - 50; atk.area.maxz = z + 50;
		//atk.area.maxx = pl->getCurDir() ? x + pl->getWeapon()->reachx + 100 : x - 10;
		//atk.area.minx = pl->getCurDir() ? x + 10 : x - pl->getWeapon()->reachx - 100;
		//atk.pushX = pl->getCurDir() ? 3.f : -3.f;
		//atk.pushY = -2.f;												//추후 스킬레벨에따라 띄우기능력변경
		//atk.staytime = 30;
		//atk.time = GetTickCount();
		//pl->addAttack(atk);
	}
}

void icewave::renderb()
{
	char tmp[50];
	//여기서부터는 스킬효과
	if (!finished) {
		for (list<iceNeedle>::iterator i = needles.begin(); i != needles.end();) {
			if (i->curState == 0) {					//이제 막 시작되었다면
				if (i->begintime + i->fadetime < GetTickCount()) {
					i->curState = 1;
					i++;
					continue;
				}
				sprintf(tmp, "파동검_빙인_얼음기둥_%d", i->id);
				IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x -cam.x, (i->y + translate(i->z)) -cam.y -(IMAGEMANAGER->findImage(tmp)->getHeight() * i->scale*0.5) +105, 100, 200, i->scale, (GetTickCount() - i->begintime) % 256);			//스킬 좌표 상태 체크
				IMAGEMANAGER->findImage("파동검_빙인_얼음구름_0")->DFpointrender(i->x - cam.x, (i->y + translate(i->z)+10) -cam.y, 98, 50, 1.f, (GetTickCount() - i->begintime) % 256);
			}
			else if (i->curState == 1) {			//유지되는중이라면
				if (i->begintime + i->staytime + i->fadetime < GetTickCount()) {
					i->curState = 2;
					i++;
					continue;
				}
				sprintf(tmp, "파동검_빙인_얼음기둥_%d", i->id);
				IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x -cam.x, (i->y + translate(i->z)) -cam.y - (IMAGEMANAGER->findImage(tmp)->getHeight() * i->scale*0.5) +105, 100, 200, i->scale);
				IMAGEMANAGER->findImage("파동검_빙인_얼음구름_0")->DFpointrender(i->x - cam.x, (i->y + translate(i->z)+10) -cam.y, 98, 50, 1.f);
				IMAGEMANAGER->findImage("파동검_빙인_얼음구름_1")->DFpointrender(i->x - cam.x, (i->y + translate(i->z)+10) - cam.y, 45, 20, 1.f);
			}
			else if (i->curState == 2) {			//사라지는중이라면
				if (i->begintime + i->staytime + (i->fadetime * 2) < GetTickCount()) {
					//모든 틱 카운트가 다 끝나면 삭제
					i = needles.erase(i);
					continue;
				}
				sprintf(tmp, "파동검_빙인_얼음기둥_%d", i->id);
				IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x -cam.x, (i->y + translate(i->z)) -cam.y -(IMAGEMANAGER->findImage(tmp)->getHeight() * i->scale*0.5) +105, 100, 200, i->scale, 255 - (GetTickCount() - i->begintime) % 256);
				IMAGEMANAGER->findImage("파동검_빙인_얼음구름_0")->DFpointrender(i->x - cam.x, (i->y + translate(i->z)+10) -cam.y, 98, 50, 1.f, 255 - (GetTickCount() - i->begintime) % 256);
				IMAGEMANAGER->findImage("파동검_빙인_얼음구름_1")->DFpointrender(i->x - cam.x, (i->y + translate(i->z)+10) - cam.y, 45, 20, 1.f, 255 - (GetTickCount() - i->begintime) % 256);
				IMAGEMANAGER->findImage("파동검_빙인_얼음구름_2")->DFpointrender(i->x - cam.x, (i->y + translate(i->z)+10) -cam.y, 115, 50, 1.f, 255 - (GetTickCount() - i->begintime) % 256);
			}
			i++;
		}
	}

}

void icewave::renderf()
{
	char tmp[50];
	if (oncast) {
		if (35 <= curAction && curAction <= 40) {
			sprintf(tmp, "파동검_빙인_시작효과_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +300 : -300) - cam.x, y + translate(z) + 220 - cam.y, head);
		}
	}
	
}

icewave::icewave()
{
}


icewave::~icewave()
{
}
