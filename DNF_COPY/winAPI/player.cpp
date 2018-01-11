#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

//extern HDC hdc;

HRESULT player::init(void)
{
	Time = 0;
	frame = 176;
	x = curMap->getWidth() / 2;
	y = 0;
	z = (curMap->getHeight() - 50)*2;
	curStance = stance_idle;
	onDebug = onJump = onSkill = false;
	ui = new UI;
	ui->init();
	ui->linkPlayer(this);
	movebegin = 0;
	setOnCombat(!curMap->isPeaceful());
	Item* wep = new Item;
	wep->reachx = 180;
	wep->reachz = 150;
	Weapon = wep;
	curSkill = nullptr;

	setSkills();
	test = false;
	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	tick++;
	Time++;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////상태에 따른 프레임 처리
	switch (curStance) {
	case stance_idle:
		if (tick % 30 == 0) {
			frame++;
			if (frame > 179) {
				frame = 176;
			}
		}
		break;
	case stance_walk:
		if (tick % 15 == 0) {
			frame++;
			if (frame > 187) {
				frame = stance_walk;
			}
		}
		break;
	case stance_run:
		if (tick % 15 == 0) {
			frame++;
			if (frame > 112) {
				frame = stance_run;
			}
		}
		break;
	case stance_ready:
		if (tick % 15 == 0) {
			frame++;
			if (frame > 95) {
				frame = stance_ready;
			}
		}
		break;
	case stance_hit:
		break;
	case stance_jump_up:
		if (tick % 30 == 0) {
		frame++;
		if (frame > 127) {
			frame = 127;
		}
	}
	break;
	case stance_jump_down:
		if (tick % 30 == 0) {
			frame++;
			if (frame > 132) {
				frame = 132;
			}
		}
		break;
	case stance_norm_1:
		if (tick % 5 == 0) {
			frame++;
			if (frame > 8) {
				if (nextStance < 0) {
					curStance = stance_ready;
					frame = stance_ready;
				}
				else {
					curStance = nextStance;
					frame = nextStance;
					nextStance = stance_NULL;
				}
			}
		}
		break;
	case stance_norm_2:
		if (tick % 5 == 0) {
			frame++;
			if (frame > 20) {
				if (nextStance < 0) {
					curStance = stance_ready;
					frame = stance_ready;
				}
				else {
					curStance = nextStance;
					frame = nextStance;
					nextStance = stance_NULL;
				}
			}
		}
		break;
	case stance_norm_3:
		if (tick % 5 == 0) {
			frame++;
			if (frame > 41) {
				//if (nextStance < 0) {
				curStance = stance_ready;
				frame = stance_ready;
				nextStance = stance_NULL;
				//}
				//else {
				//	curStance = nextStance;
				//	frame = nextStance;
				//}
			}
		}
		break;
	case stance_upper:
		if (tick % 5 == 0) {
			frame++;
			if (frame > 50) {
				//if (nextStance < 0) {
				curStance = stance_ready;
				frame = stance_ready;
				nextStance = stance_NULL;
				onSkill = false;
				//}
				//else {
				//	curStance = nextStance;
				//	frame = nextStance;
				//}
			}
		}
		break;
	case stance_areal_att:
		if (tick % 10 == 0) {
			frame++;
			if (frame > 137) {
				if (jumpPow > 0) {
					curStance = stance_jump_down;
				}
				else {
					curStance = stance_jump_up;
				}
				nextStance = stance_NULL;
				//frame = stance_jump_down -1;
			}
		}
		break;
	case stance_onSkill:
		//스킬로부터 프레임을 받아와야한다.

		if (!curSkill->oncast) { curStance = stance_ready; frame = stance_ready; curSkill = nullptr; }
		else { frame = curSkill->getCurAction(); }
		break;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////상태에 따른 프레임 처리


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////각 스킬들 업데이트
	updateSkills();




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////평타에따라 대미지 포인트 만들어주기
	if(onAttack){
		effectedOnTime atk;
		switch (curStance) {
		case stance_norm_1:
			if (frame == 3) {
				atk.dmg = 5;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.area.miny = -50; atk.area.maxy = 0;
				atk.area.minz = z - Weapon->reachz; atk.area.maxz = z + Weapon->reachz;
				atk.area.maxx = curDir ? x + Weapon->reachx : x+50;
				atk.area.minx = curDir ? x-50 : x - Weapon->reachx;
				atk.pushX = curDir ? 3.f : -3.f;
				atk.pushY = 0.f;
				atk.staytime = 15;
				atk.time = Time;
				atk.time = GetTickCount();
				attackQueue.push_back(atk);
			}
			break;
		case stance_norm_2:
			if (frame == 12) {
				atk.dmg = 5;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.area.miny = -50; atk.area.maxy = 0;
				atk.area.minz = z - Weapon->reachz; atk.area.maxz = z + Weapon->reachz;
				atk.area.maxx = curDir ? x + Weapon->reachx : x - 10;
				atk.area.minx = curDir ? x + 10 : x - Weapon->reachx;
				atk.pushX = curDir ? 3.f : -3.f;
				atk.pushY = 0.f;
				atk.staytime = 15;
				atk.time = Time;
				atk.time = GetTickCount();
				attackQueue.push_back(atk);
			}
			break;
		case stance_norm_3:
			if (frame == 35) {
				atk.dmg = 5;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.area.miny = -100; atk.area.maxy = 0;
				atk.area.minz = z - Weapon->reachz/2; atk.area.maxz = z + Weapon->reachz/2;
				atk.area.maxx = curDir ? x + Weapon->reachx : x - 10;
				atk.area.minx = curDir ? x + 10 : x - Weapon->reachx;
				atk.pushX = curDir ? 1.f : -1.f;
				atk.pushY = -5.f;												//추후 스킬레벨에따라 띄우기능력변경
				atk.staytime = 15;
				atk.time = Time;
				atk.time = GetTickCount();
				attackQueue.push_back(atk);
			}
			break;
		case stance_areal_att:
			if (frame == 134) {
				atk.dmg = 5;
				atk.isOnetime = true;
				atk.isProjectile = false;
				atk.area.miny = y -100; atk.area.maxy = y+30;
				atk.area.minz = z - Weapon->reachz/2; atk.area.maxz = z + Weapon->reachz/2;
				atk.area.maxx = curDir ? x + Weapon->reachx : x - 10;
				atk.area.minx = curDir ? x + 10 : x - Weapon->reachx;
				atk.pushX = curDir ? 1.f : -1.f;
				atk.pushY = 0;
				atk.staytime = 15;
				atk.time = Time;
				atk.time = GetTickCount();
				attackQueue.push_back(atk);											//추후 스킬레벨에따라 띄우기능력변경

			}
			break;
		}
	}

	for (list<effectedOnTime>::iterator i = attackQueue.begin(); i != attackQueue.end();) {
		if (i->time + i->staytime < GetTickCount())i = attackQueue.erase(i);
		else { i++; }
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 평타에따라 대미지 포인트 만들어주기



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력부분
	{
		if ((KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN)) && (curStance == stance_idle || curStance == stance_ready)) {
			if (GetTickCount() - movebegin < 400 && curMap->isRunnable()) {
				curStance = stance_run;
				movestatus = 2;
				frame = 105;
			}
			if (curStance == stance_idle || curStance == stance_ready) {
				curStance = stance_walk;
				movestatus = 1;
				movebegin = GetTickCount();
				frame = 180;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			if (curStance == stance_walk || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att || curStance == stance_idle) && movestatus == 1)) {
				if (curStance == stance_idle) curStance = stance_walk;
				x += 2;
			}
			else if (curStance == stance_run || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att) && movestatus == 2)) {
				x += 3;
			}
			else if (curStance == stance_norm_1 || curStance == stance_norm_2 || curStance == stance_upper) {
				x += 1;
			}
			if(curStance == stance_walk||curStance == stance_idle||curStance == stance_run||curStance == stance_ready)
			curDir = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (curStance == stance_walk || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att||curStance == stance_idle) && movestatus == 1)) {
				if (curStance == stance_idle)  curStance = stance_walk;
				x -= 2;
			}
			else if (curStance == stance_run || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att) && movestatus == 2)) {
				x -= 3;
			}
			else if (curStance == stance_norm_1 || curStance == stance_norm_2 || curStance == stance_upper) {
				x -= 1;
			}
			if(curStance == stance_walk||curStance == stance_idle||curStance == stance_run || curStance == stance_ready)
			curDir = false;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			if(curStance == stance_walk ||curStance == stance_run|| curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att)
			z -= 3;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			if(curStance == stance_walk ||curStance == stance_run|| curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att)
			z += 3;
		}
		if ((!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN)) && (curStance == stance_walk || curStance == stance_run)) {
			if (!curMap->isPeaceful()) {
				curStance = stance_ready;
				frame = 90;
			}
			else {
				curStance = stance_idle;
				frame = 176;
			}
			movestatus = 0;
		}


		if (KEYMANAGER->isOnceKeyDown('X')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'X';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('Z')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'Z';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('A')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'A';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('S')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'S';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('D')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'D';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}if (KEYMANAGER->isOnceKeyDown('F')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'F';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('G')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'G';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('Q')) {
			if (curMap->isAttackable()) {
				inputStruct t;
				t.key = 'Q';
				t.time = GetTickCount();
				inputQueue.push_back(t);
			}
		}
		if (KEYMANAGER->isOnceKeyDown('C')) {
			if (curMap->isRunnable()) {
				if (curStance == stance_walk || curStance == stance_run || curStance == stance_idle || curStance == stance_ready) {
					curStance = stance_jump_up;
					frame = 125;
					onJump = true;
					jumpPow = -4.5f;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			onDebug = !onDebug;
		}
		//if (KEYMANAGER->isOnceKeyDown('V')) {
		//	test = !test;
		//}
		//if (test) {
		//	if (GetTickCount() % 100 == 0) {
		//		inputStruct t;
		//		t.key = 'Z';
		//		t.time = GetTickCount();
		//		inputQueue.push_back(t);
		//	}
		//}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력부분

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력 처리부분(공격 및 모션처리)
	{
		if (inputQueue.size() > 0) {
			if (inputQueue.front().time + KEYDELAY > GetTickCount()) {
				if (inputQueue.front().key == 'X') {
					if ((curStance == stance_idle||curStance == stance_ready||curStance == stance_walk)&&curMap->isAttackable()) {
						onAttack = true;
						curStance = stance_norm_1;
						frame = stance_norm_1;
						nextStance = stance_NULL;
						inputQueue.pop_front();
					}
					else if (curStance == stance_norm_1) {
						nextStance = stance_norm_2;
						inputQueue.pop_front();
					}
					else if (curStance == stance_norm_2) {
						nextStance = stance_norm_3;
						inputQueue.pop_front();
					}
					else if(curStance == stance_jump_up||curStance == stance_jump_down){
						curStance = stance_areal_att;
						frame = stance_areal_att;
						inputQueue.pop_front();
					}
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'Z'&&curStance!=stance_onSkill&&!onJump && !skill_upper->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_upper;
					skill_upper->cast(x, y, z);
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'A'&&curStance!=stance_onSkill&&!onJump && !skill_wave->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_wave;
					skill_wave->cast(x, y, z);
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'S'&&curStance!=stance_onSkill&&!onJump && !skill_icewave->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_icewave;
					skill_icewave->cast(x, y, z);
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'D'&&curStance != stance_onSkill && !onJump && !skill_firewave->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_firewave;
					skill_firewave->cast(x, y, z);
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'F'&&curStance != stance_onSkill && !onJump && !skill_vacslash->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_vacslash;
					skill_vacslash->cast(x, y, z);
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'G'&&curStance != stance_onSkill && !onJump && !skill_wavespin->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_wavespin;
					skill_wavespin->cast(x, y, z);
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'Q'&&curStance != stance_onSkill && !onJump && !skill_releasewave->onCooldown) {
					curStance = stance_onSkill;
					curSkill = skill_releasewave;
					skill_releasewave->cast(x, y, z);
					inputQueue.pop_front();
				}
			}
			else {
				inputQueue.pop_front();
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////점프처리부분
	if (onJump) {
		jumpPow += 0.07f;
		y += jumpPow;
	}
	if (curStance == stance_jump_up) {
		if (jumpPow > 0) {
			frame = 127;
			curStance = stance_jump_down;
		}
	}
	if (curStance == stance_jump_down) {
		if (y > 0) {
			y = 0;
			onJump = false;
			if (curMap->isPeaceful()) {
				curStance = stance_idle;
				frame = 176;
				if (movestatus == 1) {
					curStance = stance_walk;
					frame = 180;
				}
				else if (movestatus == 2) {
					curStance = stance_run;
					frame = 105;
				}
			}
			else {
				curStance = stance_ready;
				frame = 90;
				if (movestatus == 1) {
					curStance = stance_walk;
					frame = 180;
				}
				else if (movestatus == 2) {
					curStance = stance_run;
					frame = 105;
				}
			}
		}
	}
	if (curStance == stance_areal_att) {
		if (y > 0) {
			y = 0;
			onJump = false;
			if (curMap->isPeaceful()) {
				curStance = stance_idle;
				frame = 176;
				if (movestatus == 1) {
					curStance = stance_walk;
					frame = 180;
				}
				else if (movestatus == 2) {
					curStance = stance_run;
					frame = 105;
				}
			}
			else {
				curStance = stance_ready;
				frame = 90;
				if (movestatus == 1) {
					curStance = stance_walk;
					frame = 180;
				}
				else if (movestatus == 2) {
					curStance = stance_run;
					frame = 105;
				}
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////위치보정,충돌
	if (!onDebug) {
		//플레이어  지형충돌렉트 생성
		terColRect = RectMakeCenter(x, translate(z), 50, 30);
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
							z = (i->rc.top - 15) * 2;
						}
						if (t.bottom == i->rc.bottom && terColRect.bottom > i->rc.bottom) {
							z = (i->rc.bottom + 15) * 2;
						}
					}
				}
				else if (i->type == 0) {		//이동함.
					setCurScene(curMap->NextMap(i->moveindex), curMap->NextPos(i->moveindex).x, curMap->NextPos(i->moveindex).y);
					break;
				}
			}
		}
		if (x + 25 > curMap->getWidth()) x = curMap->getWidth() - 25;
		if (x - 25 < 0) x = 25;
		if (translate(z) + 15 > curMap->getHeight()) z = (curMap->getHeight() - 15) * 2;
		if (translate(z) - 15 < 0) z = (15) * 2;
		terColRect = RectMakeCenter(x, translate(z), 50, 30);
		if (y > 0) {
			y = 0;
			jumpPow = 0;
			onJump = false;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////위치보정,충돌


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////카메라 처리 부분
	cam.x = x - WINSIZEX / 2;
	cam.y = translate(z) - WINSIZEY / 2;
	if (cam.x + WINSIZEX > curMap->getWidth()) cam.x = curMap->getWidth() - WINSIZEX;
	if (cam.x < 0)cam.x = 0;
	if (cam.y + WINSIZEY > curMap->getHeight()) cam.y = curMap->getHeight() - WINSIZEY;
	if (cam.y < 0) cam.y = 0;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////카메라 처리 부분

	ui->update();
}

void player::render(void)
{
	printSkillb();
	char tmp[50];
	//sprintf(tmp, "무기뒤오라_%d", frame);
	//IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y+translate(z)) - cam.y, curDir);

	sprintf(tmp, "무기뒤_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);

	sprintf(tmp, "캐릭터_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);

	//sprintf(tmp, "무기앞오라_%d", frame);
	//IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);

	sprintf(tmp, "무기앞_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);
	printSkillf();
}

void player::renderdc(void)
{
	//Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom-cam.y);
	char t[100];
	sprintf(t, "x : %f y : %f z : %f", x, y, z);
	TextOut(hdc, 50, 100, t, strlen(t));

	POINT tmp;
	tmp.x = ptMouse.x + cam.x;
	tmp.y = ptMouse.y + cam.y;
	sprintf(t, "x : %i y : %i", tmp.x, tmp.y);
	TextOut(hdc, 50, 150, t, strlen(t));
	sprintf(t, "queuesize : %d", inputQueue.size());
	TextOut(hdc, 50, 200, t, strlen(t));

	//대미지 렉트 그려주기
	for (list<effectedOnTime>::iterator i = attackQueue.begin(); i != attackQueue.end(); i++) {
		Rectangle(hdc, i->area.minx - cam.x, translate(i->area.minz)+y - cam.y, i->area.maxx -cam.x, translate(i->area.maxz)+y - cam.y);
	}

}

void player::setCurScene(MapBase * map, FLOAT x, FLOAT z)
{
	if (map->getCurMap() != NULL) {
		curMap = map->getCurMap();
	}
	else {
		curMap = map;
	}
	this->x = x;
	this->y = 0;
	this->z = z;
}

void player::setOnCombat(bool oncombat)
{
	if (oncombat) {
		curStance = stance_ready;
		frame = 90;
	}
	else {
		curStance = stance_idle;
		frame = 176;
	}
}

void player::setSkills()
{
	skill_upper = new upper;
	skill_upper->init();
	skills.push_back(skill_upper);

	skill_wave = new wave;
	skill_wave->init();
	skills.push_back(skill_wave);

	skill_icewave = new icewave;
	skill_icewave->init();
	skills.push_back(skill_icewave);

	skill_firewave = new firewave;
	skill_firewave->init();
	skills.push_back(skill_firewave);

	skill_vacslash = new vacslash;
	skill_vacslash->init();
	skills.push_back(skill_vacslash);

	skill_releasewave = new releasewave;
	skill_releasewave->init();
	skills.push_back(skill_releasewave);
	
	skill_wavespin = new wavespin;
	skill_wavespin->init();
	skills.push_back(skill_wavespin);
}

void player::updateSkills()
{
	for (vector<Skill*>::iterator i = skills.begin(); i != skills.end(); i++)
	{
		(*i)->update();
	}
}

void player::printSkillb()
{
	for (vector<Skill*>::iterator i = skills.begin(); i != skills.end(); i++)
	{
		(*i)->renderb();
	}
}

void player::printSkillf()
{
	for (vector<Skill*>::iterator i = skills.begin(); i != skills.end(); i++)
	{
		(*i)->renderf();
	}
}



player::player()
{
	x = y = z = 0.0f;
}


player::~player()
{
}

