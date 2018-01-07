#pragma once
#include "Skill.h"

struct iceNeedle {
	int id;
	int curState;			//������� 0-������ 1-���� 2-�������
	FLOAT scale;
	FLOAT x, y, z;
	DWORD begintime;
	int staytime;
	int fadetime;
	int count;
};

class icewave :public Skill
{
private:
	bool begin;
	bool head;
	DWORD waveBegin;
	int pillarcount;
	int numofpillar;
	list<iceNeedle> needles;
public:
	HRESULT init();
	void cast(FLOAT x, FLOAT y, FLOAT z);
	void update();
	void renderb();
	void renderf();

	icewave();
	~icewave();
};

