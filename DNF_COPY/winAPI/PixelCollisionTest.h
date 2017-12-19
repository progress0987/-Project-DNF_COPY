#pragma once
#include "gameNode.h"

class PixelCollisionTest:public gameNode
{
private:
	image* ground;
	image*ball;
	RECT rc;

	float x, y;

	int probeY;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	PixelCollisionTest();
	~PixelCollisionTest();
};

