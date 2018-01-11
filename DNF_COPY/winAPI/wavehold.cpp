#include "stdafx.h"
#include "wavehold.h"


HRESULT wavehold::init()				//여유될때 더 만들것
{
	reqMana = 15;
	onCooldown = false;
	oncast = false;
	cooldownTick = 1000;
	//zmul = 2.f / 3.f;
	return S_OK;
}

void wavehold::cast(FLOAT x, FLOAT y, FLOAT z)
{
}

void wavehold::update()
{
}

void wavehold::renderb()
{
}

void wavehold::renderf()
{
}

wavehold::wavehold()
{
}


wavehold::~wavehold()
{
}
