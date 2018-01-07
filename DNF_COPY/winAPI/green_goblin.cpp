#include "stdafx.h"
#include "green_goblin.h"

//���� Ÿ�ݰ��� �ٽú���(���� ������ �̻���)
HRESULT green_goblin::init()
{
	goblin_base::init();
	x = rand() % curMap->getWidth();
	y = 0;
	int range = WINSIZEY - 350;
	z = (rand() % range + 350) * 2;
	frame = 0;
	actionTick = 0;
	actionIndicate = rand() % 500+300;
	curStatus = mon_Idle;
	moveSpeedMaxX = moveSpeedMaxZ = 6.0f;
	hitXvel = hitYvel = 0.f;
	probeX = 500;
	probeZ = 600;
	found = onAir = false;
	printblood = bloodframe = false;
	hitAvail = -1;
	return S_OK;
}

HRESULT green_goblin::init(int x, int z)
{
	goblin_base::init();
	green_goblin::init();
	this->x = x;
	this->z = z;
	y = 0;

	return S_OK;
}

void green_goblin::update()
{
	actionTick++;
	if (actionTick > actionIndicate && !found&&(curStatus!=mon_Hit||curStatus!=mon_Falldown||curStatus!=mon_Wakeup)) {										//���� ����
		int indicate = rand() % 100;
		if(indicate>30){																		//�̵����� ����
			curStatus = mon_Walk;
			moveSpeedX = RND->getFloat(moveSpeedMaxX) - moveSpeedMaxX/2.f;
			moveSpeedX += moveSpeedX > 0.f ? 1.f : -1.f;
			moveSpeedZ = RND->getFloat(moveSpeedMaxZ) - moveSpeedMaxZ/2.f;
			moveSpeedZ += moveSpeedX > 0.f ? 1.f : -1.f;
			frame = walkfrom;
			actionIndicate = rand() % 300 + 200;
		}
		else {																					//������ �ֱ�
			curStatus = mon_Idle;
			frame = idlefrom;
			actionIndicate = rand() % 500 + 300;
		}
		actionTick = 0;
	}
	else if (isdetected()&&curStatus!=mon_Hit) {
		found = true;
		if (curMap->getPlayer()->getX() > x) {
			moveSpeedX = 4.f;
		}
		else if (x-4.f<=curMap->getPlayer()->getX()&&curMap->getPlayer()->getX()<= x+4.f) {
			//x = curMap->getPlayer()->getX();
			moveSpeedX = 0.f;
		}
		else {
			moveSpeedX = -4.f;
		}

		if (curMap->getPlayer()->getZ() > z) {
			moveSpeedZ = 5.f;
		}
		else if( z - 5.f <= curMap->getPlayer()->getZ() && curMap->getPlayer()->getZ() <= z + 5.f) {
			moveSpeedZ = 0.f;
		}
		else {
			moveSpeedZ = -5.f;
		}
	}
	else {
		found = false;
	}
	//���ݽ���
	for (list<effectedOnTime>::iterator i = curMap->getPlayer()->getAttackQueueBegin(); i != curMap->getPlayer()->getAttackQueueEnd(); i++) {
		if (curMap->getPlayer()->getAttackQueue().size() > 0 && hitAvail) {
			if (i->area.minx < x&&x < i->area.maxx&&
				i->area.minz < z&&z < i->area.maxz&&
				i->area.miny < y&&y <= i->area.maxy) {
				curStatus = mon_Hit;
				hitAvail = false;
				printblood=true;
				frame = hitfrom;
				hitXvel = i->pushX;
				hitYvel = i->pushY;
				if (hitYvel < 0) {
					onAir = true; curStatus = mon_Falldown; frame = falldownfrom;
				}
				onHitCount = hitAvailCount = GetTickCount();
			}
		}
	}
	if (hitAvailCount+10 < GetTickCount()&&!hitAvail) {
		hitAvail = true;
	}
	if (hitYvel < 0) { curStatus = mon_Falldown; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////�´»����̸�

	if (onAir) {
		hitYvel += .1f;
		y += hitYvel;
		x += hitXvel;
		if (y > 0) {
			y = 0;
			hitYvel = 0;
			onAir = false;
			onHitCount = GetTickCount();
		}
	}
	if (curStatus == mon_Hit || curStatus == mon_Falldown) {
		if (hitXvel != 0.f&&!onAir) {
			x += hitXvel;
			hitXvel *= 0.8f;
			if (-0.5f < hitXvel&&hitXvel < 0.5f) hitXvel = 0.f;
		}
		if (!onAir && onHitCount + 300< GetTickCount() && hitXvel == 0.f) {
			if (curStatus == mon_Falldown) {
				curStatus = mon_Wakeup;
				frame = wakeupfrom;
			}
			else if (curStatus == mon_Hit) {
				curStatus = mon_Idle;
				frame = idlefrom;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////�´»����̸�
	if (curStatus == mon_Idle) {
		moveSpeedX = moveSpeedZ = 0;
		tick = 0;
	}
	//���¿� ���� ó��
	switch (curStatus) {																		//�������̹��� ó���κ�
	case mon_Walk:
		tick++;
		if (tick % 15 == 0) {
			frame++;
			if (frame > walkto) {
				frame = walkfrom;
			}
		}
		break;
	case mon_Idle:
		tick++;
		if (tick % 15 == 0) {
			frame++;
			if (frame > idleto) {
				frame = idlefrom;
			}
		}
		break;
	case mon_Attack:
		tick++;
		if (tick % 10 == 0) {
			frame++;
			if (frame > attackto) {
				frame = attackfrom;
			}
		}
		break;
	case mon_Hit:
		tick++;
		if (tick % 10 == 0) {
			frame++;
			if (frame > hitto) {
				frame = hitfrom;
			}
		}
		break;
	case mon_Falldown:
		tick++;
		if (tick % 15 == 0) {
			if(frame!=falldownto)
				frame++;
			if (frame > falldownto) {
				frame = falldownto;			//��� �������ִ� ���·� ����
			}
		}
		break;
	case mon_Wakeup:
		tick++;
		if (tick % 30 == 0) {
			frame++;
			if (frame > wakeupto) {
				curStatus = mon_Idle;
				frame = idlefrom;
			}
		}
		break;
	}

	if (printblood) {
		bloodframe++;
	}

	if (tick % 5 == 0 && curStatus == mon_Walk) {														//�ȱ�(�̵�)
		x += moveSpeedX;
		z += moveSpeedZ;
	}

	if (curStatus != mon_Hit&& curStatus != mon_Falldown) {
		curDir = curMap->getPlayer()->getX() > x ? true : false;
	}
	MonsterBase::update();
}

void green_goblin::render()
{
	char tmp[50];
	sprintf(tmp, "���_�ʷ�_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y+translate(z)) - cam.y,200,154,curDir);

	sprintf(tmp, "���_����_Ŭ��_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y+translate(z)) - cam.y,200,154,curDir);

	if (printblood) {
		char tmp[50];
		if (bloodframe/4 > 6) {
			bloodframe = 0;
			printblood = false;
		}
		sprintf(tmp, "����_%d", bloodframe/4);
		IMAGEMANAGER->findImage(tmp)->render(x - 50 -cam.x, (y + translate(z) - 80) -cam.y);
	}
}

void green_goblin::renderdc()
{
	//Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom -cam.y);
}

green_goblin::green_goblin()
{
}


green_goblin::~green_goblin()
{
}
