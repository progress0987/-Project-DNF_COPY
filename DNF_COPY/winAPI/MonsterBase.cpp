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

	//�ൿ�� �����Ѵ�
	if (!onHold&&curStatus!= mon_onDeadProcess &&(!onSkill||!onAttack)) {
		if (actionTick > actionIndicate && !found && (curStatus != mon_Hit || curStatus != mon_Falldown || curStatus != mon_Wakeup)) {										//���� ����
			int indicate = rand() % 80;
			
			//�̵����� ����
			if (indicate > 40) {
				curStatus = mon_Walk;
				moveSpeedX = RND->getFloat(moveSpeedMaxX) - moveSpeedMaxX / 2.f;
				moveSpeedX += moveSpeedX > 0.f ? 1.f : -1.f;
				moveSpeedZ = RND->getFloat(moveSpeedMaxZ) - moveSpeedMaxZ / 2.f;
				moveSpeedZ += moveSpeedX > 0.f ? 1.f : -1.f;
				frame = walkfrom;
				actionIndicate = rand() % 100 + 200;
			}
			//������ �ֱ�
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

	//���� ��ٿ�
	if (curatkcooldown > 0) {
		curatkcooldown -= 5;
		if (curatkcooldown <= 0) {
			curatkcooldown = 0;
			onAttack = false;
		}
	}

	//���ݷ�Ʈ�� �浹Ȯ��
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
				if (i->mindmg > 0) {////////////////////////////////////���ݹ޾������ ������� 1�̻��̶��
					int hitdmg = RND->getFromIntTo(i->mindmg, i->maxdmg);
					stat.curHP -= hitdmg;
					////////////////////////////////����� ����Ʈ�� ����ü�����
					HitQueue hit;
					hit.dmg = hitdmg;
					hit.isCrit = i->isCrit;
					hit.time = GetTickCount();
					hit.x = x;
					hit.y = y + translate(z)-100;//�Ӹ��������� ����ϱ�����
					hitQueue.push_back(hit);
					if (!SOUNDMANAGER->isPlaySound(hitSound)) {
						SOUNDMANAGER->play(hitSound);
					}
				}
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
	
	//�����ð����� �ٽ� ����������
	if (hitAvailCount + 10 < GetTickCount() && !hitAvail) {
		hitAvail = true;
	}
	
	//����� �̹��� �ö󰡴ºκ�
	for (list<HitQueue>::iterator i = hitQueue.begin(); i != hitQueue.end();) {
		DWORD now = GetTickCount();
		if (now<i->time+300) {////////////////////////// �¾Ƽ� 300ms������ ���οö�
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

	//Ȧ�����̶��
	if (onHold) {
		if (tick % 10 == 0) {
			effectframe1++;
			if (effectframe1 >= effectframeMax) {
				effectframe1 = 0;
			}
		}
	}

	//���߿� �������� �´¹������� ������
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

	//ü���� 0 �̸��̸� ���ó��
	if (stat.curHP <= 0&&y==0) {
		stat.curHP = 0;
		curStatus = mon_onDeadProcess;
	}

	//���߿� �������� �������¸��
	if (y < 0 && !onHold) {
		curStatus = mon_Falldown;
	}

	//������μ���
	if (curStatus == mon_onDeadProcess) {
		deadcount++;
		if (deadcount >= 128) {
			//���ó�� �Ϸ�
			SOUNDMANAGER->play(deadSound);
			pl->gainEXP(expamount);
			//���⼭ �����۵��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

	//������ �и��°�
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

	//���¿� ���� ó�� (������ó��)
	switch (curStatus) {																		//�������̹��� ó���κ�
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
				frame = falldownto;			//��� �������ִ� ���·� ����
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
		//������ ��ų������ ������ �����������
		break;
	}

	//�����̻� ó��
	if (onAbnormal) {
		switch (abnormalType) {
			//����
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

	//�ȱ�(�̵�)
	if (tick % 5 == 0 && curStatus == mon_Walk) {
		x += moveSpeedX;
		z += moveSpeedZ;
	}

	//�÷��̾ ���������� �ٶ󺸵���
	if (curStatus != mon_Hit && curStatus != mon_Falldown && abnormalType != 0&&!onSkill) {
		curDir = curMap->getPlayer()->getX() > x ? true : false;
	}

	//��ų�� ������Ʈ
	onskill1();
	onskill2();
	onskill3();

	//�� ���
	if (printblood) {
		bloodframe++;
	}

	//���Ͱ� ȭ�� �������
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
		IMAGEMANAGER->findImage("ü�¹�_���")->render(x - 35 -cam.x, y + translate(z) - 100 -cam.y);
		int hp = stat.curHP > 0 ? stat.curHP : 1;
		IMAGEMANAGER->findImage("ü�¹�_����")->render(x - 35 -cam.x, y + translate(z) - 100,0,0,(float)IMAGEMANAGER->findImage("ü�¹�_����")->getWidth()*((float)hp/(float)stat.maxHP),(float)IMAGEMANAGER->findImage("ü�¹�_����")->getHeight() -cam.y);
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
