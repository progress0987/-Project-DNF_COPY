#include "stdafx.h"
#include "wavespin.h"


HRESULT wavespin::init()
{
	reqMana = 15;
	onCooldown = false;
	oncast = false;
	cooldownTick = 1000;
	zmul = 2.f / 3.f;
	numofbead = 5;
	skilldiameter = 160;
	ballHeight = -100;
	skillActive = 136;
	skillInactive = 137;
	for (int i = 0; i < numofbead; i++) {
		bead t;
		balls.push_back(t);
	}
	return S_OK;
}

void wavespin::cast(FLOAT x, FLOAT y, FLOAT z)
{
	count = framecount = 0;
	curAction = 75;
	this->x = x;
	this->y = y;
	this->z = z;
	finished = false;
	oncast = true;
	isbuff = false;
	cooldownstartfrom = GetTickCount();
	onCooldown = true;
	curcharge = 0;
	stage = stagecount = 0;
	for (int i = 0; i < 5; i++) {
		balls[i].x = x;
		balls[i].y = ballHeight;
		balls[i].z = z;
		balls[i].angle = PI * 2 / numofbead * i;
		balls[i].distance = 0;
		balls[i].effect = i;
	}
	SOUNDMANAGER->play("ĳ��_��ų_�ε�_����");
	SOUNDMANAGER->play("ĳ��_��ų����_�ε�_������_����",0.5f);
}

void wavespin::update()
{//���� - ���� �� ��� ������ ��ü����, ��ü����� �����ð��Ŀ� ���� �ൿ��
	if (!finished&&oncast) {						//������
		count++;
		effectedOnTime atk;
		switch (stage) {
		case 0:
			if (count % 8 == 0) {
				curAction++;
				if (curAction > 89) {
					curAction = 89;
					stage = 1;
					SOUNDMANAGER->play("ĳ��_��ų����_�ε�_������");
				}
				if (curAction == 77) {
					atk.mindmg = 0;
					atk.maxdmg = 0;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = true;
					atk.isAbnormal = true;
					atk.isCrit = false;
					atk.attr1 = skilldiameter;
					atk.attr2 = ballHeight;
					atk.attr3 = 6;
					atk.abnormal = 50;											//Ȧ�� ���� �غ�
					atk.area.miny = -100; atk.area.maxy = 0;
					atk.area.minz = z - 140; atk.area.maxz = z + 140;
					atk.area.maxx = x +200;
					atk.area.minx = x - 200;
					atk.pushX = 0;
					atk.pushY = 0;												//���� ��ų���������� ����ɷº���
					atk.staytime = 10;
					atk.time = GetTickCount();
					atk.effectNames.push_back("�ε�_����_ȿ��_���_");
					atk.effectNames.push_back("�ε�_����_ȿ��_");
					atk.attr4 = 6;
					pl->addAttack(atk);
				}
			}
			break;
		case 1:
			for (int i = 0; i < 5; i++) {
				if (balls[i].distance < skilldiameter) {
					balls[i].distance += 2.f;
				}
				else {
					balls[i].distance = skilldiameter;
				}
				balls[i].angle += 0.05f;
				balls[i].x =x+ balls[i].distance * cosf(balls[i].angle);
				balls[i].z =z+ balls[i].distance * sinf(balls[i].angle)*zmul;
				if(count%20==0)
					balls[i].effect++;

				if (balls[i].effect > 5)
					balls[i].effect = 0;

				if (count % 10== 0) {
					atk.isCrit = rand() % 100 > 80 ? true : false;
					atk.mindmg = atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel)*1.5f + pl->getWeapon().magdmgmin * 2)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel)*1.5f + pl->getWeapon().magdmgmin * 2;
					atk.maxdmg = atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel)*2.5f + pl->getWeapon().magdmgmax * 2)*1.5: (pl->getStatus().intel + pl->getStatus().a_intel)*2.5f + pl->getWeapon().magdmgmax * 2;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = true;
					atk.isAbnormal = false;
					atk.area.miny = -150; atk.area.maxy = -50;
					atk.area.minz = balls[i].z - 45; atk.area.maxz =balls[i]. z + 45;
					atk.area.maxx = balls[i].x + 45;
					atk.area.minx = balls[i].x - 45;
					atk.pushX = 0;
					atk.pushY = 0;												//���� ��ų���������� ����ɷº���
					atk.staytime = 2;
					atk.time = GetTickCount();
					pl->addAttack(atk);
				}
			}
			if (count % 30 == 0) {
				stagecount++;
				if (stagecount>15) {
					stage = 2;
					curAction = 159;
					stagecount = 0;
				}
			}
			break;
		case 2:
			if (count % 8 == 0) {
				curAction++;
				//if (curAction == 165) {
				//	atk.dmg = 0;
				//	atk.isOnetime = true;
				//	atk.isProjectile = false;
				//	atk.isHold = true;
				//	atk.isAbnormal = true;
				//	atk.attr1 = skilldiameter;
				//	atk.attr2 = ballHeight;
				//	atk.abnormal = 51;											//Ȧ�� ���� �غ�
				//	atk.area.miny = -150; atk.area.maxy = -50;
				//	atk.area.minz = z - 140; atk.area.maxz = z + 140;
				//	atk.area.maxx = x + 200;
				//	atk.area.minx = x - 200;
				//	atk.pushX = 0;
				//	atk.pushY = -6.f;												//���� ��ų���������� ����ɷº���
				//	atk.staytime = 10;
				//	atk.time = GetTickCount();
				//	pl->addAttack(atk);
				//}
				if (curAction == 166) {
					for (int i = 0; i < 5; i++) {
						atk.mindmg = (pl->getStatus().intel + pl->getStatus().a_intel)*4 + pl->getWeapon().magdmgmin;
						atk.maxdmg = (pl->getStatus().intel + pl->getStatus().a_intel)*4 + pl->getWeapon().magdmgmax;
						atk.isOnetime = true;
						atk.isProjectile = false;
						atk.isHold = false;
						atk.isAbnormal = true;
						atk.abnormal = 51;
						atk.area.miny = -150; atk.area.maxy = -50;
						atk.area.minz = balls[i].z - 500; atk.area.maxz = balls[i].z + 500;
						atk.area.maxx = balls[i].x + 400;
						atk.area.minx = balls[i].x - 400;
						atk.pushX = balls[i].x<x ? -4.f : 4.f;
						atk.pushY = -6.f;												//���� ��ų���������� ����ɷº���
						atk.staytime = 10;
						atk.time = GetTickCount();
						pl->addAttack(atk);
					}
					SOUNDMANAGER->play("ĳ��_��ų_�ε�_����");
					SOUNDMANAGER->play("ĳ��_��ų����_�ε�_������");
					SOUNDMANAGER->stop("ĳ��_��ų����_�ε�_������_����");
				}
				if (curAction > 175) {/*
					curAction = 175;
					stagecount++;
					if (stagecount > 5) {*/
						finished = true;
						oncast = false;
					//}
				}
			}
		}
	}
	else if (onCooldown&&cooldownstartfrom + cooldownTick<GetTickCount()) {
		onCooldown = false;
		cooldownstartfrom = 0;
	}
}

void wavespin::renderb()
{
	char tmp[100];
	int offsetx1 = -87;
	int offsetx2 = 88;
	int offsety = -67;
	if (!finished) {
		switch (stage) {
		case 0:
			//14�ܰ�
			sprintf(tmp, "�ε�_������_����Ʈ_��_%d", (count%60)/10 +2);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx1 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y, 180, 60, 1.f, 255/15* (curAction-75), true);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx2 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y,180,60,1.f,255/15* (curAction-75),false);

			IMAGEMANAGER->findImage("�ε�_������")->DFpointedcirclerender(pl->getX() - cam.x, pl->getY() + translate(pl->getZ()) - cam.y,1.0f,1.0f,255/15* (curAction-75));

			sprintf(tmp, "�ε�_������_����Ʈ_��_%d", (count % 60)/10 +2);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx1 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y, 180, 60, 1.f, 255/15* (curAction-75), true);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx2 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y,180,60,1.f,255/15* (curAction-75),false);
			break;
		case 1:

			sprintf(tmp, "�ε�_������_����Ʈ_��_%d", (count%60)/10 +2);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx1 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y, 180, 60, 1.f, 255, true);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx2 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y,180,60,1.f,255,false);

			IMAGEMANAGER->findImage("�ε�_������")->DFpointedcirclerender(pl->getX() - cam.x, pl->getY() + translate(pl->getZ()) - cam.y);

			sprintf(tmp, "�ε�_������_����Ʈ_��_%d", (count % 60)/10 +2);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx1 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y, 180, 60, 1.f, 255, true);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(pl->getX()+offsetx2 - cam.x, pl->getY() + translate(pl->getZ())+offsety - cam.y,180,60,1.f,255,false);
			break;
		case 2:
			break;
		}
	}
}

void wavespin::renderf()
{
	char tmp[100];
	if (!finished) {
		if (80 <= curAction && curAction <= 84) {
			sprintf(tmp, "�ε�_�õ�_%d", curAction - 80);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(				x -cam.x-75, y + translate(z)-210 -cam.y,0,0);
		}
		switch (stage) {
		case 1:
			for (int i = 0; i < 5; i++) {
				IMAGEMANAGER->findImage("�ε�_��ü_����")->DFpointrender(	balls[i].x -cam.x, balls[i].y + translate(balls[i].z) -cam.y,89,88);
				IMAGEMANAGER->findImage("�ε�_��ü")->DFpointrender(		balls[i].x -cam.x, balls[i].y + translate(balls[i].z) -cam.y,89,88);
				sprintf(tmp, "�ε�_��ü_ȿ��_%d", balls[i].effect);
				IMAGEMANAGER->findImage(tmp)->DFpointrender(				balls[i].x -cam.x, balls[i].y + translate(balls[i].z) -cam.y,89,88);
			}
			break;
		case 2:
			if (159 <= curAction && curAction <= 164) {
				for (int i = 0; i < 5; i++) {
					sprintf(tmp, "�ε�_�Ҹ�����Ʈ_%d", (curAction - 159)/2);
					IMAGEMANAGER->findImage(tmp)->DFpointedcirclerender(		balls[i].x -cam.x, balls[i].y + translate(balls[i].z)-50 -cam.y);
				}
			}
			else if (165 <= curAction && curAction <= 170) {
				for (int i = 0; i < 5; i++) {
					sprintf(tmp, "�ε�_����_3_%d", (curAction - 165));
					IMAGEMANAGER->findImage(tmp)->DFpointrender(balls[i].x -cam.x, balls[i].y + translate(balls[i].z) -cam.y,200,145);
					sprintf(tmp, "�ε�_����_2_%d", (curAction - 165));
					IMAGEMANAGER->findImage(tmp)->DFpointrender(balls[i].x - cam.x, balls[i].y + translate(balls[i].z) - cam.y,200,145);
					sprintf(tmp, "�ε�_����_1_%d", (curAction - 165));
					IMAGEMANAGER->findImage(tmp)->DFpointrender(balls[i].x - cam.x, balls[i].y + translate(balls[i].z) - cam.y,200,145);
				}
			}
			break;
		}
	}
}

wavespin::wavespin()
{
}


wavespin::~wavespin()
{
}
