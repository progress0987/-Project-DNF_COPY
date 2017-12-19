#include "stdafx.h"
#include "BattleCruiser.h"


HRESULT BattleCruiser::init(const char * imgName, int x, int y)
{
	ShipBase::init(imgName, x, y);

	missilepf = new missilePF;
	missilepf->init("misslePF", 30, 600);//없는거임. 추가수정

	return S_OK;
}

void BattleCruiser::release(void)
{
	ShipBase::release();
}

void BattleCruiser::update(void)
{
	ShipBase::update();
	missileMove();
	keyControl();
}

void BattleCruiser::render()
{
	ShipBase::render();
	missileDraw();
}

void BattleCruiser::keyControl()
{
	if (KEYMANAGER->isStayKeyDown('A')) {
		angle -= 0.05f;
		if (angle <= 0) angle += (PI * 2);
	}
	if (KEYMANAGER->isStayKeyDown('D')) {
		angle += 0.05f;
		if (angle >= (PI * 2)) angle -= (PI * 2);
	}
	if (KEYMANAGER->isStayKeyDown('W')) {
		speed += 0.02f;
	}
	if (KEYMANAGER->isStayKeyDown('S')) {
		speed -= 0.02f;
	}
}

void BattleCruiser::missileFire()
{
	float xd = this->x + cosf(angle) * 50;
	float yd = this->y - sinf(angle) * 50;

	missilepf->fire(xd, yd, angle, speed);
}

void BattleCruiser::missileMove()
{
	missilepf->move();
}

void BattleCruiser::missileDraw()
{
	missilepf->draw();
}

BattleCruiser::BattleCruiser()
{
}


BattleCruiser::~BattleCruiser()
{
}
