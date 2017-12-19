#pragma once
#include <vector>


class Animation
{
public:
	typedef vector<POINT> FrameList;
	typedef vector<int> PlayList;
private:
	int				 frameNum;
	FrameList		 frameList;
	PlayList		 playList;

	int				 frameWidth;
	int				 frameHeight;

	BOOL			loop;

	float			frameUpdateSec;
	float			elapsedSec;

	DWORD			nowPlayIndex;
	BOOL			play;

public:

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	void setDefPlayFrame(BOOL reverse = FALSE,BOOL loop = FALSE);

	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);

	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline BOOL isPlay() { return play; }
	inline POINT getFramePos() { return frameList[playList[nowPlayIndex]]; }

	inline int getFrameWidth() { return frameWidth; }
	inline int getFrameHeight() { return frameHeight; }

	Animation();
	~Animation();
};

