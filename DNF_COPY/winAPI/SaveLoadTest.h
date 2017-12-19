#pragma once

#include "gameNode.h"
class SaveLoadTest : public gameNode
{
public:
	void update();
	void save();
	void load();


	SaveLoadTest();
	~SaveLoadTest();
};

