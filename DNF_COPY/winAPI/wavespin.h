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
	float zmul;//��ü ���ư��°� �̻��Ұ����
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

