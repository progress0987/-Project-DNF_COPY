#include "stdafx.h"
#include "Seria.h"
#include "Village.h"


Seria::Seria()
{
}


Seria::~Seria()
{
}

HRESULT Seria::init()
{
	IMAGEMANAGER->addImage("技府酒_0", "sprites/maps/seria/bg0/0.png");
	IMAGEMANAGER->addImage("技府酒_1", "sprites/maps/seria/bg1/0.png");
	IMAGEMANAGER->addImage("技府酒_2", "sprites/maps/seria/bg2/0.png");
	IMAGEMANAGER->addImage("技府酒_3", "sprites/maps/seria/bg3/0.png");
	IMAGEMANAGER->addImage("技府酒_4", "sprites/maps/seria/bg4/0.png");
	IMAGEMANAGER->addImage("技府酒_5", "sprites/maps/seria/bg5/0.png");
	IMAGEMANAGER->addImage("技府酒_6", "sprites/maps/seria/bg6/0.png");
	tileNumX = IMAGEMANAGER->findImage("技府酒_2")->getWidth() / 50 + 1;
	tileNumY = IMAGEMANAGER->findImage("技府酒_2")->getHeight() / 50 + 1;
	mapWidth = IMAGEMANAGER->findImage("技府酒_2")->getWidth();
	mapHeight = IMAGEMANAGER->findImage("技府酒_2")->getHeight();
	for (int i = 0; i < tileNumY; i++) {
		for (int j = 0; j < tileNumX; j++) {
			if ((i == 7 && (j >= 4 && j <= 15)) || (i == 8 && (j >= 1 && j <= 17)) || (i >= 9)&&!(i==11&&(j>=8&&j<=10)))continue;
			MapTile tile;
			tile.rc = RectMake((j * 50)-cam.x, (i * 50) -cam.y, 50, 50);
			if (i == 11 && (j >= 8 && j <= 10)) {
				tile.type = 0;
				tile.moveindex = 0;
			}
			else tile.type = -1;

			mapTiles.push_back(tile);
		}
	}
	peaceful = true;
	runnable = false;
	attackable = false;
	isChangable = false;
	showresult = false;
	seria.init();

	return S_OK;
}

void Seria::update()
{
	if (!SOUNDMANAGER->isPlaySound("BGM_技府酒")) {
		playBGM("BGM_技府酒");
	}
	seria.update();
	MapBase::update();
}

void Seria::render()
{
	IMAGEMANAGER->findImage("技府酒_2")->render(0,0,cam.x,cam.y,WINSIZEX,WINSIZEY);
	IMAGEMANAGER->findImage("技府酒_1")->render(0, 0, cam.x, cam.y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("技府酒_0")->render(0, 0, cam.x, cam.y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("技府酒_3")->render(0,0,cam.x,cam.y,WINSIZEX,WINSIZEY);
	IMAGEMANAGER->findImage("技府酒_4")->render(0,0,cam.x,cam.y,WINSIZEX,WINSIZEY);

	seria.render();

	//IMAGEMANAGER->findImage("技府酒_2")->blurredrender(0,0,0x88);
	//IMAGEMANAGER->findImage("技府酒_3")->blurredrender(0,0,0x88);
	//IMAGEMANAGER->findImage("技府酒_4")->blurredrender(0,0,0x88);
	pl->render();
	IMAGEMANAGER->findImage("技府酒_5")->render(0, 0, cam.x, cam.y, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("技府酒_6")->render(0, 0, cam.x, cam.y, WINSIZEX, WINSIZEY);

}

void Seria::renderz()
{
	IMAGEMANAGER->findImage("技府酒_5")->render(0,0,cam.x,cam.y,WINSIZEX,WINSIZEY);
	
	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	IMAGEMANAGER->findImage("X钎矫")->render(i->rc.left -cam.x, i->rc.top -cam.y);
	//}
}

void Seria::renderdc()
{

}
