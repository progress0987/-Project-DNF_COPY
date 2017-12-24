#include "stdafx.h"
#include "Village.h"


void Village::init()
{
	IMAGEMANAGER->addImage("마을_뒷배경_0", "sprites/maps/village/back_far/0.png");
	IMAGEMANAGER->addImage("마을_뒷배경_1", "sprites/maps/village/back_far/1.png");
	IMAGEMANAGER->addImage("마을_뒷배경_2", "sprites/maps/village/back_far/2.png");
	IMAGEMANAGER->addImage("마을_중간배경_0", "sprites/maps/village/back_middle/0.png");
	IMAGEMANAGER->addImage("마을_화로", "sprites/maps/village/blacksmith/0.png");
	IMAGEMANAGER->addImage("마을_불꽃_0", "sprites/maps/village/blacksmith/1.png");
	IMAGEMANAGER->addImage("마을_불꽃_1", "sprites/maps/village/blacksmith/2.png");
	IMAGEMANAGER->addImage("마을_불꽃_2", "sprites/maps/village/blacksmith/3.png");
	IMAGEMANAGER->addImage("마을_불꽃_3", "sprites/maps/village/blacksmith/4.png");
	IMAGEMANAGER->addImage("마을_불꽃_4", "sprites/maps/village/blacksmith/5.png");
	IMAGEMANAGER->addImage("마을_불꽃_5", "sprites/maps/village/blacksmith/6.png");
	IMAGEMANAGER->addImage("마을_불꽃_6", "sprites/maps/village/blacksmith/7.png");
	IMAGEMANAGER->addImage("마을_불꽃_7", "sprites/maps/village/blacksmith/8.png");
	IMAGEMANAGER->addImage("마을_불꽃_6", "sprites/maps/village/blacksmith/0.png");
	IMAGEMANAGER->addImage("마을_연기_0", "sprites/maps/village/blacksmith_smoke/0.png");
	IMAGEMANAGER->addImage("마을_연기_1", "sprites/maps/village/blacksmith_smoke/1.png");
	IMAGEMANAGER->addImage("마을_연기_2", "sprites/maps/village/blacksmith_smoke/2.png");
	IMAGEMANAGER->addImage("마을_연기_3", "sprites/maps/village/blacksmith_smoke/3.png");
	IMAGEMANAGER->addImage("마을_연기_4", "sprites/maps/village/blacksmith_smoke/4.png");
	IMAGEMANAGER->addImage("마을_연기_5", "sprites/maps/village/blacksmith_smoke/5.png");
	IMAGEMANAGER->addImage("마을_연기_6", "sprites/maps/village/blacksmith_smoke/6.png");
	IMAGEMANAGER->addImage("마을_연기_7", "sprites/maps/village/blacksmith_smoke/7.png");
	IMAGEMANAGER->addImage("마을_관문_아래", "sprites/maps/village/gate_down/0.png");
	IMAGEMANAGER->addImage("마을_관문_위", "sprites/maps/village/gate_up/0.png");
	IMAGEMANAGER->addImage("마을_세리아", "sprites/maps/village/seria_tree/0.png");
	IMAGEMANAGER->addImage("마을_던전표석", "sprites/maps/village/sign_dungeon/0.png");
	IMAGEMANAGER->addImage("마을_텐트", "sprites/maps/village/seria_tree/0.png");
	IMAGEMANAGER->addImage("마을_타일", "sprites/maps/village/tile/0.png");
	IMAGEMANAGER->addImage("마을_나무_0", "sprites/maps/village/tree/0.png");
	IMAGEMANAGER->addImage("마을_나무_1", "sprites/maps/village/tree/1.png");
	this->count = smokeframe = 0;
	peaceful = true;
	flameframe = 1;
	tilewidth = IMAGEMANAGER->findImage("마을_타일")->getWidth();
	floortileNum = 10;
	mapWidth = tilewidth * floortileNum;
	mapHeight = IMAGEMANAGER->findImage("마을_타일")->getHeight();
	tileNumX = mapWidth / 50 + 1;
	tileNumY = mapHeight / 50 + 1;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < tileNumX; j++) {
			MapTile tile;
			tile.rc = RectMake((j * 50) - Cam->x, (i * 50) - Cam->y, 50, 50);
			//if (i == 11 && (j >= 8 && j <= 10))	tile.type = 0;
			//else tile.type = -1;
			tile.type = -1;
			mapTiles.push_back(tile);
		}
	}
	MapTile t;
	t.rc = RectMakeCenter(683, 300, 50, 50);
	t.type = 0;
	t.moveindex = 0;
	mapTiles.push_back(t);

	t.rc = RectMakeCenter(683+50, 300, 50, 50);
	mapTiles.push_back(t);
	t.rc = RectMakeCenter(683-50, 325, 50, 50);
	t.type = -1;
	mapTiles.push_back(t);
	t.rc = RectMakeCenter(683-100, 325, 50, 50);
	mapTiles.push_back(t);
	t.rc = RectMakeCenter(683+100, 325, 50, 50);
	mapTiles.push_back(t);
	t.rc = RectMakeCenter(683+150, 325, 50, 50);
	mapTiles.push_back(t);
	for (int i = 0; i < 9; i++) {
		t.rc = RectMakeCenter(1575 + i * 50, 300, 50, 50);
		mapTiles.push_back(t);
	}
	


}

void Village::update()
{
	count++;
	showSmoke();
	showFlame();
}

void Village::render()
{
	char temp[255];
	int backtilenum = 5;
	for (int i = 0; i < backtilenum; i++) {
		IMAGEMANAGER->findImage("마을_뒷배경_0")->render(i*IMAGEMANAGER->findImage("마을_뒷배경_0")->getWidth()-Cam->x,-Cam->y);
	}
	IMAGEMANAGER->findImage("마을_뒷배경_1")->render(IMAGEMANAGER->findImage("마을_뒷배경_0")->getWidth()+100-Cam->x,-Cam->y);
	IMAGEMANAGER->findImage("마을_뒷배경_2")->render(IMAGEMANAGER->findImage("마을_뒷배경_0")->getWidth()*2+300-Cam->x,-Cam->y);
	for (int i = 0; i < backtilenum; i++) {
		IMAGEMANAGER->findImage("마을_중간배경_0")->render(i*IMAGEMANAGER->findImage("마을_중간배경_0")->getWidth()-Cam->x,-Cam->y);
	}


	for (int i = 0; i < floortileNum; i++) {
		IMAGEMANAGER->findImage("마을_타일")->render(i*tilewidth - Cam->x, -Cam->y);
	}
	IMAGEMANAGER->findImage("마을_화로")->render(1290-Cam->x, -20-Cam->y);
	sprintf(temp, "마을_불꽃_%d", flameframe - 1);
	IMAGEMANAGER->findImage(temp)->render(1290 - Cam->x, -20- Cam->y);
	sprintf(temp, "마을_연기_%d", smokeframe);
	IMAGEMANAGER->findImage(temp)->render(1290+262 - Cam->x, -20-160- Cam->y);
	IMAGEMANAGER->findImage("마을_세리아")->render(480 - Cam->x, -20-Cam->y);
	IMAGEMANAGER->findImage("마을_던전표석")->render(-40-Cam->x, 120-Cam->y);
}

void Village::renderz()
{
	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	IMAGEMANAGER->findImage("X표시")->render(i->rc.left - Cam->x, i->rc.top - Cam->y);
	//}
}

void Village::renderdc()
{
	POINT curpt = ptMouse;
	curpt.x += Cam->x;
	curpt.y += Cam->y;
	char t[50];
	sprintf(t, "x:%d, y:%d", curpt.x, curpt.y);
	TextOut(hdc, 50, 300, t, strlen(t));	//테스트용
}

void Village::showSmoke()
{
	if (count % 15==0) {
		smokeframe++;
		if (smokeframe > 7) {
			smokeframe = 0;
		}
	}
}

void Village::showFlame()
{
	if (count % 10==0) {
		flameframe++;
		if (flameframe > 8) {
			flameframe = 1;
		}
	}
}

Village::Village()
{
}


Village::~Village()
{
}
