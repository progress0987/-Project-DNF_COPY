#pragma once
#include "gameNode.h"

class Animation;

class Effect : public gameNode
{
protected:
	int				x;					//이펙트 좌표위치 Left
	int				y;					//이펙트 좌표위치 top

	D2DImage*		effectImage;		//이펙트 이미지
	Animation*		effectAnimation;	//이펙트 애니메이션
	BOOL			isRunning;			//이펙트 활성화 여부
	float			elapsedTime;		//이펙트 경과시간

public:

	virtual HRESULT init(D2DImage* effectImage, int frameX, int frameY, int fps, float elapsedTime);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void startEffect(int x, int y);

	virtual void killEffect(void);

	BOOL getIsRunning(void) { return isRunning; }

	Effect();
	~Effect();
};