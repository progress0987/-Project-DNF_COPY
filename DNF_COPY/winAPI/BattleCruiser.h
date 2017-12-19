#pragma once

#include "Ship.h"


class BattleCruiser:public ShipBase
{

private:
	missilePF* missilepf;
public:
	HRESULT init(const char* imgName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	virtual void keyControl();

	virtual void missileFire();
	virtual void missileMove();
	virtual void missileDraw();

	BattleCruiser();
	~BattleCruiser();
};

