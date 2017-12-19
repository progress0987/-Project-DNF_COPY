#pragma once
#include "gameNode.h"

class progressBar:public gameNode
{
private:

	RECT rcProg;
	int x, y;
	float width;

	image* progBarTop;
	image* progBarBot;
public:

	HRESULT init(int x, int y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();


	void setGauge(float curGauge,float maxGauge);

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	progressBar();
	~progressBar();
};

