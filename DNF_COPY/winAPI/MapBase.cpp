#include "stdafx.h"
#include "MapBase.h"

extern struct DropItemStruct;

void MapBase::drawWindow(int destX, int destY, int width, int height, int alpha)
{
	//0, 3, 6 11x, 1,4,7 - 12x, 2,5,8 - 10x

	//0,1,2 ,6,7,8 - 11y
	//3,4,5 - 13y
	FLOAT Xmul = (width - 21.f) / 12.f;					//x축으로의 확대율
	FLOAT Ymul = (height - 22.f) / 13.f;					//y축으로의 확대율

	IMAGEMANAGER->findImage("창_0")->render(destX, destY);		//왼쪽위

	IMAGEMANAGER->findImage("창_1")->scaledrender(destX + 11, destY, Xmul);

	IMAGEMANAGER->findImage("창_2")->render(destX + 12 * Xmul + 11, destY);
	//////////////////////////////////////////
	IMAGEMANAGER->findImage("창_3")->scaledrender(destX, destY + 11, 1.f, Ymul);

	IMAGEMANAGER->findImage("창_4")->scaledrender(destX + 11, destY + 11, Xmul, Ymul);//제일중요

	IMAGEMANAGER->findImage("창_5")->scaledrender(destX + 12 * Xmul + 11, destY + 11, 1.f, Ymul);
	//////////////////////////////////////////////////////////
	IMAGEMANAGER->findImage("창_6")->render(destX, destY + 13 * Ymul + 11);

	IMAGEMANAGER->findImage("창_7")->scaledrender(destX + 11, destY + 13 * Ymul + 11, Xmul);

	IMAGEMANAGER->findImage("창_8")->render(destX + 12 * Xmul + 11, destY + 13 * Ymul + 11);

}

MapBase::MapBase()
{
	curMap = nullptr;
}


MapBase::~MapBase()
{
}

HRESULT MapBase::init()
{
	d3dFont = NULL;
	if (FAILED(D3DXCreateFont(g_pd3dDevice,
		10, 0,
		FW_NORMAL,
		1,
		0,
		HANGUL_CHARSET,
		0,
		0,
		0,
		TEXT("돋움"),
		&d3dFont))) {
		return E_FAIL;
	}
	return S_OK;
}

void MapBase::update()
{
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++) {
		if (i->y < 0) {
			if (i->xVel != 0.f) i->x += i->xVel;
			if (i->zVel != 0.f) i->z += i->zVel;
			i->yVel += 0.1f;
			i->y += i->yVel;
			i->angle += 0.3f;

			if (i->y > 0) {
				i->y = 0.f;
				i->angle = 0.f;
				if (i->x > maxX) i->x = maxX - 50;
				else if (i->x < minX) i->x = minX + 50;
				if (i->z > maxZ) i->z = maxZ - 100;
				else if (i->z < minZ) i->z = minZ + 100;

			}
		}
	}
	if (monsterList.size() > 0) {
		peaceful = false;
	}
	else if(monsterList.size()==0&&!peaceful){
		peaceful = true;
		pl->setOnCombat(!peaceful);
		for (int i = 0; i < 4; i++) {
			if (!Gates[i].isShow)continue;
			Gates[i].movable = true;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (!Gates[i].movable) continue;
		POINT pt = pointMake((int)pl->getX(), translate(pl->getZ()));
		if (PtInRect(&Gates[i].moveRect, pt)) {
			pl->setCurScene(Gates[i].con.nextNode, Gates[i].con.x, Gates[i].con.z);
			break;
		}
	}
}

void MapBase::render()
{
}

void MapBase::renderz()
{
}

void MapBase::renderdc()
{
	char tmp[50];
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++) {
		int offset = -i->item.name.length() * 8;
		if (i->isGold) {
			offset = -70;
		}
		if (i->x - 30 < pl->getX() && pl->getX() < i->x + 30 &&
			i->z - 30 < pl->getZ() && pl->getZ() < i->z + 30&&!i->isGold) {
			drawWindow(i->x + offset / 2 - cam.x, i->y + translate(i->z) - 50 - cam.y, (-(offset)), 20);
		}
		if(!i->isGold)
		drawWindow(i->x + offset / 2 - cam.x, i->y + translate(i->z) - 50 - cam.y, (-(offset)), 20);
		else
		drawWindow(i->x - cam.x, i->y + translate(i->z) - 30 - cam.y, (-(offset)), 20);
		if(!i->isGold){
			sprintf(tmp, "%s", i->item.name.c_str());
			d3dFont->DrawTextA(
				NULL,
				tmp,
				-1,
				&RectMake(i->x + offset / 2 - cam.x, i->y + translate(i->z) - 50 - cam.y, (-(offset)), 20),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}else {
			sprintf(tmp, "%d 골드", i->goldamount);
			d3dFont->DrawTextA(
				NULL,
				tmp,
				-1,
				&RectMake(i->x - cam.x, i->y + translate(i->z) - 30 - cam.y, (-(offset)), 20),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}

	}
}

bool MapBase::getMove(conNode * next, FLOAT x, FLOAT z)
{
	bool ret = false;
	for (int i = 0; i < 4; i++) {
		if (!Gates[i].movable) continue;
		POINT pt = pointMake(pl->getX(), translate(pl->getZ()));
		if (PtInRect(&Gates[i].moveRect, pt)) {
			next = &Gates[i].con;
			ret = true;
			break;
		}
	}
	return ret;
}

void MapBase::resetMonsters()
{
	//if (curMap == nullptr) {
	//	monsterList.clear();
	//	for (int i = 0; i < monsterBackup.size(); i++) {
	//		monsterList.push_back(monsterBackup[i]);
	//	}
	//	peaceful = false;
	//	for (int i = 0; i < 4; i++) {
	//		Gates[i].movable = false;
	//	}
	//}
	//else {
	//	curMap->resetMonsters();
	//}
	monsterList.clear();
	for (vector<MonsterBase*>::iterator i = monsterBackup.begin(); i != monsterBackup.end(); i++) {
		(*i)->reset();
		monsterList.push_back(*i);
	}
}

int MapBase::aboveItem(FLOAT x, FLOAT z)
{
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++ ) {
		if (x - 70 < i->x&&i->x < x + 70 &&
			z - 50 < i->z&&i->z < z + 50 && i->y == 0) {
			if (i->isGold) {
				return 2;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

DropItemStruct MapBase::rootItem(FLOAT x, FLOAT z)
{
	DropItemStruct t;
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); ) {
		if (x - 70 < i->x&&i->x < x + 70 &&
			z - 50 < i->z&&i->z < z + 50 && i->y == 0) {
			t = (*i);
			i = dropList.erase(i);
			break;
		}
		else i++;
	}
	return t;
}

