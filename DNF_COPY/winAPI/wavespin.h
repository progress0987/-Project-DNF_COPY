#pragma once

#include "Skill.h"

struct bead {
	FLOAT distance;
	float angle;
	FLOAT x, y, z;
	int effect;
};


class wavespin :public Skill
{
private:
	int numofbead;
	int stage;
	int stagecount;
	FLOAT skilldiameter;
	int ballHeight;
	float zmul;//구체 돌아가는게 이상할경우대비
	vector<bead> balls;
public:
	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();

	wavespin();
	~wavespin();
};

