#include "stdafx.h"
#include "Skill.h"

int Skill::getremainCooldownTime()
{
	DWORD t = cooldownstartfrom + cooldownTick - GetTickCount();
	if (t < 0) {
		t = 0;
	}
	return t;
}

FLOAT Skill::getremainCooldown()
{
	DWORD t = cooldownstartfrom + cooldownTick - GetTickCount();
	if (t < 0) {
		t = 0;
	}
	return (float)t / (float)cooldownTick ;
}


HRESULT Skill::init()
{
	return E_NOTIMPL;
}

void Skill::cast(FLOAT x, FLOAT y, FLOAT z)
{
}

void Skill::update()
{
}

void Skill::renderb()
{
}
void Skill::renderf()
{
}


Skill::Skill()
{
}


Skill::~Skill()
{
}
