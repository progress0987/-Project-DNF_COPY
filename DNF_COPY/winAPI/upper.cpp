#include "stdafx.h"
#include "upper.h"

HRESULT upper::init()
{

	reqMana = 30;
	cooldownTick = 500;
	onCooldown = false;
	return S_OK;
}

void upper::cast(FLOAT x, FLOAT y, FLOAT z)
{
	count = framecount = 0;

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
	SOUNDMANAGER->play("캐릭_스킬_어퍼");
}
/*
struct effected{
FLOAT maxx, minx;
FLOAT maxy, miny;
FLOAT maxz, minz;
};
struct effectedOnTime {
int dmg;									//대미지
int dmgTick;								//대미지가 얼마마다 들어올지(틱/시간)
effected area;								//대미지 타격 범위

DWORD time;									//공격 대미지 시작시간
unsigned int staytime;						//공격 대미지 유지시간

bool isProjectile;							//투사체인지
bool isOnetime;								//지속적으로 남는건지(필요할지?)

FLOAT pushX, pushY;							//각 축으로 밀어내는 정도
};
*/
void upper::update()
{
	if (!finished) {						//기술사용
		count++;
		if (count % 4 == 0) {
			curAction++;
			if (curAction == 35) {//공격
				effectedOnTime atk;
				atk.isCrit = rand() % 100 > 70 ? true : false;
				atk.mindmg = atk.isCrit?((pl->getStatus().str + pl->getStatus().a_str) * 2 + pl->getWeapon().phydmgmin)*1.5: (pl->getStatus().str + pl->getStatus().a_str) * 2 + pl->getWeapon().phydmgmin;
				atk.maxdmg = atk.isCrit?((pl->getStatus().str + pl->getStatus().a_str) * 3 + pl->getWeapon().phydmgmax)*1.5: (pl->getStatus().str + pl->getStatus().a_str) * 3 + pl->getWeapon().phydmgmax;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.isHold = false;
				atk.area.miny = -180; atk.area.maxy = 0;
				atk.area.minz = z - 50; atk.area.maxz = z + 50;
				atk.area.maxx = pl->getCurDir() ? x + pl->getWeapon().reachx : x - 10;
				atk.area.minx = pl->getCurDir() ? x + 10 : x - pl->getWeapon().reachx;
				atk.pushX = pl->getCurDir() ? 1.f : -1.f;
				atk.pushY = -5.f;												//추후 스킬레벨에따라 띄우기능력변경
				atk.staytime = 10;
				atk.time = GetTickCount();
				pl->addAttack(atk);
				SOUNDMANAGER->play("캐릭_스킬사운드_어퍼");
			}
			if (curAction > 41) {
				finished = true;
				oncast = false;
			}
		}

	}
	else if(onCooldown&&cooldownstartfrom + cooldownTick<GetTickCount()){
		onCooldown = false;
		cooldownstartfrom = 0;
	}
}

void upper::renderb()
{	if (!finished&&35<=curAction&&curAction<=38) {
		char tmp[50];
		sprintf(tmp, "어퍼슬래시_%d", curAction - 35);
		IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(pl->getCurDir()?+100:-100) - cam.x, (y + translate(z)+100) - cam.y, pl->getCurDir());
	}
}

void upper::renderf()
{
	if (!finished&&35<=curAction&&curAction<=38) {
		char tmp[50];
		sprintf(tmp, "어퍼슬래시_%d", curAction - 31);
		IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(pl->getCurDir()?+150:-150) - cam.x, (y + translate(z)+100) - cam.y, pl->getCurDir());
	}

}

upper::upper()
{
}


upper::~upper()
{
}
