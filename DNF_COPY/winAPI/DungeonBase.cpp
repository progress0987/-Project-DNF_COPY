#include "stdafx.h"
#include "DungeonBase.h"


HRESULT DungeonBase::init()
{
	return S_OK;
}

void DungeonBase::update()
{
}

void DungeonBase::render()
{
}

void DungeonBase::renderz()
{
}

void DungeonBase::renderdc()
{
}

void DungeonBase::resetMonsters()
{
}

DungeonBase::DungeonBase()
{
	peaceful = false;
	runnable = true;
	attackable = true;
}


DungeonBase::~DungeonBase()
{
}
