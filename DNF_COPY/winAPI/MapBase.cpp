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
			if (i->xVel != 0) i->x += i->xVel;
			i->y += 3.5f;
			i->angle += 0.3f;

			if (i->y > 0) {
				i->y = 0.f;
				i->angle = 0.f;
			}
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
}

bool MapBase::aboveItem(FLOAT x, FLOAT z)
{
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++ ) {
		if (x - 30 < i->x&&i->x < x + 30 &&
			z - 40 < i->z&&i->z < z + 30 && i->y == 0) {
			return true;
		}
	}
	return false;
}

DropItemStruct MapBase::rootItem(FLOAT x, FLOAT z)
{
	DropItemStruct t;
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); ) {
		if (x - 30 < i->x&&i->x < x + 30 &&
			z - 40 < i->z&&i->z < z + 30 && i->y == 0) {
			t = (*i);
			i = dropList.erase(i);
			break;
		}
		else i++;
	}
	return t;
}

