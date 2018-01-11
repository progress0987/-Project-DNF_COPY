#pragma once
#include "Skill.h"

struct flame {
	int count;
	int curFrame;
	int curStatus;					//0 - ���� 1 - �Ҹ�
	int fade;
	FLOAT x, y, z;
};

class firewave:public Skill
{
private:
	bool waveBegin;
	DWORD waveFrom;
	int numofWave;
	int curWave;
	bool head;
	list<flame> flameEffects;
public:
	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();


	firewave();
	~firewave();
};

