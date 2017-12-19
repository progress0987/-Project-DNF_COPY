#include "stdafx.h"
#include "enemyManager.h"
#include "bullets.h"


HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	for (MinionsIter = Minions.begin(); MinionsIter != Minions.end(); MinionsIter++) {

		(*MinionsIter)->update();
	}
}

void enemyManager::render()
{
	for (MinionsIter = Minions.begin(); MinionsIter != Minions.end(); MinionsIter++) {

		(*MinionsIter)->render();
	}
}


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}
