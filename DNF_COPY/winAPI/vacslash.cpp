#include "stdafx.h"
#include "vacslash.h"


HRESULT vacslash::init()
{
	reqMana = 200;
	onCooldown = false;
	cooldownTick = 500;			//쿨타임
	isChargable = true;
	chargemax = 1000;
	chargeamount = 500;
	chargetick = 10;
	travelDist = 500;			//사정거리
	sl.onshow = false;
	skillActive = 108;
	skillInactive = 109;
	return S_OK;
}

void vacslash::cast(FLOAT x, FLOAT y, FLOAT z)
{
	onCharge = true;
	curAction = 139;
	this->x = x;
	this->y = y;
	this->z = z;
	finished = false;
	oncast = true;
	isbuff = false;
	head = pl->getCurDir();
	cooldownstartfrom = GetTickCount();
	onCooldown = true;
	curcharge = 0;
	chargeFrame = fullchargeFrame = chargeStatus = 0;
	sl.onshow = false;
	playedchargesound = false;
}

void vacslash::update()
{
	count++;
	if (oncast) {						//기술사용
		if (KEYMANAGER->isStayKeyDown('F')) {//충전
			onCharge = true;
			sl.onshow = false;
			if (count%chargetick == 0) {
				curcharge += chargeamount;
				if (curcharge > chargemax) {
					chargeStatus = 1;
					curcharge = chargemax;
					if (!playedchargesound) {
						SOUNDMANAGER->play("캐릭_스킬_충전");
						playedchargesound = true;
					}
				}
			}
		}
		if (KEYMANAGER->isOnceKeyUp('F')) {//발사
			onCharge = false;
			if (chargeStatus > 0) {
				sl.dmg = 30;
				SOUNDMANAGER->play("캐릭_스킬_진공참");
			}
			else {
				sl.dmg = 15;
				SOUNDMANAGER->play("캐릭_스킬_수라진공참");
			}
		}
		switch (chargeStatus) {
		case 0:
			if (count % 5 == 0) {
				chargeFrame++;
				if (chargeFrame > 12) chargeFrame = 0;
			}
			break;
		case 1:
			if (count % 5 == 0) {
				fullchargeFrame++;
				if (fullchargeFrame > 4) {
					chargeStatus = 2;
				}
			}
			break;
		case 2:
			break;
		}
		if (onCharge) {
			curAction = 139;
		}
		else {
			if (count % 7 == 0) {
				curAction++;
				if (curAction == 141) {
					sl.onshow = true;
					sl.x = x;
					sl.y = y;
					sl.z = z;
					sl.dmgtick = 0;
					if (chargeStatus > 0) {
						sl.dmg = 30;
						travelDist = 500;
					}
					else {
						sl.dmg = 15;
						travelDist = 300;
					}
				}
				if (curAction > 156) {
					oncast = false;
				}
			}
		}
	}
	else if (onCooldown&&cooldownstartfrom + cooldownTick<GetTickCount()) {
		onCooldown = false;
		cooldownstartfrom = 0;
	}
	if (sl.onshow) {
		sl.dmgtick++;
		sl.x += (head?3:-3);
		if (sl.dmgtick % 20 == 0) {
			effectedOnTime atk;
			atk.isCrit = rand() % 100 > 80 ? true : false;
			atk.mindmg = atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) + pl->getWeapon().magdmgmin * 2)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel) + pl->getWeapon().magdmgmin * 2;
			atk.maxdmg = atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmax * 2)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmax * 2;
			atk.isOnetime = true;
			atk.isProjectile = true;
			atk.isAbnormal = false;
			atk.isHold = false;
			atk.area.miny = (chargeStatus>0?-200:-100); atk.area.maxy = 0;
			atk.area.minz = sl.z + (chargeStatus>0?-150:-90); atk.area.maxz = sl.z + (chargeStatus>0?+150:+90);
			atk.area.maxx = sl.x + 100;
			atk.area.minx = sl.x - 100;
			atk.pushX = head ? 4.f : -4.f;
			atk.pushY = chargeStatus > 0 ? -3.5f : -2.f;												//추후 스킬레벨에따라 띄우기능력변경
			atk.staytime = 10;
			atk.time = GetTickCount();
			pl->addAttack(atk);
		}
		if (abs(sl.x - x) > travelDist) {
			sl.onshow = false;
		}
	}
}

void vacslash::renderb()
{
}

void vacslash::renderf()
{
	char tmp[50];
	if (onCharge) {
		if (chargeStatus == 0) {
			sprintf(tmp, "진공참_차지중_뒤_%d", chargeFrame);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(head?100:-100) -cam.x, y + translate(z)+100 -cam.y, head);
			sprintf(tmp, "진공참_차지중_앞_%d", chargeFrame);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(head?100:-100)-cam.x, y + translate(z)+100-cam.y, head);
		}
		else if (chargeStatus == 1) {
			if (fullchargeFrame < 4) {
				sprintf(tmp, "진공참_풀차지_뒤_%d", fullchargeFrame);
				IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(head?100:-100) - cam.x, y + translate(z)+100 - cam.y, head);
				sprintf(tmp, "진공참_풀차지_앞_%d", fullchargeFrame);
				IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(head?100:-100) - cam.x, y + translate(z)+100 - cam.y, head);
			}
		}
	}
	else {
		if (142<=curAction&&curAction<=145) {
			sprintf(tmp, "진공참_모션_%d", curAction-142);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x-cam.x, y + translate(z)-cam.y, head);
		}
	}
	if (sl.onshow) {//진공참 그려주기
		if (chargeStatus > 0) {//풀차지
			sprintf(tmp, "수라진공참_뒤");
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(sl.x-cam.x, sl.y + translate(sl.z)+100-cam.y, head);
			sprintf(tmp, "수라진공참_앞");
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(sl.x-cam.x, sl.y + translate(sl.z)+100-cam.y, head);
		}
		else {//일반
			sprintf(tmp, "진공참_뒤");
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(sl.x-cam.x, sl.y + translate(sl.z)+100-cam.y, head);
			sprintf(tmp, "진공참_앞");
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(sl.x-cam.x, sl.y + translate(sl.z)+100-cam.y, head);
		}
	}
}

vacslash::vacslash()
{
}


vacslash::~vacslash()
{
}
