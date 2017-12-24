#include "stdafx.h"
#include "UI.h"


HRESULT UI::init(void)
{
	IMAGEMANAGER->addImage("UI_�⺻â", "sprites/UI/hud.img/0.png");
	IMAGEMANAGER->addImage("UI_�⺻â_Ȯ��", "sprites/UI/hud.img/133.png");
	IMAGEMANAGER->addImage("UI_�⺻â_����", "sprites/UI/hud.img/134.png");
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
	int UI_top = WINSIZEY - IMAGEMANAGER->findImage("UI_�⺻â")->getHeight();
	IMAGEMANAGER->findImage("UI_�⺻â_����")->render(0, WINSIZEY- IMAGEMANAGER->findImage("UI_�⺻â_����")->getHeight());
	IMAGEMANAGER->findImage("UI_�⺻â")->render(0, UI_top);
	IMAGEMANAGER->findImage("UI_�⺻â_Ȯ��")->render(508, UI_top);
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
