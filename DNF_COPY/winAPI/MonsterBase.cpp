#include "stdafx.h"
#include "MonsterBase.h"


HRESULT MonsterBase::init()
{
	return S_OK;
}

void MonsterBase::update()
{
	actionTick++;
	if (!onHold) {
		if (actionTick > actionIndicate && !found && (curStatus != mon_Hit || curStatus != mon_Falldown || curStatus != mon_Wakeup)) {										//���� ����
			int indicate = rand() % 100;
			if (indicate > 30) {																		//�̵����� ����
				curStatus = mon_Walk;
				moveSpeedX = RND->getFloat(moveSpeedMaxX) - moveSpeedMaxX / 2.f;
				moveSpeedX += moveSpeedX > 0.f ? 1.f : -1.f;
				moveSpeedZ = RND->getFloat(moveSpeedMaxZ) - moveSpeedMaxZ / 2.f;
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
		else if (isdetected() && curStatus != mon_Hit) {
			found = true;
			if (curMap->getPlayer()->getX() > x) {
				moveSpeedX = 4.f;
			}
			else if (x - 4.f <= curMap->getPlayer()->getX() && curMap->getPlayer()->getX() <= x + 4.f) {
				//x = curMap->getPlayer()->getX();
				moveSpeedX = 0.f;
			}
			else {
				moveSpeedX = -4.f;
			}

			if (curMap->getPlayer()->getZ() > z) {
				moveSpeedZ = 5.f;
			}
			else if (z - 5.f <= curMap->getPlayer()->getZ() && curMap->getPlayer()->getZ() <= z + 5.f) {
				moveSpeedZ = 0.f;
			}
			else {
				moveSpeedZ = -5.f;
			}
		}
		else {
			found = false;
		}
	}
	//�±����
	for (list<effectedOnTime>::iterator i = curMap->getPlayer()->getAttackQueueBegin(); i != curMap->getPlayer()->getAttackQueueEnd(); i++) {
		if (curMap->getPlayer()->getAttackQueue().size() > 0 && hitAvail) {
			if (i->area.minx < x&&x < i->area.maxx&&
				i->area.minz < z&&z < i->area.maxz&&
				i->area.miny < y&&y <= i->area.maxy) {
				float tempangle = getAngle(pl->getX(), pl->getZ(), x, z);
				curStatus = mon_Hit;
				hitAvail = false;
				printblood = true;
				onHold = i->isHold;
				frame = hitfrom;
				hitXvel = i->pushX;
				hitYvel = i->pushY;
				if (hitYvel < 0) {
					onAir = true; curStatus = mon_Falldown; frame = falldownfrom;
				}
				onHitCount = hitAvailCount = GetTickCount();
				if (i->isAbnormal) {
					switch (i->abnormal) {
					case 0://����
						frame = hitfrom;
						abnormalType = 0;
						abnormalStage = 0;
						abnormalCount = 0;
						if (!onAbnormal)
							abnormalFrame = 0;
						onAbnormal = true;
						break;
						//case 9://Ȧ��
						//	abnormalType = 9;
						//	onAbnormal = true;
						//	break;
					case 10://ȭ��
						if (abnormalType == 0) {
							abnormalType = -1;
							onAbnormal = false;
						}
						break;
					case 50://�����̵� - �����Ÿ�
						effectNames.clear();
						abnormalType = 50;
						onAbnormal = true;
						printblood = false;
						frame = hitfrom;
						destX = pl->getX() + cosf(tempangle) * i->attr1;
						destZ = pl->getZ() - sinf(tempangle) * i->attr1;
						destY = i->attr2;
						effectframeMax = (int)i->attr3;
						effectframe1 = 0;
						for (vector<string>::iterator a = i->effectNames.begin(); a != i->effectNames.end(); a++) {
							effectNames.push_back((*a));
						}
						break;
					case 51://�����̵� ����	
						effectNames.clear();
						abnormalType = -1;
						onAbnormal = false;
						onHold = false;
						hitAvail = true;
						if (y < 0) {
							curStatus = mon_Falldown;
							onAir = true;
						}
						break;
					}
				}
			}
		}
	}
	if (hitAvailCount + 10 < GetTickCount() && !hitAvail) {
		hitAvail = true;
	}
	if (hitYvel < 0 && !onHold) { curStatus = mon_Falldown; }
	/////////////////////////////////////////////////////////////////////////////////////////////////////////�´»����̸�

	if (onHold) {
		if (tick % 10 == 0) {
			effectframe1++;
			if (effectframe1 >= effectframeMax) {
				effectframe1 = 0;
			}
		}
	}
	if (onAir) {
		if (!onAbnormal&& abnormalType != 0) {
			hitYvel += .1f;
			y += hitYvel;
			x += hitXvel;
		}
		//if (!onHold&&y<0) {
		//	hitYvel += .1f;
		//	y += hitYvel;
		//}
		if (y > 0) {
			y = 0;
			hitYvel = 0;
			onAir = false;
			onHitCount = GetTickCount();
		}
	}
	if ((curStatus == mon_Hit || curStatus == mon_Falldown) && !onHold) {
		if (hitXvel != 0.f && !onAir && abnormalType != 0) {
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
			if (frame != falldownto)
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

	if (onAbnormal) {																							////�����̻� ó��
		switch (abnormalType) {
		case 0: {
			printblood = false;
			y = 0;
			moveSpeedX = moveSpeedZ = hitYvel = hitXvel = 0;
			onAir = false;
			abnormalCount++;
			if (abnormalStage == 0) {
				if (abnormalFrame < 3 && abnormalCount % 5 == 0) {
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
		case 50: {													//�����̵�
			if (destX < x) {
				x -= 5.f;
				if (x < destX) {
					x = destX;
				}
			}
			else if (destX > x) {
				x += 5.f;
				if (x > destX) {
					x = destX;
				}
			}

			if (destY < y) {
				y -= 5.f;
				if (y < destY) {
					y = destY;
				}
			}
			else if (destY > y) {
				y += 5.f;
				if (y > destY) {
					y = destY;
				}
			}

			if (destZ < z) {
				z -= 5.f;
				if (z < destZ) {
					z = destZ;
				}
			}
			else if (destZ > z) {
				z += 5.f;
				if (z > destZ) {
					z = destZ;
				}
			}
			if (x == destX && y == destY && z == destZ) {
				abnormalType = 9;
			}
			break;
		}
		}
	}
	if (printblood) {
		bloodframe++;
	}

	if (tick % 5 == 0 && curStatus == mon_Walk) {														//�ȱ�(�̵�)
		x += moveSpeedX;
		z += moveSpeedZ;
	}

	if (curStatus != mon_Hit && curStatus != mon_Falldown && abnormalType != 0) {
		curDir = curMap->getPlayer()->getX() > x ? true : false;
	}

	terColRect = RectMakeCenter(x, translate(z), 50, 50);
	RECT t;
	vector<MapTile> curMapTiles = curMap->getTiles();
	for (vector<MapTile>::iterator i = curMapTiles.begin(); i != curMapTiles.end(); i++) {
		if (IntersectRect(&t, &i->rc, &terColRect)) {
			if (i->type == -1) {
				int width = t.right - t.left;
				int height = t.bottom - t.top;
				if (width < height) {//x����
					if (t.right == i->rc.right&& terColRect.right > i->rc.right) {
						x = i->rc.right + 25;
					}
					else if (t.left == i->rc.left && terColRect.left < i->rc.left) {
						x = i->rc.left - 25;
					}
				}
				else { // z����
					if (t.top == i->rc.top && terColRect.top < i->rc.top) {
						z = (i->rc.top - 25) * 2;
					}
					if (t.bottom == i->rc.bottom && terColRect.bottom > i->rc.bottom) {
						z = (i->rc.bottom + 25) * 2;
					}
				}
			}
		}
	}
	if (x + 25 > curMap->getWidth()) x = curMap->getWidth() - 25;
	if (x - 25 < 0) x = 25;
	if (translate(z) + 25 > curMap->getHeight()) z = (curMap->getHeight() - 25) * 2;
	if (translate(z) - 25 < 0) z = (25) * 2;
	terColRect = RectMakeCenter(x, translate(z), 50, 50);
}

void MonsterBase::render()
{

}

void MonsterBase::renderdc()
{
}

bool MonsterBase::isdetected()
{
	if (x - probeX / 2 < curMap->getPlayer()->getX() && curMap->getPlayer()->getX() < x + probeX / 2 &&
		z - probeZ / 2 < curMap->getPlayer()->getZ() && curMap->getPlayer()->getZ() < z + probeZ / 2) {
		return true;
	}else
		return false;
}

MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}
