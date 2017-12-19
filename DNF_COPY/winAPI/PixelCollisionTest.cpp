#include "stdafx.h"
#include "PixelCollisionTest.h"


HRESULT PixelCollisionTest::init(void)
{
	return S_OK;
}

void PixelCollisionTest::release(void)
{
}

void PixelCollisionTest::update(void)
{
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT)) x -= 3.0f;
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) x += 3.0f;
	//probeY = y + ball->getHeight() / 2;
	//for (int i = probeY - 50; i < probeY + 50; i++) {
	//	COLORREF color = GetPixel(IMAGEMANAGER->findImage("BG")->hdc, x, i);
	//	int r = GetRValue(color);
	//	int g = GetGValue(color);
	//	int b = GetBValue(color);
	//	//ÇÈ¼¿Ã¼Å©
	//	if (!(r == 255 && g == 0 && b == 255)) {
	//		y = i - ball->getHeight() / 2;
	//		break;
	//	}
	//}
	//rc = RectMakeCenter(x, y, ball->getWidth(), ball->getHeight());
}

void PixelCollisionTest::render()
{
}

PixelCollisionTest::PixelCollisionTest()
{
}


PixelCollisionTest::~PixelCollisionTest()
{
}
