#pragma once
#include "Skill.h"

class releasewave :public Skill
{
	bool showEffect;
public:

	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();

	releasewave();
	~releasewave();
};

