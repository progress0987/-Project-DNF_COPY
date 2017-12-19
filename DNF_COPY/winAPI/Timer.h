#pragma once
class Timer
{
private:
	bool isHardware;				//고성능 타이머를 지원하는지 확인용
	float timeScale;				//시간 경과량
	float timeElapsed;				//프레임당 시간경과
	__int64 curTime;				//현재의 시간
	__int64 lastTime;				//마지막 시간
	__int64 periodFreqency;			//시간 주기


	unsigned long frameRate;		//Frame Per Second
	unsigned long FPSFrameCount;	//FPS count
	float FPStimeElapsed;			//FPS 마지막 시간과 현재시간의 차이
	float worldTime;				//전체 시간경과량
public:
	HRESULT init();
	//현재 시간 계산
	void tick(float lockFPS = 0.0f);

	//현재 FPS 가져오기
	unsigned long getFrameRate(char* str = nullptr)const;

	//한 프레임당 경과시간
	float getElapsedTime()const { return timeElapsed; }

	//전체 경과 시간
	float getWorldTime() const { return worldTime; }


	Timer();
	~Timer();
};

