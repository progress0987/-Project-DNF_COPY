#include "stdafx.h"
#include "soundTest.h"


soundTest::soundTest()
{
}


soundTest::~soundTest()
{

}
HRESULT soundTest::init(void)
{
	SOUNDMANAGER->addSound("동원참치", "Sounds/방울방울.mp3", true, true);
	//SOUNDMANAGER->play("동원참치");

	return S_OK;
}
void soundTest::release(void)
{

}
void soundTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		SOUNDMANAGER->play("동원참치", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop("동원참치");
	}
}
