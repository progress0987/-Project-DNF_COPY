#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

//extern HDC hdc;

HRESULT player::init(void)
{
	beginTime = GetTickCount();//프로그램 시작시간 저장
	temp = 176;
	x = WINSIZEX / 2;
	y = 0;
	z = (WINSIZEY - 50)*2;
	curStance = stance_idle;

	
	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	tick++;
	switch (curStance) {
	case stance_idle:
		if (tick % 25 == 0) {
			temp++;
			if (temp > 179) {
				temp = 176;
			}
		}
		break;
	case stance_walk:
		if (tick % 20 == 0) {
			temp++;
			if (temp > 187) {
				temp = 180;
			}
		}
		break;
	case stance_run:
		break;
	case stance_ready:
		break;
	case stance_hit:
		break;
	case stance_jump:
		break;
	case stance_norm_1:
		break;
	case stance_norm_2:
		break;
	case stance_upper:
		break;

	}
	if ((KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN)) && curStance == stance_idle) {
		curStance = stance_walk;
		temp = 180;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		curStance = stance_walk;
		x += 2;
		curDir = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		curStance = stance_walk;
		x -= 2;
		curDir = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		curStance = stance_walk;
		z -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		curStance = stance_walk;
		z += 3;
	}
	if ((!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN))&&(curStance!=stance_idle)) {
		curStance = stance_idle;
		temp = 176;
	}

	//플레이어  지형충돌렉트 생성
	terColRect = RectMakeCenter(x, (y + translate(z)), 50, 50);
	/////////////////////////////////////////////////위치보정
	RECT t;
	vector<MapTile> curMapTiles = curMap->getTiles();
	for (vector<MapTile>::iterator i = curMapTiles.begin(); i != curMapTiles.end(); i++) {
		if (IntersectRect(&t, &i->rc, &terColRect)&&i->type==-1) {
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
				if (t.top == i->rc.top && terColRect.top<i->rc.top) {
					z = (i->rc.top - 25) * 2;
				}
				if (t.bottom == i->rc.bottom && terColRect.bottom>i->rc.bottom) {
					z = (i->rc.bottom + 25) * 2;
				}
			}
		}
	}
	if (x + 25 > curMap->getWidth()) x = curMap->getWidth() - 25;
	if (x - 25 < 0) x = 25;
	if (translate(z) + 25 > curMap->getHeight()) z = (curMap->getHeight() - 25) * 2;
	if (translate(z) - 25 < 0 ) z = (25) * 2;
	terColRect = RectMakeCenter(x, (y + translate(z)), 50, 50);
}

void player::render(void)
{
	char tmp[50];
	HBRUSH brush;

	sprintf(tmp, "무기뒤_%d", temp);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam->x, (y+translate(z)) - cam->y, curDir);

	sprintf(tmp, "캐릭터_%d", temp);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam->x, (y + translate(z)) - cam->y, curDir);

	sprintf(tmp, "무기앞_%d", temp);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam->x, (y + translate(z)) - cam->y, curDir);
	//sprintf(tmp, "무기앞오라_%d", temp);
	//IMAGEMANAGER->findImage(tmp)->render(100, 100);
	//sprintf(tmp, "무기앞_%d", temp);
	//IMAGEMANAGER->findImage(tmp)->render(100, 100);

}

void player::renderdc(void)
{
	Rectangle(hdc, terColRect.left, terColRect.top, terColRect.right, terColRect.bottom);
	char t[100];
	sprintf(t, "x : %f y : %f z : %f", x, y, z);
	TextOut(hdc, 50, 100, t, strlen(t));
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
