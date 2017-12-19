
#pragma once
#include "gameNode.h"
#include "Ship.h"

class BattleCruiser;

class StarcraftScene : public gameNode
{
private:
	BattleCruiser* ship;
public:
	HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	StarcraftScene();
	~StarcraftScene();
};

