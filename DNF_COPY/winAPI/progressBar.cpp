#include "stdafx.h"
#include "progressBar.h"


HRESULT progressBar::init(int x, int y, int width, int height)
{
	this->x - x;
	this->y = y;
	rcProg = RectMake(this->x, this->y, width, height);
	//progBarTop = IMAGEMANAGER->addImage("TOPBAR", "sprites/hp.bmp", this->x, this->y, width, height, true, RGB(255, 0, 255));
	//progBarBot = IMAGEMANAGER->addImage("BOTBAR", "sprites/hpbg.bmp", this->x, this->y, width, height, true, RGB(255, 0, 255));


	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	rcProg = RectMakeCenter(this->x, this->y, progBarBot->getWidth(), progBarBot->getHeight());
}

void progressBar::render()
{
	//IMAGEMANAGER->render("BOTBAR", hdc, rcProg.left + progBarBot->getWidth() / 2, rcProg.top + this->y + progBarBot->getHeight() / 2, 0, 0, width, progBarBot->getHeight());
	//IMAGEMANAGER->render("TOPBAR", hdc, rcProg.left + progBarTop->getWidth() / 2, rcProg.top + this->y + progBarTop->getHeight() / 2, 0, 0, width, progBarTop->getHeight());
}

void progressBar::setGauge(float curGauge, float maxGauge)
{
	this->width = (curGauge / maxGauge)* progBarTop->getWidth();
}

progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}
