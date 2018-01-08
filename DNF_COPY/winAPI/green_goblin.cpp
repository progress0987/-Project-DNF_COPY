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
	onAbnormal = false;
	abnormalCount = abnormalFrame = abnormalStage = abnormalType = -1;
	hitXvel = hitYvel = 0.f;
	probeX = 500;
	probeZ = 600;
	found = onAir = false;
	printblood = bloodframe = onAbnormal = false;
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
	if (actionTick > actionIndicate && !found&&(curStatus!=mon_Hit||curStatus!=mon_Falldown||curStatus!=mon_Wakeup)) {										//동작 변경
		int indicate = rand() % 100;
		if(indicate>30){																		//이동으로 변경
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
	//맞기시작
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
				if (i->isAbnormal) {
					switch (i->abnormal) {
					case 0://빙결
						frame = hitfrom;
						abnormalType = 0;
						abnormalStage = 0;
						abnormalCount = 0;
						if(!onAbnormal)
						abnormalFrame = 0;
						onAbnormal = true;
						break;
					case 10://화염
						if (abnormalType == 0) {
							abnormalType = -1;
							onAbnormal = false;
						}
					}
				}
			}
		}
	}
	if (hitAvailCount+10 < GetTickCount()&&!hitAvail) {
		hitAvail = true;
	}
	if (hitYvel < 0) { curStatus = mon_Falldown; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////맞는상태이면

	if (onAir) {
		if (!onAbnormal&& abnormalType != 0) {
			hitYvel += .1f;
			y += hitYvel;
			x += hitXvel;
		}
		if (y > 0) {
			y = 0;
			hitYvel = 0;
			onAir = false;
			onHitCount = GetTickCount();
		}
	}
	if (curStatus == mon_Hit || curStatus == mon_Falldown) {
		if (hitXvel != 0.f&&!onAir && abnormalType !=0) {
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
	/////////////////////////////////////////////////////////////////////////////////////////////////////////맞는상태이면
	if (curStatus == mon_Idle) {
		moveSpeedX = moveSpeedZ = 0;
		tick = 0;
	}
	//상태에 따른 처리
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

	if (onAbnormal) {																							////상태이상 처리
		switch (abnormalType) {
		case 0:
			printblood = false;
			y = 0;
			moveSpeedX = moveSpeedZ = hitYvel = hitXvel = 0;
			onAir = false;
			abnormalCount++;
			if (abnormalStage == 0) {
				if (abnormalFrame < 3&& abnormalCount%5==0) {
					abnormalFrame++;
				}
				if (abnormalCount >= 500) {
					abnormalStage = 1;
					abnormalFrame = 0;
				}
			}
			else if (abnormalStage == 1) {
				if (abnormalFrame < 5 && abnormalCount % 5 == 0) {
					abnormalFrame++;
				}if (abnormalFrame == 5) {
					onAbnormal = false;
					curStatus = mon_Idle;
					frame = idlefrom;
					abnormalType = -1;
				}
			}
			break;
		}
	}
	if (printblood) {
		bloodframe++;
	}

	if (tick % 5 == 0 && curStatus == mon_Walk) {														//걷기(이동)
		x += moveSpeedX;
		z += moveSpeedZ;
	}

	if (curStatus != mon_Hit&& curStatus != mon_Falldown&&abnormalType!=0) {
		curDir = curMap->getPlayer()->getX() > x ? true : false;
	}
	MonsterBase::update();
}

void green_goblin::render()
{
	char tmp[50];
	sprintf(tmp, "고블린_초록_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);

	sprintf(tmp, "고블린_무기_클럽_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y, 200, 154, 1.0f, 255, curDir);

	if (onAbnormal) {
		switch (abnormalType) {
		case 0:
			frame = hitfrom;
			switch (abnormalStage) {
			case 0:
				sprintf(tmp, "빙결_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir?-15:15), (y + translate(z) -5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			case 1:
				sprintf(tmp, "빙결_해제_%d", abnormalFrame);
				IMAGEMANAGER->findImage(tmp)->DFscaledrender(x - cam.x + (curDir?-15:15), (y + translate(z) -5) - cam.y, 200, 154, 0.4f, 0.4f, 255, curDir);
				break;
			}
			break;
		}
	}
	if (printblood) {
		char tmp[50];
		if (bloodframe/4 > 6) {
			bloodframe = 0;
			printblood = false;
		}
		sprintf(tmp, "혈흔_%d", bloodframe/4);
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
