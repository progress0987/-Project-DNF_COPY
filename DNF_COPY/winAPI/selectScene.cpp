#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init(void)
{
	return S_OK;
}

void selectScene::release(void)
{
}

void selectScene::update(void)
{
}

void selectScene::render()
{
	char str[128];
	sprintf(str, "º±≈√ æ¿");
	TextOut(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));
}
