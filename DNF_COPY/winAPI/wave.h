#pragma once
#include "Skill.h"

class wave : public Skill
{
public:
	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();


	wave();
	~wave();
};

