#include "stdafx.h"
#include "Tau_Base.h"


HRESULT Tau_Base::init()
{
	MonsterBase::init();
	sprintf(stat.name,"Å¸¿ì");
	idlefrom = idleto = 0;
	attackfrom = 1;
	attackto = 7;
	hitfrom = hitto = 9;
	falldownfrom = 10;
	falldownto = 12;
	skill1from = 13;
	skill1to = 18;
	wakeupfrom = wakeupto = 19;
	walkfrom = 20;
	walkto = 27;
	skill2from = 28;
	skill2to = 31;
	y = 0;
	return S_OK;
}

HRESULT Tau_Base::init(int x, int z)
{
	return E_NOTIMPL;
}

void Tau_Base::update()
{
}

void Tau_Base::render()
{
}

void Tau_Base::renderdc()
{
}

Tau_Base::Tau_Base()
{
}


Tau_Base::~Tau_Base()
{
}
