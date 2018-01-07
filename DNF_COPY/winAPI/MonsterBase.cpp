#include "stdafx.h"
#include "MonsterBase.h"


HRESULT MonsterBase::init()
{
	return S_OK;
}

void MonsterBase::update()
{
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
