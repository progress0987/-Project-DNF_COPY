#pragma once
#include "gameNode.h"
class selectScene:public gameNode
{
public:
	selectScene();
	~selectScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};

