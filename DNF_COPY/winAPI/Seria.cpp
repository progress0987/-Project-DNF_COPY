#include "stdafx.h"
#include "Seria.h"
#include "Village.h"


Seria::Seria()
{
}


Seria::~Seria()
{
}

void Seria::init()
{
	IMAGEMANAGER->addImage("������_2", "sprites/maps/seria/bg2/0.png");
	IMAGEMANAGER->addImage("������_3", "sprites/maps/seria/bg3/0.png");
	IMAGEMANAGER->addImage("������_4", "sprites/maps/seria/bg4/0.png");
	IMAGEMANAGER->addImage("������_5", "sprites/maps/seria/bg5/0.png");
	tileNumX = IMAGEMANAGER->findImage("������_2")->getWidth() / 50 + 1;
	tileNumY = IMAGEMANAGER->findImage("������_2")->getHeight() / 50 + 1;
	mapWidth = IMAGEMANAGER->findImage("������_2")->getWidth();
	mapHeight = IMAGEMANAGER->findImage("������_2")->getHeight();
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
}

void Seria::update()
{
}

void Seria::render()
{
	IMAGEMANAGER->findImage("������_2")->render();
	IMAGEMANAGER->findImage("������_3")->render();
	IMAGEMANAGER->findImage("������_4")->render();
	//IMAGEMANAGER->findImage("������_2")->blurredrender(0,0,0x88);
	//IMAGEMANAGER->findImage("������_3")->blurredrender(0,0,0x88);
	//IMAGEMANAGER->findImage("������_4")->blurredrender(0,0,0x88);

}

void Seria::renderz()
{
	IMAGEMANAGER->findImage("������_5")->render();
	
	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	IMAGEMANAGER->findImage("Xǥ��")->render(i->rc.left, i->rc.top);
	//}
}

void Seria::renderdc()
{
	//for (int i = 0; i < tileNumY; i++) {
	//	for (int j = 0; j < tileNumX; j++) {
	//		if (PtInRect(&mapTiles[j + i * tileNumX], ptMouse)) {
	//			char t[50];
	//			sprintf(t, "j:%d, i:%d", j, i);
	//			TextOut(hdc, 50, 300, t, strlen(t));	//�׽�Ʈ��
	//		}
	//	}
	//}
	TIMEMANAGER->render(hdc);
}
