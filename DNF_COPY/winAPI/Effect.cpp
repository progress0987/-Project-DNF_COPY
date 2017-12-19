#include "stdafx.h"
#include "Effect.h"


HRESULT Effect::init(D2DImage * effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	if (!effectImage) return E_FAIL;

	isRunning = false;
	this->effectImage = effectImage;
	this->elapsedTime = elapsedTime;

	if (!effectAnimation) effectAnimation = new Animation;

	effectAnimation->init(effectImage->getWidth(), effectImage->getHeight(), frameW, frameH);
	effectAnimation->setDefPlayFrame(false, false);
	effectAnimation->setFPS(fps);
	effectAnimation->stop();
}

void Effect::release(void)
{
	effectImage = NULL;
	SAFE_DELETE(effectAnimation);
}

void Effect::update(void)
{

	//실행중이지 않다면 돌려보내고
	if (!isRunning) return;

	//애니메이션 프레임 업데이트
	effectAnimation->frameUpdate(elapsedTime);

	//플레이 상태가 아니면 꺼준다
	if (!effectAnimation->isPlay()) killEffect();
}

void Effect::render(void)
{
	if (!isRunning) return;

	//effectImage->aniRender(hdc, x, y, effectAnimation);
}

void Effect::startEffect(int x, int y)
{
	//이미지나 애니메이션 둘중 하나라도 없으면 실행시키지마라
	if (!effectImage || !effectAnimation) return;

	this->x = x - (effectAnimation->getFrameWidth() / 2);
	this->y = y - (effectAnimation->getFrameHeight() / 2);

	isRunning = true;
	effectAnimation->start();
}

void Effect::killEffect(void)
{
	isRunning = false;
}

Effect::Effect()
	: effectImage(NULL),
	effectAnimation(NULL),
	isRunning(false),
	x(0), y(0)
{
}


Effect::~Effect()
{
}
