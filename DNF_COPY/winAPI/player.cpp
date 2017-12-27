#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

//extern HDC hdc;

HRESULT player::init(void)
{
	//beginTime = GetTickCount();//프로그램 시작시간 저장 - 필요?
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

	
	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	tick++;
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
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////상태에 따른 프레임 처리


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력부분

	{
		if ((KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN)) && (curStance == stance_idle || curStance == stance_ready)) {
			if (GetTickCount() - movebegin < 300 && curMap->isRunnable()) {
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
			curDir = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			if (curStance == stance_walk || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att||curStance == stance_idle) && movestatus == 1)) {
				if (curStance == stance_idle) curStance = stance_walk;
				x -= 2;
			}
			else if (curStance == stance_run || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att) && movestatus == 2)) {
				x -= 3;
			}
			else if (curStance == stance_norm_1 || curStance == stance_norm_2 || curStance == stance_upper) {
				x -= 1;
			}
			curDir = false;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			z -= 3;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
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
				if (inputQueue.size() > 0 && inputQueue.front().key == 'Z'&&!onSkill) {
					onSkill = true;
					curStance = stance_upper;
					frame = stance_upper;
					nextStance = stance_NULL;
					inputQueue.pop_front();
				}
				//if (curStance == stance_idle || curStance == stance_ready||curStance == stance_walk) {
				//	if (inputQueue.front().key == 'X') {
				//		curStance = stance_norm_1;
				//		frame = stance_norm_1;
				//		inputQueue.pop_front();
				//	}
				//}
				//else if (curStance == stance_norm_1) {
				//	if (inputQueue.front().key == 'X'&&nextStance!=stance_norm_2) {
				//		nextStance = stance_norm_2;
				//		inputQueue.pop_front();
				//	}
				//}
				//else if (curStance == stance_norm_2&&nextStance!=stance_upper) {
				//	if (inputQueue.front().key == 'X') {
				//		nextStance = stance_norm_3;
				//		inputQueue.pop_front();
				//	}
				//}
				//else if (curStance == stance_norm_3) {
				//	nextStance = stance_NULL;
				//	inputQueue.clear();
				//}
				//if (inputQueue.size()>0&&inputQueue.front().key == 'Z'&&!onJump&&!onSkill) {
				//	onSkill = true;
				//	curStance = stance_upper;
				//	frame = stance_upper;
				//	nextStance = stance_NULL;
				//	inputQueue.pop_front();
				//}
				//if (curStance == stance_jump_up || curStance == stance_jump_down) {
				//	if (inputQueue.front().key == 'X') {
				//		curStance = stance_areal_att;
				//		frame = stance_areal_att;
				//		inputQueue.pop_front();
				//	}
				//}
			}
			else {
				inputQueue.pop_front();
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력 처리부분(공격 및 모션처리)


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
				else if (i->type == 0) {		//이동함.
					setCurScene(curMap->NextMap(i->moveindex), curMap->NextPos(i->moveindex).x, curMap->NextPos(i->moveindex).y);
					break;
				}
			}
		}
		if (x + 25 > curMap->getWidth()) x = curMap->getWidth() - 25;
		if (x - 25 < 0) x = 25;
		if (translate(z) + 25 > curMap->getHeight()) z = (curMap->getHeight() - 25) * 2;
		if (translate(z) - 25 < 0) z = (25) * 2;
		terColRect = RectMakeCenter(x, translate(z), 50, 50);
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
	char tmp[50];

	sprintf(tmp, "무기뒤_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y+translate(z)) - cam.y, curDir);

	sprintf(tmp, "캐릭터_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);

	sprintf(tmp, "무기앞_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);
}

void player::renderdc(void)
{
	Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom-cam.y);
	char t[100];
	sprintf(t, "x : %f y : %f z : %f", x, y, z);
	TextOut(hdc, 50, 100, t, strlen(t));
	sprintf(t, "cur : %i next : %i", curStance, nextStance);
	TextOut(hdc, 50, 150, t, strlen(t));
	sprintf(t, "queuesize : %d", inputQueue.size());
	TextOut(hdc, 50, 200, t, strlen(t));
}

void player::setCurScene(MapBase * map, FLOAT x, FLOAT z)
{
	curMap = map;
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

FLOAT player::translate(FLOAT zval)
{
	FLOAT transVal = zval/2;

	return transVal;
}

player::player()
{
}


player::~player()
{
}
