#include "stdafx.h"
#include "MonsterBase.h"




HRESULT MonsterBase::init()
{
	frame = deadcount = actionTick = curatkcooldown = 0;
	onAbnormal = isDead = onAttack = onSkill = found = onAir = onHold = printblood = bloodframe = onAbnormal = false;
	abnormalCount = abnormalFrame = abnormalStage = abnormalType = hitAvail = -1;
	hitXvel = hitYvel = hitZvel = 0.f;
	curStatus = mon_Idle;
	return S_OK;
}

void MonsterBase::update()
{
	actionTick++;
	tick++;

	//행동을 변경한다
	if (!onHold&&curStatus!= mon_onDeadProcess &&(!onSkill||!onAttack)) {
		if (actionTick > actionIndicate && !found && (curStatus != mon_Hit || curStatus != mon_Falldown || curStatus != mon_Wakeup)) {										//동작 변경
			int indicate = rand() % 80;
			
			//이동으로 변경
			if (indicate > 40) {
				curStatus = mon_Walk;
				moveSpeedX = RND->getFloat(moveSpeedMaxX) - moveSpeedMaxX / 2.f;
				moveSpeedX += moveSpeedX > 0.f ? 1.f : -1.f;
				moveSpeedZ = RND->getFloat(moveSpeedMaxZ) - moveSpeedMaxZ / 2.f;
				moveSpeedZ += moveSpeedX > 0.f ? 1.f : -1.f;
				frame = walkfrom;
				actionIndicate = rand() % 100 + 200;
			}
			//가만히 있기
			else {
				curStatus = mon_Idle;
				frame = idlefrom;
				actionIndicate = rand() % 200 + 200;
			}
			actionTick = 0;
		}
		else if (actionTick > actionIndicate && isdetected() && (curStatus ==mon_Idle||curStatus == mon_Walk)) {
			int indicate = rand() % 40;
			if (indicate > 20) {
				FLOAT plX = curMap->getPlayer()->getX();
				FLOAT plZ = curMap->getPlayer()->getZ();
				found = true;
				if (plX > x) {
					moveSpeedX = 4.f;
				}
				else if (x - 4.f <= plX && plX <= x + 4.f) {
					//x = curMap->getPlayer()->getX();
					moveSpeedX = 0.f;
				}
				else {
					moveSpeedX = -4.f;
				}

				if (plZ > z) {
					moveSpeedZ = 5.f;
				}
				else if (z - 5.f <= plZ && plZ <= z + 5.f) {
					moveSpeedZ = 0.f;
				}
				else {
					moveSpeedZ = -5.f;
				}
				curStatus = mon_Walk;
				actionIndicate = rand() % 200 + 200;
			}
			else {
				curStatus = mon_Idle;
				frame = idlefrom;
				actionIndicate = rand() % 200 + 100;
			}
			actionTick = 0;
		}
		else {
			found = false;
		}
	}

	//공격 쿨다운
	if (curatkcooldown > 0) {
		curatkcooldown -= 5;
		if (curatkcooldown <= 0) {
			curatkcooldown = 0;
			onAttack = false;
		}
	}

	//공격렉트와 충돌확인
	for (list<effectedOnTime>::iterator i = curMap->getPlayer()->getAttackQueueBegin(); i != curMap->getPlayer()->getAttackQueueEnd(); i++) {
		if (curMap->getPlayer()->getAttackQueue().size() > 0 && hitAvail) {
			if (i->area.minx < x&&x < i->area.maxx&&
				i->area.minz < z&&z < i->area.maxz&&
				i->area.miny < y &&y <= i->area.maxy) {
				float tempangle = getAngle(pl->getX(), pl->getZ(), x, z);
				curStatus = mon_Hit;
				hitAvail = false;
				printblood = true;
				onHold = i->isHold;
				frame = hitfrom;
				hitXvel = i->pushX;
				hitYvel = i->pushY;
				if (i->mindmg > 0) {////////////////////////////////////공격받았을경우 대미지가 1이상이라면
					int hitdmg = RND->getFromIntTo(i->mindmg, i->maxdmg);
					stat.curHP -= hitdmg;
					////////////////////////////////대미지 프린트할 구조체만들기
					HitQueue hit;
					hit.dmg = hitdmg;
					hit.isCrit = i->isCrit;
					hit.time = GetTickCount();
					hit.x = x;
					hit.y = y + translate(z)-100;//머리위쪽으로 출력하기위함
					hitQueue.push_back(hit);
				}
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
						if (!onAbnormal)
							abnormalFrame = 0;
						onAbnormal = true;
						break;
					case 10://화염
						if (abnormalType == 0) {
							abnormalType = -1;
							onAbnormal = false;
						}
						break;
					case 50://강제이동 - 일정거리
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
					case 51://강제이동 해제	
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
	
	//일정시간이후 다시 맞을수있음
	if (hitAvailCount + 10 < GetTickCount() && !hitAvail) {
		hitAvail = true;
	}
	
	//대미지 이미지 올라가는부분
	for (list<HitQueue>::iterator i = hitQueue.begin(); i != hitQueue.end();) {
		DWORD now = GetTickCount();
		if (now<i->time+300) {////////////////////////// 맞아서 300ms까지는 위로올라감
			i->y -= (1.f / 2.f);
		}
		else if (i->time+300<now&&now<i->time+600) {
			i->y -= (1.f / 500.f);
		}
		else if (i->time + 600 < now&&now<i->time + 900 ) {
			i->y -= (1.f / 2.f);
		}
		else if (i->time + 900 < now) {
			i=hitQueue.erase(i);
			continue;
		}
		i++;
	}

	//홀딩중이라면
	if (onHold) {
		if (tick % 10 == 0) {
			effectframe1++;
			if (effectframe1 >= effectframeMax) {
				effectframe1 = 0;
			}
		}
	}

	//공중에 떠있으면 맞는방향으로 움직임
	if (onAir) {
		onAttack = onSkill = false;
		if (curStatus != mon_Falldown) {
			frame = falldownfrom;
		}
		curStatus = mon_Falldown;
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

	//체력이 0 미만이면 사망처리
	if (stat.curHP <= 0&&y==0) {
		stat.curHP = 0;
		curStatus = mon_onDeadProcess;
	}

	//공중에 떠있을땐 쓰러지는모습
	if (y < 0 && !onHold) {
		curStatus = mon_Falldown;
	}

	//사망프로세스
	if (curStatus == mon_onDeadProcess) {
		deadcount++;
		if (deadcount >= 128) {
			//사망처리 완료
			pl->gainEXP(expamount);
			//여기서 아이템드롭!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			for (vector<Item>::iterator i = dropItems.begin(); i != dropItems.end(); i++) {
				int prob = rand() % 100;
				if (prob > 50) {
					DropItemStruct t;
	 				t.item = (*i);
					t.isGold = false;
					t.angle = 0;
					t.Tick = 0;
					t.x = x;
					t.z = z;
					t.y = -100;
					t.xVel = RND->getFromFloatTo(-1.f, 1.f);
					t.zVel = RND->getFromFloatTo(-2.f, 2.f);
					t.yVel = -3.f;
					curMap->DropItem(t);
				}
			}
			DropItemStruct t;
			t.isGold = true;
			t.goldamount = goldAmount + rand()%goldAmount-goldAmount/2;
			t.angle = 0;
			t.Tick = 0;
			t.x = x;
			t.z = z;
			t.y = -100;
			t.xVel = RND->getFromFloatTo(-1.f, 1.f);
			t.zVel = RND->getFromFloatTo(-2.f, 2.f);
			t.yVel = -3.f;
			curMap->DropItem(t);
			isDead = true;
			curStatus = mon_onDead;
		}
	}

	//맞으면 밀리는거
	if ((curStatus == mon_Hit || curStatus == mon_Falldown) && !onHold) {
		if (hitXvel != 0.f && !onAir && abnormalType != 0) {
			x += hitXvel;
			hitXvel *= 0.8f;
			if (-0.4f < hitXvel&&hitXvel < 0.4f) hitXvel = 0.f;
		}
		if (!onAir && hitXvel == 0.f) {
			if (curStatus == mon_Hit) {
				curStatus = mon_Idle;
				frame = idlefrom;
			}
		}
	}

	//상태에 따른 처리 (프레임처리)
	switch (curStatus) {																		//프레임이미지 처리부분
	case mon_Walk:
		if (tick % 15 == 0) {
			frame++;
			if (frame > walkto) {
				frame = walkfrom;
			}
		}
		break;
	case mon_Idle:
		onSkill = onAttack = false;
		if (tick % 15 == 0) {
			frame++;
			if (frame > idleto) {
				frame = idlefrom;
			}
		}
		break;
	case mon_Attack:
		if (tick % 10 == 0) {
			frame++;
			if (frame == 3) {
				setAttack();
			}
			if (frame > attackto) {
				frame = idlefrom;
				curStatus = mon_Idle;
				actionIndicate = rand() % 300 + 100;
				actionTick = 0;
			}
		}
		break;
	case mon_Hit:
		if (tick % 10 == 0) {
			frame++;
			if (frame > hitto) {
				frame = hitfrom;
			}
		}
		break;
	case mon_Falldown:
		if (tick % 15 == 0) {
			if (frame != falldownto)
				frame++;
			if (frame > falldownto) {
				frame = falldownto;			//계속 쓰러져있는 상태로 유지
			}
			if (stat.curHP > 0) {
				if (GetTickCount() % 50 == 0) {
					curStatus = mon_Wakeup;
					frame = wakeupfrom;
				}
			}
		}
		break;
	case mon_Wakeup:
		if (tick % 30 == 0) {
			frame++;
			if (frame > wakeupto) {
				curStatus = mon_Idle;
				frame = idlefrom;
			}
		}
		break;
	case mon_Skill1:
	case mon_Skill2:
	case mon_Skill3:
		//각각의 스킬당으로 프레임 정리해줘야함
		break;
	}

	//상태이상 처리
	if (onAbnormal) {
		switch (abnormalType) {
			//빙결
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
		case 50: {													//강제이동
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

	//걷기(이동)
	if (tick % 5 == 0 && curStatus == mon_Walk) {
		x += moveSpeedX;
		z += moveSpeedZ;
	}

	//플레이어를 지속적으로 바라보도록
	if (curStatus != mon_Hit && curStatus != mon_Falldown && abnormalType != 0&&!onSkill) {
		curDir = curMap->getPlayer()->getX() > x ? true : false;
	}

	//스킬들 업데이트
	onskill1();
	onskill2();
	onskill3();

	//피 출력
	if (printblood) {
		bloodframe++;
	}

	//몬스터가 화면 못벗어나게
	terColRect = RectMakeCenter(x, translate(z), 50, 50);
	RECT t;
	vector<MapTile> curMapTiles = curMap->getTiles();
	for (vector<MapTile>::iterator i = curMapTiles.begin(); i != curMapTiles.end(); i++) {
		if (IntersectRect(&t, &i->rc, &terColRect)) {
			if (i->type == -1) {
				int width = t.right - t.left;
				int height = t.bottom - t.top;
				if (width < height) {//x먼저
					if (t.right == i->rc.right&& terColRect.right > i->rc.right) {
						x = i->rc.right + 25;
					}
					else if (t.left == i->rc.left && terColRect.left < i->rc.left) {
						x = i->rc.left - 25;
					}
				}
				else { // z먼저
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

	for (vector<projectile>::iterator i = projectiles.begin(); i != projectiles.end();) {
		if (tick % 20 == 0) {
			if(i->frame>=0)
				i->frame++;
			if (i->framemax <= i->frame && i->frame>=0) {
				i->frame = 0;
			}
		}
		i->speedx += i->accelx;
		i->speedy += i->accely;
		i->speedz += i->accelz;
		i->x += i->speedx;
		i->y += i->speedy;
		i->z += i->speedz;
		i->dmginfo.area.minx = i->x - i->sizex / 2;
		i->dmginfo.area.maxx = i->x + i->sizex / 2;
		i->dmginfo.area.miny = i->y - i->sizey / 2;
		i->dmginfo.area.maxy = i->y + i->sizey / 2;
		i->dmginfo.area.minz = i->z - i->sizez / 2;
		i->dmginfo.area.maxz = i->z + i->sizez / 2;
		i->distance -= sqrt(i->speedx*i->speedx + i->speedz*i->speedz);
		if (i->distance < 0 ) {
			i = projectiles.erase(i);
		}
		else if ((i->x - i->sizex / 2 <= pl->getX() && pl->getX() <= i->x + i->sizex / 2 &&
			i->y - i->sizey / 2 <= pl->getY() && pl->getY() <= i->y + i->sizey / 2 &&
			i->z - i->sizez / 2 <= pl->getZ() && pl->getZ() <= i->z + i->sizez / 2)) {
			pl->hit(i->dmginfo);
			i = projectiles.erase(i);
		}
		else {
			i++;
		}
	}
}

void MonsterBase::render()
{
	char tmp[100];

	if (stat.curHP < stat.maxHP) {
		IMAGEMANAGER->findImage("체력바_배경")->render(x - 35 -cam.x, y + translate(z) - 100 -cam.y);
		int hp = stat.curHP > 0 ? stat.curHP : 1;
		IMAGEMANAGER->findImage("체력바_빨강")->render(x - 35 -cam.x, y + translate(z) - 100,0,0,(float)IMAGEMANAGER->findImage("체력바_빨강")->getWidth()*((float)hp/(float)stat.maxHP),(float)IMAGEMANAGER->findImage("체력바_빨강")->getHeight() -cam.y);
	}

	for (vector<projectile>::iterator i = projectiles.begin(); i != projectiles.end(); i++) {
		sprintf(tmp, "%s%d", i->imgName.c_str(), i->frame);
		IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + i->imgOffsetX - cam.x, i->y + i->imgOffsetY + translate(i->z) - cam.y, 17, 8);
	}
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

void MonsterBase::setAttack()
{
}

MonsterBase::MonsterBase()
{
}


MonsterBase::~MonsterBase()
{
}
