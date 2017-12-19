#include "stdafx.h"
#include "timeManager.h"


HRESULT timeManager::init(void)
{
	timer = new Timer;
	timer->init();
	return S_OK;
}

void timeManager::release(void)
{
	if (timer != nullptr) {
		SAFE_DELETE(timer);
		timer = nullptr;
	}
}

void timeManager::update(float lock)
{
	if (timer != nullptr) {
		timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	
	string strFrame;

	SetBkColor(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 0, 0));

#ifdef _DEBUG
	if (timer != nullptr) {
		//FPS
		sprintf(str, "FPS : %d", timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
		//전체 경과시간
		sprintf(str, "worldTime : %f", timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));
		//한 프레임당 경과시간
		sprintf(str, "ElapsedTime : %f", timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	if (timer != nullptr) {
		sprintf(str, "FPS : %d", timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif//_DEBUG 프린트
}

timeManager::timeManager() :timer(NULL)
{
}


timeManager::~timeManager()
{
}
