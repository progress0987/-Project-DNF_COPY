#include "stdafx.h"
#include "green_goblin.h"


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
	probeX = 500;
	probeZ = 600;
	found = false;
	return S_OK;
}

HRESULT green_goblin::init(int x, int z)
{
	goblin_base::init();
	this->x = x;
	this->z = z;
	y = 0;
	frame = 0;
	actionTick = 0;
	actionIndicate = rand() % 500+300;
	curStatus = mon_Idle;
	moveSpeedMaxX = moveSpeedMaxZ = 5.0f;
	probeX = 500;
	probeZ = 600;
	found = false;
	return S_OK;
}

void green_goblin::update()
{
	actionTick++;
	if (actionTick > actionIndicate && !found) {															//동작 변경
		int indicate = rand() % 100;
		if(indicate>60){																		//이동으로 변경
			curStatus = mon_Walk;
			moveSpeedX = RND->getFloat(moveSpeedMaxX) - moveSpeedMaxX/2.f;
			moveSpeedX += moveSpeedX > 0.f ? 1.f : -1.f;
			moveSpeedZ = RND->getFloat(moveSpeedMaxZ) - moveSpeedMaxZ/2.f;
			moveSpeedZ += moveSpeedX > 0.f ? 1.f : -1.f;
			frame = walkfrom;
			actionIndicate = rand() % 300 + 200;
		}
		else {																					//가만히 있기
			curStatus = mon_Idle;
			frame = idlefrom;
			actionIndicate = rand() % 500 + 300;
		}
		actionTick = 0;
	}else if (isdetected()) {
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

	if (curStatus == mon_Idle) {
		moveSpeedX = moveSpeedZ = 0;
		tick = 0;
	}
	switch (curStatus) {																		//프레임이미지 처리부분
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
				frame = falldownto;			//계속 쓰러져있는 상태로 유지
			}
		}
	}


	if (tick % 5 == 0 && mon_Walk) {
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
	sprintf(tmp, "고블린_초록_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y+translate(z)) - cam.y,200,154,curDir);

	sprintf(tmp, "고블린_무기_클럽_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y+translate(z)) - cam.y,200,154,curDir);

}

void green_goblin::renderdc()
{
}

green_goblin::green_goblin()
{
}


green_goblin::~green_goblin()
{
}
