#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(const char * img, POINT position)
{
	return S_OK;
}


void enemy::release(void)
{
}

void enemy::update(void)
{
}

void enemy::render()
{
	draw();
}

void enemy::move()
{
}

void enemy::draw()
{
}

enemy::enemy()
{
}


enemy::~enemy()
{
}
