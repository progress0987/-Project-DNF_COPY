#include "stdafx.h"
#include "Mirkwood.h"


void Mirkwood::init()
{
	IMAGEMANAGER->addImage("던전_머크우드_배경_뒤", "sprites/maps/dungeons/mirkwood/back_far.img/0.png");
	IMAGEMANAGER->addImage("던전_머크우드_배경_중간", "sprites/maps/dungeons/mirkwood/back_middle.img/0.png");
	IMAGEMANAGER->addImage("던전_머크우드_배경_나무길", "sprites/maps/dungeons/mirkwood/tree_backway.img/0.png");
	
	IMAGEMANAGER->addImage("던전_머크우드_바닥_0", "sprites/maps/dungeons/mirkwood/tile.img/0.png");
	IMAGEMANAGER->addImage("던전_머크우드_바닥_1", "sprites/maps/dungeons/mirkwood/tile.img/1.png");
	IMAGEMANAGER->addImage("던전_머크우드_바닥_2", "sprites/maps/dungeons/mirkwood/tile.img/2.png");
	IMAGEMANAGER->addImage("던전_머크우드_바닥_3", "sprites/maps/dungeons/mirkwood/tile.img/3.png");
	IMAGEMANAGER->addImage("던전_머크우드_바닥_덧붙임", "sprites/maps/dungeons/mirkwood/tile_ex.img/0.png");

	IMAGEMANAGER->addImage("던전_머크우드_지형_돌_0", "sprites/maps/dungeons/mirkwood/stone.img/0.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_돌_1", "sprites/maps/dungeons/mirkwood/stone.img/1.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_돌_2", "sprites/maps/dungeons/mirkwood/stone.img/2.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_돌_3", "sprites/maps/dungeons/mirkwood/stone.img/3.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_돌_4", "sprites/maps/dungeons/mirkwood/stone.img/4.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_돌_5", "sprites/maps/dungeons/mirkwood/stone.img/5.png");

	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_0", "sprites/maps/dungeons/mirkwood/tree.img/0.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_1", "sprites/maps/dungeons/mirkwood/tree.img/1.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_2", "sprites/maps/dungeons/mirkwood/tree.img/2.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_3", "sprites/maps/dungeons/mirkwood/tree.img/3.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_4", "sprites/maps/dungeons/mirkwood/tree.img/4.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_5", "sprites/maps/dungeons/mirkwood/tree.img/5.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_6", "sprites/maps/dungeons/mirkwood/tree.img/6.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_7", "sprites/maps/dungeons/mirkwood/tree.img/7.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_8", "sprites/maps/dungeons/mirkwood/tree.img/8.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_9", "sprites/maps/dungeons/mirkwood/tree.img/9.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_10", "sprites/maps/dungeons/mirkwood/tree.img/10.png");
	IMAGEMANAGER->addImage("던전_머크우드_지형_나무_11", "sprites/maps/dungeons/mirkwood/tree.img/11.png");
	

	peaceful = false;
	runnable = true;
	attackable = true;



	MirkwoodMap* m1 = new MirkwoodMap;
	MirkwoodMap* m2 = new MirkwoodMap;
	MirkwoodMap* m3 = new MirkwoodMap;
	
	tilewidth = IMAGEMANAGER->findImage("던전_머크우드_바닥_0")->getWidth();
	/////////////////////////////////////////////////////////////////////////1번째 맵 처리
	{

		int tileNum = 5;
		for (int i = 0; i < tileNum; i++) {
			m1->setMap("던전_머크우드_배경_뒤", IMAGEMANAGER->findImage("던전_머크우드_배경_뒤")->getWidth() * i, 0);
			m1->setMap("던전_머크우드_배경_중간", IMAGEMANAGER->findImage("던전_머크우드_배경_뒤")->getWidth() * i, 0);
		}
		m1->setMap("던전_머크우드_바닥_1", 0, 0);
		for (int i = 0; i < tileNum; i++) {
			m1->setMap("던전_머크우드_바닥_2", tilewidth + tilewidth * i, 0);
		}
		m1->setMap("던전_머크우드_바닥_3", tilewidth*(tileNum + 1), 0);

		for (int i = 0; i < 10; i++) {
			m1->setMap("던전_머크우드_지형_나무_4", rand() % (tilewidth*(tileNum+2) - IMAGEMANAGER->findImage("던전_머크우드_지형_나무_4")->getWidth()), -rand() % 50-50);
		}


		m1->setWidth(tilewidth*(tileNum + 2));
		m1->setHeight(IMAGEMANAGER->findImage("던전_머크우드_바닥_0")->getHeight());

		m1->setTileNumX(m1->getWidth() / 50 + 1);
		m1->setTileNumY(m1->getHeight() / 50 + 1);
		for (int y = 0; y < m1->getTileNumY() / 2 +1; y++) {
			for (int x = 0; x < m1->getTileNumX(); x++) {
				MapTile t;
				t.rc = RectMake(x * 50, y * 50, 50, 50);
				t.type = -1;
				m1->addMapTile(t);
			}
		}
	}
	/////////////////////////////////////////////////////////////////////2번째 맵 처리
	{
		int tileNum = 6;
		for (int i = 0; i < tileNum; i++) {
			m2->setMap("던전_머크우드_배경_뒤", IMAGEMANAGER->findImage("던전_머크우드_배경_뒤")->getWidth() * i, 0);
			m2->setMap("던전_머크우드_배경_중간", IMAGEMANAGER->findImage("던전_머크우드_배경_뒤")->getWidth() * i, 0);
		}
		m2->setMap("던전_머크우드_바닥_1", 0, 0);
		for (int i = 0; i < tileNum; i++) {
			m2->setMap("던전_머크우드_바닥_2", tilewidth + tilewidth * i, 0);
		}
		m2->setMap("던전_머크우드_바닥_3", tilewidth*(tileNum + 1), 0);

		for (int i = 0; i < 10; i++) {
			m2->setMap("던전_머크우드_지형_나무_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("던전_머크우드_지형_나무_4")->getWidth()), -rand() % 50 - 50);
		}


		m2->setWidth(tilewidth*(tileNum + 2));
		m2->setHeight(IMAGEMANAGER->findImage("던전_머크우드_바닥_0")->getHeight());
		m2->setTileNumX(m2->getWidth() / 50 + 1);
		m2->setTileNumY(m2->getHeight() / 50 + 1);
		for (int y = 0; y < m2->getTileNumY() / 2 +1; y++) {
			for (int x = 0; x < m2->getTileNumX(); x++) {
				MapTile t;
				t.rc = RectMake(x * 50, y * 50, 50, 50);
				t.type = -1;
				m2->addMapTile(t);
			}
		}

	}
	/////////////////////////////////////////////////////////////////////////////3번째 맵 처리
	{
		int tileNum = 7;
		for (int i = 0; i < tileNum; i++) {
			m3->setMap("던전_머크우드_배경_뒤", IMAGEMANAGER->findImage("던전_머크우드_배경_뒤")->getWidth() * i, 0);
			m3->setMap("던전_머크우드_배경_중간", IMAGEMANAGER->findImage("던전_머크우드_배경_뒤")->getWidth() * i, 0);
		}
		m3->setMap("던전_머크우드_바닥_1", 0, 0);
		for (int i = 0; i < tileNum; i++) {
			m3->setMap("던전_머크우드_바닥_2", tilewidth + tilewidth * i, 0);
		}
		m3->setMap("던전_머크우드_바닥_3", tilewidth*(tileNum + 1), 0);

		for (int i = 0; i < 10; i++) {
			m3->setMap("던전_머크우드_지형_나무_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("던전_머크우드_지형_나무_4")->getWidth()), -rand() % 50 - 50);
		}


		m3->setWidth(tilewidth*(tileNum + 2));
		m3->setHeight(IMAGEMANAGER->findImage("던전_머크우드_바닥_0")->getHeight());
		m3->setTileNumX(m3->getWidth() / 50 + 1);
		m3->setTileNumY(m3->getHeight() / 50 + 1);

		for (int y = 0; y < m3->getTileNumY() / 2 +1; y++) {
			for (int x = 0; x < m3->getTileNumX(); x++) {
				MapTile t;
				t.rc = RectMake(x * 50, y * 50, 50, 50);
				t.type = -1;
				m3->addMapTile(t);
			}
		}
	}
	Maps.push_back(m1);
	Maps.push_back(m2);
	Maps.push_back(m3);
	curMap = m1;
}

void Mirkwood::update()
{
	curMap->update();
}

void Mirkwood::render()
{
	curMap->render();
}

void Mirkwood::renderz()
{
	curMap->renderz();
}

void Mirkwood::renderdc()
{
}

Mirkwood::Mirkwood()
{
}


Mirkwood::~Mirkwood()
{
}
///////////////////////////////////////////////////////////////머크우드 세부맵


void MirkwoodMap::init()
{
}

void MirkwoodMap::update()
{
}

void MirkwoodMap::render()
{
	for (vector<ImgTile>::iterator i = staticTiles.begin(); i != staticTiles.end(); i++) {
		i->tileImg->render(i->pos.x - cam.x, i->pos.y - cam.y);
	}
}

void MirkwoodMap::renderz()
{
	for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
		IMAGEMANAGER->findImage("X표시")->render(i->rc.left -cam.x, i->rc.top -cam.y);
	}
}

void MirkwoodMap::renderdc()
{
}

void MirkwoodMap::setMap(const char* tileName, int x, int y)
{
	ImgTile t;
	t.tileImg = IMAGEMANAGER->findImage(tileName);
	t.pos = pointMake(x,y);
	staticTiles.push_back(t);
}
