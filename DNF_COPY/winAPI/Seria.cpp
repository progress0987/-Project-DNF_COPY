#include "stdafx.h"
#include "Seria.h"


Seria::Seria()
{
}


Seria::~Seria()
{
}

void Seria::init()
{
	//IMAGEMANAGER->addImage("세리아_0", "sprites/maps/seria/bg0/0.png");
	//IMAGEMANAGER->addImage("세리아_1", "sprites/maps/seria/bg1/0.png");
	IMAGEMANAGER->addImage("세리아_2", "sprites/maps/seria/bg2/0.png");
	IMAGEMANAGER->addImage("세리아_3", "sprites/maps/seria/bg3/0.png");
	IMAGEMANAGER->addImage("세리아_4", "sprites/maps/seria/bg4/0.png");
	IMAGEMANAGER->addImage("세리아_5", "sprites/maps/seria/bg5/0.png");
	//IMAGEMANAGER->addImage("세리아_6", "sprites/maps/seria/bg6/0.png");
	tileNumX = IMAGEMANAGER->findImage("세리아_2")->getWidth() / 50 + 1;
	tileNumY = IMAGEMANAGER->findImage("세리아_2")->getHeight() / 50 + 1;
	//ZeroMemory(&mapTiles, sizeof(RECT)*tileNumX*tileNumY);						//이미 있는공간을 초기화하기위해 이렇게 사용
	for (int i = 0; i < tileNumY; i++) {
		for (int j = 0; j < tileNumX; j++) {
			if ((i == 7 && (j >= 4 && j <= 15)) || (i == 8 && (j >= 1 && j <= 17)) || (i >= 9)&&!(i==11&&(j>=8&&j<=10)))continue;
			MapTile tile;
			tile.rc = RectMake((j * 50), (i * 50), 50, 50);
			if (i == 11 && (j >= 8 && j <= 10))	tile.type = 0;
			else tile.type = -1;

			mapTiles.push_back(tile);
		}
	}
	standardY = IMAGEMANAGER->findImage("세리아_2")->getHeight();//이미지의 좌하단을 기준으로 Z좌표를 정할것.
}

void Seria::update()
{
}

void Seria::render()
{
	//IMAGEMANAGER->findImage("세리아_0")->render();
	//IMAGEMANAGER->findImage("세리아_1")->render();
	//IMAGEMANAGER->findImage("세리아_2")->render();
	//IMAGEMANAGER->findImage("세리아_3")->render();
	//IMAGEMANAGER->findImage("세리아_4")->render();
	IMAGEMANAGER->findImage("세리아_2")->blurredrender(0,0,0x88);
	IMAGEMANAGER->findImage("세리아_3")->blurredrender(0,0,0x88);
	IMAGEMANAGER->findImage("세리아_4")->blurredrender(0,0,0x88);

	//IMAGEMANAGER->findImage("세리아_6")->render();
}

void Seria::renderz()
{
	IMAGEMANAGER->findImage("세리아_5")->render();
	
	for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
		IMAGEMANAGER->findImage("X표시")->render(i->rc.left, i->rc.top);
	}
}

void Seria::renderdc()
{
	//for (int i = 0; i < tileNumY; i++) {
	//	for (int j = 0; j < tileNumX; j++) {
	//		if (PtInRect(&mapTiles[j + i * tileNumX], ptMouse)) {
	//			char t[50];
	//			sprintf(t, "j:%d, i:%d", j, i);
	//			TextOut(hdc, 50, 300, t, strlen(t));	//테스트용
	//		}
	//	}
	//}
	TIMEMANAGER->render(hdc);
}
