#include "stdafx.h"
#include "UI.h"


HRESULT UI::init(void)
{
	IMAGEMANAGER->addImage("UI_기본창", "sprites/UI/hud.img/0.png");
	IMAGEMANAGER->addImage("UI_기본창_확장", "sprites/UI/hud.img/133.png");
	IMAGEMANAGER->addImage("UI_기본창_조각", "sprites/UI/hud.img/134.png");
	IMAGEMANAGER->addImage("UI_HP", "sprites/UI/hud.img/1.png");
	IMAGEMANAGER->addImage("UI_MP", "sprites/UI/hud.img/2.png");
	return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{
}

void UI::render(void)
{
	int UI_top = WINSIZEY - IMAGEMANAGER->findImage("UI_기본창")->getHeight();
	IMAGEMANAGER->findImage("UI_기본창_조각")->render(0, WINSIZEY- IMAGEMANAGER->findImage("UI_기본창_조각")->getHeight());
	IMAGEMANAGER->findImage("UI_기본창")->render(0, UI_top);
	IMAGEMANAGER->findImage("UI_기본창_확장")->render(508, UI_top);
	IMAGEMANAGER->findImage("UI_HP")->render(35, UI_top+9);
	IMAGEMANAGER->findImage("UI_MP")->render(730, UI_top+9);
	
}

void UI::renderdc(void)
{
}

UI::UI()
{
}


UI::~UI()
{
}
