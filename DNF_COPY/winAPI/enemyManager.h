#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "bullets.h"
#include <vector>
class enemyManager :public gameNode
{
private:
	typedef vector<enemy*>EnemyList;
	typedef vector<enemy*>::iterator EnemyListIter;
	EnemyList Minions;
	EnemyListIter MinionsIter;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	inline vector<enemy*>getMinionVector() { return Minions; }
	inline vector<enemy*>::iterator getMinionIter() { return MinionsIter; }


	enemyManager();
	~enemyManager();
};

