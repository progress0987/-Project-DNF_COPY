#include "stdafx.h"
#include "Animation.h"


Animation::Animation():frameNum(0),frameWidth(0),frameHeight(0),loop(FALSE),frameUpdateSec(0),elapsedSec(0),nowPlayIndex(0),play(FALSE)
{
}


Animation::~Animation()
{
}

HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//프레임 가로 갯수
	frameWidth = frameW;
	int frameNumWidth = totalW / frameWidth;

	//프레임 세로 갯수
	frameHeight = frameH;
	int frameNumHeight = totalH / frameHeight;

	for (int i = 0;i< frameNumHeight; i++) {
		for (int j = 0; j < frameNumWidth; j++) {
			POINT framePos;
			framePos.x = j*frameWidth;
			framePos.y = i*frameHeight;

			frameList.push_back(framePos);
		}

	}
	setDefPlayFrame();

	return S_OK;
}

void Animation::release()
{
}

void Animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//루프 여부
	this->loop = loop;

	//플레이 리스트 초기화
	playList.clear();

	if (reverse) {
		if (this->loop) {
			for (int i = 0; i < frameNum; i++) {//정방향
				playList.push_back(i);
			}
			for (int i = frameNum - 1; i > 0; i--) {
				playList.push_back(i);
			}
		}
		else {
			for (int i = 0; i < frameNum; i++) {//정방향
				playList.push_back(i);
			}
		}
	}
	else {
		if (this->loop) {
			for (int i = 0; i < frameNum; i++) {//정방향
				playList.push_back(i);
			}
			for (int i = frameNum - 1; i > 0; i--) {
				playList.push_back(i);
			}
		}
		else {
			for (int i = 0; i < frameNum; i++) {//정방향
				playList.push_back(i);
			}
		}
	}
}
//배열 애니메이션
void Animation::setPlayFrame(int * playArr, int arrLen, BOOL loop)
{

	this->loop = loop;
	playList.clear();
	for (int i = 0; i < arrLen; i++) {
		playList.push_back(playArr[i]);
	}
}
//구간 애니메이션
void Animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	this->loop = loop;
	playList.clear();
	//첫장 == 끝장 -> 1장짜리
	if (start == end) {
		playList.clear();
		stop();
		return;
	}
	//인덱스 번호가 앞이 크면 - 수정
	if (start > end) {
		if (reverse) {
			if (this->loop) {
				for (int i = start; i >= end; i++) {
					playList.push_back(i);
				}
				for (int i = end + 1; i < start; i--) {
					playList.push_back(i);
				}
			}
			else {
				for (int i = end + 1; i < start; i--) {
					playList.push_back(i);
				}
			}
		}
		else {
			if (this->loop) {
				for (int i = start; i >= end; i++) {
					playList.push_back(i);
				}
				for (int i = end + 1; i < start; i++) {
					playList.push_back(i);
				}
			}
			else {
				for (int i = start; i >= end; i++) {
					playList.push_back(i);
				}
			}
		}
	}
	else {
		if (reverse) {
			if (this->loop) {
				for (int i = start; i < end; i++) {
					playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--) {
					playList.push_back(i);
				}
			}
			else {
				for (int i = start; i < end; i++) {
					playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--) {
					playList.push_back(i);
				}
			}
		}
		else {
			if (this->loop) {
				for (int i = start; i < end; i++) {
					playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--) {
					playList.push_back(i);
				}
			}
			else {
				for (int i = start; i < end; i++) {
					playList.push_back(i);
				}
				for (int i = end - 1; i > start; i--) {
					playList.push_back(i);
				}
			}
				for (int i = start; i < end; i++) {
					playList.push_back(i);
				}
		}
	}
}

void Animation::setFPS(int framePerSec)
{
	frameUpdateSec = 1.0f/framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
	if (play) {
		elapsedSec += elapsedTime;
		//프레임을 업데이트해야하는경우
		if (elapsedSec >= frameUpdateSec) {
			elapsedSec -= frameUpdateSec;
			nowPlayIndex++;
			//끝까지 재생한 경우
			if (nowPlayIndex == playList.size()) {
				if (this->loop) nowPlayIndex = 0;
				else {
					nowPlayIndex--;
					play = FALSE;
				}
			}
		}
	}
}

void Animation::start()
{
	play = TRUE;
	nowPlayIndex = 0;
}

void Animation::stop()
{
	play = FALSE;
	nowPlayIndex = 0;
}

void Animation::pause()
{
	play = FALSE;
}

void Animation::resume()
{
	play = TRUE;
}
