#include "stdafx.h"
#include "Timer.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

//timeGettime함수를 사용하기위한 라이브러리 추가
//윈도우가 시작되고 난 뒤의 시간을 리턴


HRESULT Timer::init()
{
	//고성능 타이머 지원여부를 체크
	//고성능 타이머를 지원하면 초당 마이크로세컨드까지 값을 처리가능.(1/1000000)
	//
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFreqency)) {
		//64비트 정수를 사용할 수 있도록 정의한 이유는 마이크로 세컨드단위로 측정하여 조금 더 정확한 시간값을 저장하기 위함.
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

		//초당 시간 계산 범위
		timeScale = 1.0f / periodFreqency;
	}
	else {
		isHardware = false;
		//밀리세컨드 단위의 시간으로 처리 , 1/1000초
		lastTime = timeGetTime();
		timeScale = 0.001f;

	}
	frameRate = FPSFrameCount = 0;
	FPStimeElapsed = worldTime = 0.0f;

	return S_OK;
}

void Timer::tick(float lockFPS)
{
	//고성능 타이머지원
	if (isHardware) {
		//마이크로세컨드 단위로 계산 - 1/1000000 초
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	}
	else {
		//일반 밀리세컨드 단위로 계산 - 1/1000 초
		curTime = timeGetTime();
	}
	//마지막 시간과 현재시간의 경과량
	timeElapsed = (curTime - lastTime)*timeScale;

	if (lockFPS > 0.0f) {
		//고정프레임 시간을 만족할때까지 루프
		while (timeElapsed < (1.0f / lockFPS)) {
			if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			else curTime = timeGetTime();

			//마지막시간과 현재시간의 경과량
			timeElapsed = (curTime - lastTime)*timeScale;
		}
		
	}
	//마지막 시간을 기록
	lastTime = curTime;
	//자동으로 프레임카운트 증가
	FPSFrameCount++;
	//초당 프레임 시간 경과량 증가
	FPStimeElapsed += timeElapsed;
	//전체 시간 경과량 증가
	worldTime += timeElapsed;

	//프레임 초기화를 1초마다 진행
	if (FPStimeElapsed > 1.0f) {
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPStimeElapsed = 0.0f;
	}
}

//현재 fps 가져오기
unsigned long Timer::getFrameRate(char * str) const
{
	if (str != nullptr) {
		wsprintf(str, "FPS : %d", frameRate);
	}
	return frameRate;
}

Timer::Timer()
{
}


Timer::~Timer()
{
}
