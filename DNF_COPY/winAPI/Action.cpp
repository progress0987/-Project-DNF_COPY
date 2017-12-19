#include "stdafx.h"
//#include "Action.h"
//
//
//HRESULT Action::init(void)
//{
//	this->worldTimeCount = 0;
//	this->isMoving = false;
//	return S_OK;
//}
//
//void Action::release(void)
//{
//}
//
//void Action::update(void)
//{
//	moving();
//}
//
//void Action::render()
//{
//}
//
//void Action::moveTo(image * image, float endx, float endy, float time)
//{
//	if (isMoving) {
//		img = image;
//		startX = img->getX();
//		startY = img->getY();
//
//		endX = endx;
//		endY = endy;
//		travelRange = getDistance(startX, startY, endX, endY);
//		angle = getAngle(startX, startY, endX, endY);
//		worldTimeCount = TIMEMANAGER->getWorldTime();
//		this->time = time;
//		isMoving = true;
//	}
//}
//
//void Action::moveTo(image * image, float endx, float endy, float time, CALLBACK_FUNCTION cbfunc)
//{
//	if (isMoving) {
//		callbackfunc = static_cast<CALLBACK_FUNCTION>(cbfunc);
//		img = image;
//		startX = img->getX();
//		startY = img->getY();
//
//		endX = endx;
//		endY = endy;
//		travelRange = getDistance(startX, startY, endX, endY);
//		angle = getAngle(startX, startY, endX, endY);
//		worldTimeCount = TIMEMANAGER->getWorldTime();
//		this->time = time;
//		isMoving = true;
//	}
//}
//
//void Action::moving()
//{
//	if (!isMoving) return;
//
//	float elapsedTime = TIMEMANAGER->getElapsedTime();
//	//향속(원하는 시간분에 틱카운트*) 가고자 하는 거리
//	float moveSpeed = (elapsedTime / time)*travelRange;
//	img->setX(img->getX() + cosf(angle)*moveSpeed);
//	img->setY(img->getY() - sinf(angle)*moveSpeed);
//
//	float t = TIMEMANAGER->getElapsedTime();
//
//	if (t + worldTimeCount == TIMEMANAGER->getElapsedTime()) {
//		worldTimeCount = TIMEMANAGER->getWorldTime();
//		img->setX(endX);
//		img->setY(endY);
//		isMoving = false;
//		if (callbackfunc != NULL) {
//			callbackfunc();
//		}
//	}
//	
//}
//
//Action::Action()
//{
//}
//
//
//Action::~Action()
//{
//}
