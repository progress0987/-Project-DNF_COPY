#include "stdafx.h"
#include "firewave.h"


HRESULT firewave::init()
{

	reqMana = 15;
	chargeamount = 10;
	onCooldown = false;
	cooldownTick = 400;
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
	if (oncast) {						//±â¼ú»ç¿ë
		count++;
		if (count % 5 == 0) {
			curAction++;
			if (curAction == 35) {//°ø°Ý
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

	if (waveBegin) {						//½ºÅ³ÀÌÆåÆ®
		if (curWave < numofWave&& waveFrom + curWave * 300 < GetTickCount()) {
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
			atk.dmg = 5;
			atk.isOnetime = true;
			atk.isProjectile = false;
			atk.area.miny = -170; atk.area.maxy = 0;
			atk.area.minz = f.z - 50; atk.area.maxz = f.z + 50;
			atk.area.maxx = f.x + 200;
			atk.area.minx = f.x ;
			atk.pushX = head? 1.5f : -1.5f;
			atk.pushY = -7.f;												//ÃßÈÄ ½ºÅ³·¹º§¿¡µû¶ó ¶ç¿ì±â´É·Âº¯°æ
			atk.staytime = 20;
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
			if (i->count > 200) {			//³²Àº ÀÚ±¹ ¾ø¾ÖÁÖ±â
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
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_Ä®_È­¿°_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +250 : -250) - cam.x, y + translate(z) + 100 - cam.y, head);
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_Ä®_ÀÜ¿µ_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +250 : -250) - cam.x, y + translate(z) + 100 - cam.y, head);
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_Ä®_¿¬±â_%d", curAction - 35);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x + (pl->getCurDir() ? +250 : -250) - cam.x, y + translate(z) + 100 - cam.y, head);
		}
	}

	for (list<flame>::iterator i = flameEffects.begin(); i != flameEffects.end();i++) {
		if (i->curStatus == 0) {
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_È­¿°_¹Ù´Ú_¿¬±â");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?0:-300) - cam.x,i->y + translate(i->z)+30 - cam.y,421,489);
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_È­¿°_¹Ù´Ú_È­¿°");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?0:-300) - cam.x,i->y + translate(i->z)+23 - cam.y,408,481);
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_È­¿°_¹Ù´Ú_Æø¹ß");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x+(head?50:-225) - cam.x,i->y + translate(i->z)+30 - cam.y,502,500);
		}
		else if (i->curStatus == 1) {
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_È­¿°_¹Ù´Ú_¿¬±â");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?0:-300) - cam.x, i->y + translate(i->z)+30 - cam.y, 421, 489, 1.f, i->fade);
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_È­¿°_¹Ù´Ú_È­¿°");
			IMAGEMANAGER->findImage(tmp)->DFpointrender(i->x + (head?0:-300) - cam.x, i->y + translate(i->z)+23 - cam.y, 408, 481, 1.f, i->fade);
		}
		if (0<i->curFrame&&i->curFrame<10) {
			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_È­¿°_%d", i->curFrame);
			IMAGEMANAGER->findImage(tmp)->DFcharpointrender(i->x+(head?50:-50) - cam.x, i->y + translate(i->z) -150 - cam.y, head);

			sprintf(tmp, "ÆÄµ¿°Ë_Æø¿°_¿¬±â_%d", i->curFrame);
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
