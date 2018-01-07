#pragma once
#include "Skill.h"

struct iceNeedle {
	int id;
	int curState;			//현재상태 0-나오기 1-유지 2-사라지기
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

