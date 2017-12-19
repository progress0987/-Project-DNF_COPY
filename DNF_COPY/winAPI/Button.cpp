#include "stdafx.h"
//#include "Button.h"
//
//
//HRESULT Button::init(const char * imgName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunc)
//{
//	this->callbackfunction = static_cast<CALLBACK_FUNCTION>(cbFunc);
//	this->Dir = BUTTONDIRECTION_NULL;
//	this->X = x;
//	this->Y = y;
//	this->btnUpFramePoint = btnUpFramePoint;
//	this->btnDownFramePoint = btnDownFramePoint;
//	this->imgName = imgName;
//	this->img = IMAGEMANAGER->findImage(imgName);
//	this->rc = RectMakeCenter(x, y, this->img->getFrameWidth(), this->img->getFrameHeight());
//	return S_OK;
//}
//
//void Button::release(void)
//{
//}
//
//void Button::update(void)
//{
//	if (PtInRect(&rc, ptMouse)) {
//		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
//			Dir = BUTTONDIRECTION_DOWN;
//		}
//		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
//			Dir = BUTTONDIRECTION_UP;
//			this->callbackfunction();
//		}
//	}
//	else Dir = BUTTONDIRECTION_NULL;
//}
//
//void Button::render()
//{
//	switch (Dir) {
//	case BUTTONDIRECTION_NULL:
//	case BUTTONDIRECTION_UP:
//		img->frameRender(hdc, rc.left, rc.top, btnUpFramePoint.x, btnUpFramePoint.y);
//		break;
//	case BUTTONDIRECTION_DOWN:
//		img->frameRender(hdc, rc.left, rc.top, btnDownFramePoint.x, btnDownFramePoint.y);
//		break;
//	}
//}
//
//Button::Button()
//{
//}
//
//
//Button::~Button()
//{
//}
