#pragma once
#include "Skill.h"
class wavehold :public Skill
{
public:
	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();

	wavehold();
	~wavehold();
};

