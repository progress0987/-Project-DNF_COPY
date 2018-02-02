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
	MonsterBase::init();
	sprintf(stat.name,"고블린");
	idlefrom = idleto = 0;
	attackfrom = 1;
	attackto = 4;
	hitfrom =hitto= 5;
	falldownfrom = 6;
	falldownto = 9;
	wakeupfrom = wakeupto = 10;
	walkfrom = 11;
	walkto = 16;
	y = 0;
	deadSound = "몬스터_고블린_사망";
	hitSound = "몬스터_고블린_피격";
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
