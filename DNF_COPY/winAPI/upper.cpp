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
	SOUNDMANAGER->play("ĳ��_��ų_����");
}
/*
struct effected{
FLOAT maxx, minx;
FLOAT maxy, miny;
FLOAT maxz, minz;
};
struct effectedOnTime {
int dmg;									//�����
int dmgTick;								//������� �󸶸��� ������(ƽ/�ð�)
effected area;								//����� Ÿ�� ����

DWORD time;									//���� ����� ���۽ð�
unsigned int staytime;						//���� ����� �����ð�

bool isProjectile;							//����ü����
bool isOnetime;								//���������� ���°���(�ʿ�����?)

FLOAT pushX, pushY;							//�� ������ �о�� ����
};
*/
void upper::update()
{
	if (!finished) {						//������
		count++;
		if (count % 4 == 0) {
			curAction++;
			if (curAction == 35) {//����
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
				atk.pushY = -5.f;												//���� ��ų���������� ����ɷº���
				atk.staytime = 10;
				atk.time = GetTickCount();
				pl->addAttack(atk);
				SOUNDMANAGER->play("ĳ��_��ų����_����");
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
		sprintf(tmp, "���۽�����_%d", curAction - 35);
		IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(pl->getCurDir()?+100:-100) - cam.x, (y + translate(z)+100) - cam.y, pl->getCurDir());
	}
}

void upper::renderf()
{
	if (!finished&&35<=curAction&&curAction<=38) {
		char tmp[50];
		sprintf(tmp, "���۽�����_%d", curAction - 31);
		IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x+(pl->getCurDir()?+150:-150) - cam.x, (y + translate(z)+100) - cam.y, pl->getCurDir());
	}

}

upper::upper()
{
}


upper::~upper()
{
}
