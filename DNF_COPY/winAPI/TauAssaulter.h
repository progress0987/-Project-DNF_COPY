#pragma once
#include "Tau_Base.h"

class TauAssaulter:public Tau_Base
{
public:
	HRESULT init();
	HRESULT init(int x, int z);
	void reset(){
		x = backupx;
		z = backupz;
		stat.curHP = stat.maxHP;
		curStatus = mon_Idle;
		
	}
	void update();
	void render();
	void renderdc();
	void setAttack();
	TauAssaulter();
	~TauAssaulter();
};

