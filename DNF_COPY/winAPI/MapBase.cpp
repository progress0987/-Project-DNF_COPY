#include "stdafx.h"
#include "MapBase.h"

extern struct DropItemStruct;

MapBase::MapBase()
{
	curMap = nullptr;
}


MapBase::~MapBase()
{
}

void MapBase::init()
{
}

void MapBase::update()
{
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++) {
		if (i->y < 0) {
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
		}
		else i++;
	}
	return t;
}

