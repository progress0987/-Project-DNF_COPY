#pragma once
#include "gameNode.h"

class fontTest: public gameNode
{
public:
	HRESULT init(void);
	void render();


	fontTest();
	~fontTest();
};

