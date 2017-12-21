#pragma once
#include "MapBase.h"
class Village:public MapBase
{
private:
	int count;
	POINT furnanceLoc;
public:
	void init();
	void update();
	void render();
	void renderz();
	void renderdc();
	Village();
	~Village();
};

