#include "stdafx.h"
#include "firewave.h"


HRESULT firewave::init()
{

	reqMana = 200;
	chargeamount = 10;
	onCooldown = false;
	cooldownTick = 5000;
	waveBegin = false;
	numofWave = 3;
	curWave = 0;


	return S_OK;
}

void firewave::cast(FLOAT x, FLOAT y, FLOAT z)
{
	flameEffects.clear();
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

void firewave::update()
{
	if (oncast) {						//������
		count++;
		if (count % 5 == 0) {
			curAction++;
			if (curAction == 35) {//����
				waveBegin = true;
				head = pl->getCurDir();
				waveFrom = GetTickCount();
				curWave = 0;
			}
			if (curAction > 41) {
				oncast = false;
			}
		}
	}
	else if (onCooldown&&cooldownstartfrom + cooldownTick<GetTickCount()) {
		onCooldown = false;
		cooldownstartfrom = 0;
	}

	if (waveBegin) {						//��ų����Ʈ
		if (curWave < numofWave&& waveFrom + curWave * 250 < GetTickCount()) {
			flame f;
			f.count = 0;
			f.curFrame = 0;
			f.curStatus = 0;
			f.x = head ? x + 50 + 90*curWave : x - 50 - 90*curWave;
			f.y = y;
			f.z = z;
			f.fade = 0xFF;
			flameEffects.push_back(f);
			curWave++;

			effectedOnTime atk;
			atk.isCrit = rand() % 100 > 70 ? true : false;
			atk.mindmg = atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 2 + pl->getWeapon().magdmgmin * 2)*1.5: (pl->getStatus().intel+pl->getStatus().a_intel)*2 + pl->getWeapon().magdmgmin*2;
			atk.maxdmg = atk.isCrit?((pl->getStatus().intel + pl->getStatus().a_intel) * 3 + pl->getWeapon().magdmgmax * 2)*1.5: (pl->getStatus().intel+pl->getStatus().a_intel)*3 + pl->getWeapon().magdmgmax*2;
			atk.isAbnormal = true;
			atk.abnormal = 10;
			atk.isHold = false;
			atk.isOnetime = true;
			atk.isProjectile = false;
			atk.area.miny = -170; atk.area.maxy = 0;
			atk.area.minz = f.z - 300; atk.area.maxz = f.z + 300;
			atk.area.maxx = head ? f.x + 300 : f.x+10;
			atk.area.minx = head ? f.x-10 : f.x - 300;
			atk.pushX = head? 1.5f : -1.5f;
			atk.pushY = -5.f;												//���� ��ų���������� ����ɷº���
			atk.staytime = 10;
			atk.time = GetTickCount();
			pl->addAttack(atk);
		}
	}
	for (list<flame>::iterator i = flameEffects.begin(); i != flameEffects.end();) {
		i->count++;
		switch (i->curStatus) {
		case 0:
			if (i->count % 5 == 0) {
				i->curFrame++;
				if (i->curFrame > 10) {
					i->curFrame = -1;
					i->curStatus = 1;
				}
			}
			i++;
			break;
		case 1:
			if (i->count > 200) {			//���� �ڱ� �����ֱ�
				i->fade--;
				if (i->fade < 0) {
					i = flameEffects.erase(i);
					break;
				}
			}
			i++;
			break;
		}
	}

}

void firewave::renderb()
{
	char tmp[50];
	if (oncast) {
		if (35 <= curAction && curAction <= 41) {
			sprintf(tmp, "�ĵ���_����_Į_ȭ��_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +250 : -250) - cam.x, y + translate(z) + 100 - cam.y, head);
			sprintf(tmp, "�ĵ���_����_Į_�ܿ�_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +250 : -250) - cam.x, y + translate(z) + 100 - cam.y, head);
			sprintf(tmp, "�ĵ���_����_Į_����_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +250 : -250) - cam.x, y + translate(z) + 100 - cam.y, head);
		}
	}

	for (list<flame>::iterator i = flameEffects.begin(); i != flameEffects.end();i++) {
		if (i->curStatus == 0) {
			sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_����");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?-20:-320) - cam.x,i->y + translate(i->z)+30 - cam.y,421,489);
			sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_ȭ��");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?-20:-320) - cam.x,i->y + translate(i->z)+23 - cam.y,408,481);
			sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_����");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x+(head?30:-245) - cam.x,i->y + translate(i->z)+30 - cam.y,502,500);
		}
		else if (i->curStatus == 1) {
			sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_����");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?-20:-320) - cam.x, i->y + translate(i->z)+30 - cam.y, 421, 489, 1.f, i->fade);
			sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_ȭ��");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?-20:-320) - cam.x, i->y + translate(i->z)+23 - cam.y, 408, 481, 1.f, i->fade);
		}
		if (0<i->curFrame&&i->curFrame<10) {
			sprintf(tmp, "�ĵ���_����_ȭ��_%d", i->curFrame);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(i->x+(head?50:-50) - cam.x, i->y + translate(i->z) -150 - cam.y, head);

			sprintf(tmp, "�ĵ���_����_����_%d", i->curFrame);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(i->x+(head?50:-50) - cam.x, i->y + translate(i->z) -150 - cam.y, head);

		}

	}
}

void firewave::renderf()
{

}

firewave::firewave()
{
}


firewave::~firewave()
{
}
