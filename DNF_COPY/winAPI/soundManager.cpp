#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:system(NULL),sound(NULL),channel(NULL)
{
}


soundManager::~soundManager()
{
}

HRESULT soundManager::init(void)
{
	//FMOD 사운드 엔진을 쓰겠다고 선언
	System_Create(&system);

	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	sound = new Sound*[TOTALSOUNDBUFFER];
	channel = new Channel*[TOTALSOUNDBUFFER];
	memset(sound, 0, sizeof(Sound*)*(TOTALSOUNDBUFFER));
	memset(channel, 0, sizeof(Sound*)*(TOTALSOUNDBUFFER));

	return S_OK;
}

void soundManager::release(void)
{
	SAFE_DELETE_ARRAY(sound);
	SAFE_DELETE_ARRAY(channel);
	system->release();
}

void soundManager::update(void)
{
	system->update();
}
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop) {
		if (bgm) {
			system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &sound[totalSounds.size()]);
		}
		else {
			system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &sound[totalSounds.size()]);
		}
	}
	else {
		if (bgm) {
			system->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &sound[totalSounds.size()]);
		}
		else {
			system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &sound[totalSounds.size()]);
		}
	}
	totalSounds.insert(make_pair(keyName, &sound[totalSounds.size()]));
}

void soundManager::play(string keyName, float volume)
{
	SoundsIter iter = totalSounds.begin();
	int count = 0;

	for (; iter != totalSounds.end();count++, iter++) {
		if (keyName == iter->first) {
			system->playSound(FMOD_CHANNEL_FREE, *(iter->second)/*sound[count]*/, false, &channel[count]);

			channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	SoundsIter iter = totalSounds.begin();
	int count = 0;

	for (; iter != totalSounds.end();count++, iter++) {
		if (keyName == iter->first) {
			channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	SoundsIter iter = totalSounds.begin();
	int count = 0;

	for (; iter != totalSounds.end();count++, iter++) {
		if (keyName == iter->first) {
			channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	SoundsIter iter = totalSounds.begin();
	int count = 0;

	for (; iter != totalSounds.end();count++, iter++) {
		if (keyName == iter->first) {
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay=false;
	SoundsIter iter = totalSounds.begin();
	int count = 0;

	for (; iter != totalSounds.end();count++, iter++) {
		if (keyName == iter->first) {
			channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPlay = true;
	SoundsIter iter = totalSounds.begin();
	int count = 0;

	for (; iter != totalSounds.end(); count++, iter++) {
		if (keyName == iter->first) {
			channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return !isPlay;
}
