#pragma once
#include "singletonBase.h"
#include <map>
//fmod.hpp 추가
#include "inc/fmod.hpp"
//라이브러리 링크
#pragma comment(lib,"lib/fmodex_vc.lib")

using namespace FMOD;

//여유분의 채널 갯수 설정(버퍼)
#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

//총 사운드 갯수
#define TOTALSOUNDBUFFER SOUNDBUFFER+EXTRACHANNELBUFFER

class soundManager:public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>Sounds;
	typedef map<string, Sound**>::iterator SoundsIter;
	typedef map<string, Sound**>Channels;
	typedef map<string, Sound**>::iterator ChannelsIter;

	System* system;
	Sound** sound;
	Channel** channel;
	Sounds totalSounds;
public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f);//볼륨은 0~1.0
	void stop(string keyNBame);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);


	soundManager();
	~soundManager();
};

