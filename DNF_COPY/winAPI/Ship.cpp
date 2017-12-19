#include "stdafx.h"
#include "Ship.h"


HRESULT ShipBase::init(const char * imgName, int x, int y)
{
	img = IMAGEMANAGER->findImage(imgName);

	this->x = x;
	this->y = y;
	angle = 0.0f;
	rc = RectMakeCenter(this->x, this->y, img->getFrameWidth(), img->getFrameHeight());

	speed = 0.0f;
	radius = img->getFrameWidth()/2;

	bul = new classBullet;
	return S_OK;
}

void ShipBase::release(void)
{
}

void ShipBase::update(void)
{
	bulletMove();
	keyControl();
	move();
}

void ShipBase::render()
{
	bulletDraw();
	draw();
}

void ShipBase::draw()
{
	img->frameRender(getMemDC(), rc.left, rc.right);//디버그용

													//앵글/스피드

	char str[128];
	sprintf(str, "각도 : %d, 속도 : %3.2f", int(angle * 180 / PI), speed);
	TextOut(getMemDC(), rc.left, rc.top - 15, str, strlen(str));
}

void ShipBase::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		angle -= 0.05f;
		if (angle <= 0) angle += (PI * 2.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		angle += 0.05f;
		if (angle >=(PI*2)) angle -= (PI * 2.f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		speed += 0.02f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		speed -= 0.02f;
	}
}

void ShipBase::move()
{
	int frame;
	float ang;

	angle = ang + (PI / 16);
	if (ang >= (PI / 2))ang -= (PI / 2);
	frame = int(ang / (PI / 8));
	img->setFrameX(frame);

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * 100;

	x += cosf(angle)*speed*moveSpeed;
	y += -sinf(angle)*speed*moveSpeed;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
}

void ShipBase::bulletFire()
{
	float xd = this->x + cosf(angle) * 50;
	float yd = this->y - sinf(angle) * 50;

	bul->fire(xd, yd, angle, speed);
}

void ShipBase::bulletMove()
{
	bul->move();
}

void ShipBase::bulletDraw()
{
	bul->draw();
}

ShipBase::ShipBase()
{
}


ShipBase::~ShipBase()
{
}
