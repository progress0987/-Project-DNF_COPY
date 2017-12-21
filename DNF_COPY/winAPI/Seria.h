#pragma once
#include "MapBase.h"
class Seria :public MapBase
{
private:
	FLOAT standardY;
public:
	Seria();
	~Seria();

	void init();
	void update();
	void render();
	void renderz();
	void renderdc();
	FLOAT getStandardY() { return standardY; }
};

