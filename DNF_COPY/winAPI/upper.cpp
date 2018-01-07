#include "stdafx.h"
#include "upper.h"

HRESULT upper::init()
{

	reqMana = 10;
	cooldownTick = 700;
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
				atk.dmg = 5;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.area.miny = -180; atk.area.maxy = 0;
				atk.area.minz = z - 50; atk.area.maxz = z + 50;
				atk.area.maxx = pl->getCurDir() ? x + pl->getWeapon()->reachx : x - 10;
				atk.area.minx = pl->getCurDir() ? x + 10 : x - pl->getWeapon()->reachx;
				atk.pushX = pl->getCurDir() ? 1.f : -1.f;
				atk.pushY = -5.f;												//���� ��ų���������� ����ɷº���
				atk.staytime = 30;
				atk.time = GetTickCount();
				pl->addAttack(atk);
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