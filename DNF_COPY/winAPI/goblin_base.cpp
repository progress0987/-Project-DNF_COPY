#include "stdafx.h"
#include "goblin_base.h"


goblin_base::goblin_base()
{
}


goblin_base::~goblin_base()
{
}

HRESULT goblin_base::init()
{
	stat.name = "°íºí¸°";
	idlefrom = idleto = 0;
	attackfrom = 1;
	attackto = 4;
	hitfrom =hitto= 5;
	falldownfrom = 6;
	falldownto = 9;
	wakeupfrom = wakeupto = 10;
	walkfrom = 11;
	walkto = 16;
	return S_OK;
}

void goblin_base::update()
{
}

void goblin_base::render()
{
}

void goblin_base::renderdc()
{
}
