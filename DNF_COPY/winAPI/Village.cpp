#include "stdafx.h"
#include "Village.h"


HRESULT Village::init()
{
	IMAGEMANAGER->addImage("����_�޹��_0", "sprites/maps/village/back_far/0.png");
	IMAGEMANAGER->addImage("����_�޹��_1", "sprites/maps/village/back_far/1.png");
	IMAGEMANAGER->addImage("����_�޹��_2", "sprites/maps/village/back_far/2.png");
	IMAGEMANAGER->addImage("����_�߰����_0", "sprites/maps/village/back_middle/0.png");
	IMAGEMANAGER->addImage("����_ȭ��", "sprites/maps/village/blacksmith/0.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_0", "sprites/maps/village/blacksmith/1.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_1", "sprites/maps/village/blacksmith/2.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_2", "sprites/maps/village/blacksmith/3.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_3", "sprites/maps/village/blacksmith/4.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_4", "sprites/maps/village/blacksmith/5.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_5", "sprites/maps/village/blacksmith/6.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_6", "sprites/maps/village/blacksmith/7.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_7", "sprites/maps/village/blacksmith/8.png");
	IMAGEMANAGER->addImage("����_�Ҳ�_6", "sprites/maps/village/blacksmith/0.png");
	IMAGEMANAGER->addImage("����_����_0", "sprites/maps/village/blacksmith_smoke/0.png");
	IMAGEMANAGER->addImage("����_����_1", "sprites/maps/village/blacksmith_smoke/1.png");
	IMAGEMANAGER->addImage("����_����_2", "sprites/maps/village/blacksmith_smoke/2.png");
	IMAGEMANAGER->addImage("����_����_3", "sprites/maps/village/blacksmith_smoke/3.png");
	IMAGEMANAGER->addImage("����_����_4", "sprites/maps/village/blacksmith_smoke/4.png");
	IMAGEMANAGER->addImage("����_����_5", "sprites/maps/village/blacksmith_smoke/5.png");
	IMAGEMANAGER->addImage("����_����_6", "sprites/maps/village/blacksmith_smoke/6.png");
	IMAGEMANAGER->addImage("����_����_7", "sprites/maps/village/blacksmith_smoke/7.png");
	IMAGEMANAGER->addImage("����_����_�Ʒ�", "sprites/maps/village/gate_down/0.png");
	IMAGEMANAGER->addImage("����_����_��", "sprites/maps/village/gate_up/0.png");
	IMAGEMANAGER->addImage("����_������", "sprites/maps/village/seria_tree/0.png");
	IMAGEMANAGER->addImage("����_����ǥ��", "sprites/maps/village/sign_dungeon/0.png");
	IMAGEMANAGER->addImage("����_��Ʈ", "sprites/maps/village/seria_tree/0.png");
	IMAGEMANAGER->addImage("����_Ÿ��", "sprites/maps/village/tile/0.png");
	IMAGEMANAGER->addImage("����_����_0", "sprites/maps/village/tree/0.png");
	IMAGEMANAGER->addImage("����_����_1", "sprites/maps/village/tree/1.png");
	this->count = smokeframe = 0;

	peaceful = true;
	runnable = false;
	attackable = false;
	isChangable = true;
	showresult = false;
	linus.init();
	kanna.init();


	flameframe = 1;
	tilewidth = IMAGEMANAGER->findImage("����_Ÿ��")->getWidth();
	floortileNum = 10;
	mapWidth = tilewidth * floortileNum;
	mapHeight = IMAGEMANAGER->findImage("����_Ÿ��")->getHeight();
	tileNumX = mapWidth / 50 + 1;
	tileNumY = mapHeight / 50 + 1;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < tileNumX; j++) {
			MapTile tile;
			tile.rc = RectMake((j * 50) - cam.x, (i * 50) - cam.y, 50, 50);
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
	
	////////////////////////////////////////////////////�̹��� Ÿ�� ������

	ImgTile imgt;



	int backtilenum = 5;
	for (int i = 0; i < backtilenum; i++) {
		imgt.tileImg = IMAGEMANAGER->findImage("����_�޹��_0");
		imgt.pos.x = i * IMAGEMANAGER->findImage("����_�޹��_0")->getWidth();
		imgt.pos.y = 0;
		staticTiles.push_back(imgt);
	}
	imgt.tileImg	= IMAGEMANAGER->findImage("����_�޹��_1");
	imgt.pos.x		= IMAGEMANAGER->findImage("����_�޹��_0")->getWidth() + 100;
	imgt.pos.y		= 0;
	staticTiles.push_back(imgt);

	imgt.tileImg = IMAGEMANAGER->findImage("����_�޹��_2");
	imgt.pos.x = IMAGEMANAGER->findImage("����_�޹��_0")->getWidth() * 2 + 300;
	imgt.pos.y = 0;
	staticTiles.push_back(imgt);

	for (int i = 0; i < backtilenum; i++) {
		imgt.tileImg = IMAGEMANAGER->findImage("����_�߰����_0");
		imgt.pos.x = i * IMAGEMANAGER->findImage("����_�߰����_0")->getWidth();
		imgt.pos.y = 0;
		staticTiles.push_back(imgt);
	}


	for (int i = 0; i < floortileNum; i++) {
		imgt.tileImg = IMAGEMANAGER->findImage("����_Ÿ��");
		imgt.pos.x = i * tilewidth;
		imgt.pos.y = 0;
		staticTiles.push_back(imgt);
	}
	imgt.tileImg = IMAGEMANAGER->findImage("����_ȭ��");
	imgt.pos.x = 1290;
	imgt.pos.y = -20;
	staticTiles.push_back(imgt);

	imgt.tileImg = IMAGEMANAGER->findImage("����_������");
	imgt.pos.x = 480;
	imgt.pos.y = -20;
	staticTiles.push_back(imgt);

	imgt.tileImg = IMAGEMANAGER->findImage("����_����ǥ��");
	imgt.pos.x = -40;
	imgt.pos.y = 120;
	staticTiles.push_back(imgt);
	return S_OK;
}

void Village::update()
{
	if (!SOUNDMANAGER->isPlaySound("BGM_����")) {
		playBGM("BGM_����");
	}
	count++;
	showSmoke();
	showFlame();
	linus.update();
	kanna.update();
	MapBase::update();
}

void Village::render()
{
	char temp[255];
	for (vector<ImgTile>::iterator i = staticTiles.begin(); i != staticTiles.end(); i++) {
		i->tileImg->render(i->pos.x - cam.x, i->pos.y - cam.y);
	}

	sprintf(temp, "����_�Ҳ�_%d", flameframe - 1);
	IMAGEMANAGER->findImage(temp)->render(1290 - cam.x, -20- cam.y);
	sprintf(temp, "����_����_%d", smokeframe);
	IMAGEMANAGER->findImage(temp)->render(1290+262 - cam.x, -20-160- cam.y);
	linus.render();
	kanna.render();
	pl->render();
}

void Village::renderz()
{
	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	IMAGEMANAGER->findImage("Xǥ��")->render(i->rc.left - cam.x, i->rc.top - cam.y);
	//}
}

void Village::renderdc()
{
	//POINT curpt = ptMouse;
	//curpt.x += cam.x;
	//curpt.y += cam.y;
	//char t[50];
	//sprintf(t, "x:%d, y:%d", curpt.x, curpt.y);
	//TextOut(hdc, 50, 300, t, strlen(t));	//�׽�Ʈ��
	//linus.renderdc();
	//kanna.renderdc();
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
