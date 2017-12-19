#pragma once
#include "gameNode.h"
#include "bullets.h"
class ShipBase:public gameNode
{
protected:

	image* img;
	RECT rc;
	float x, y;
	float angle;
	float speed;
	float radius;
	classBullet * bul;

public:
	HRESULT init(const char* imgName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	virtual void draw();
	virtual void keyControl();
	virtual void move();
	virtual void bulletFire();
	virtual void bulletMove();
	virtual void bulletDraw();


	ShipBase();
	~ShipBase();
};

