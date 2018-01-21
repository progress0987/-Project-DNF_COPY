#include "stdafx.h"
#include "Mirkwood.h"


HRESULT Mirkwood::init()
{
	//MapBase::init();
	peaceful = false;
	runnable = true;
	attackable = true;



	MirkwoodMap* m1 = new MirkwoodMap;
	MirkwoodMap* m2 = new MirkwoodMap;
	MirkwoodMap* m3 = new MirkwoodMap;
	
	tilewidth = IMAGEMANAGER->findImage("던전_머크우드_바닥_0")->getWidth();
	/////////////////////////////////////////////////////////////////////////1번째 맵 처리
	{
		m1->init();
		m1->setPlayer(pl);
		m1->setPeaceful(false);
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
		for (int i = 0; i < 1; i++) {
			green_goblin* g = new green_goblin();
			g->setCurmap(m1);
			g->init(800+i*100,(WINSIZEY - 50)*2);
			m1->addMonster(g);
		}
	}
	/////////////////////////////////////////////////////////////////////2번째 맵 처리
	{
		m2->init();
		m2->setPlayer(pl);
		m2->setPeaceful(false);
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

		for (int i = 0; i < 5; i++) {
			green_goblin* g = new green_goblin();
			g->setCurmap(m2);
			g->init(800 + i * 150, (WINSIZEY - 50) * 2);
			m2->addMonster(g);
		}

	}
	/////////////////////////////////////////////////////////////////////////////3번째 맵 처리
	{
		m3->init();
		m3->setPlayer(pl);
		m3->setPeaceful(false);
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


		for (int i = 0; i < 5; i++) {
			green_goblin* g = new green_goblin();
			g->setCurmap(m3);
			g->init(800 + i * 150, (WINSIZEY - 50) * 2);
			m3->addMonster(g);
		}

	}
	conNodes node;
	node.nextNode = m1;
	node.pos = (pointMake(WINSIZEX/2, (WINSIZEY-50)*2));
	connectedNodes.push_back(node);

	node.nextNode = m2;
	node.pos = (pointMake(WINSIZEX / 2, (WINSIZEY - 50) * 2));
	connectedNodes.push_back(node);

	node.nextNode = m3;
	node.pos = (pointMake(WINSIZEX / 2, (WINSIZEY - 50) * 2));
	connectedNodes.push_back(node);


	curMap = m1;
	return S_OK;
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


HRESULT MirkwoodMap::init()
{
	MapBase::init();
	return S_OK;
}

void MirkwoodMap::update()
{
	monBack.clear();
	monFront.clear();
	for (vector<MonsterBase*>::iterator i = monsterList.begin(); i!=monsterList.end();i++ ){
		(*i)->update();
		if ((*i)->getZ() < pl->getZ())monBack.push_back((*i));
		else if ((*i)->getZ() >= pl->getZ())monFront.push_back((*i));
	}
	MapBase::update();
}

void MirkwoodMap::render()
{
	for (vector<ImgTile>::iterator i = staticTiles.begin(); i != staticTiles.end(); i++) {
		i->tileImg->render(i->pos.x - cam.x, i->pos.y - cam.y);
	}
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++) {
		switch (i->item.type) {
		case item_coat: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("아이템_필드_판금_상의")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_pants: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("아이템_필드_판금_하의")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_shoulder: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("아이템_필드_판금_어깨")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_belt: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("아이템_필드_판금_벨트")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_shoes: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("아이템_필드_판금_신발")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_weapon: {
			switch (i->item.detail) {
			case wp_sswd:
				IMAGEMANAGER->findImage("아이템_필드_소검")->DFpointrotatedrender(i->x - cam.x, (i->y + translate(i->z)) - cam.y, i->angle, 24, 10);
				break;
			}
			break;
		}
		case item_consume: {
			IMAGEMANAGER->findImage("아이템_필드_소모품")->DFpointrotatedrender(i->x - cam.x, (i->y + translate(i->z)) - cam.y, i->angle, 7, 10);
			break;
		}
		}
		//IMAGEMANAGER->findImage("아이템_필드_판금_상의")->rotatedrender(i->x - cam.x, i->y -cam.y + translate(i->z), i->angle);
	}
	for (vector<MonsterBase*>::iterator i = monBack.begin(); i != monBack.end(); i++) {
		(*i)->render();
	}

	pl->render();

	for (vector<MonsterBase*>::iterator i = monFront.begin(); i != monFront.end(); i++) {
		(*i)->render();
	}

	renderz();
	renderdc();
}

void MirkwoodMap::renderz()
{
	

	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	IMAGEMANAGER->findImage("X표시")->render(i->rc.left -cam.x, i->rc.top -cam.y);
	//}
}

void MirkwoodMap::renderdc()
{
	char tmp[50];


	for (vector<MonsterBase*>::iterator i = monBack.begin(); i != monBack.end(); i++) {
		(*i)->renderdc();
	}


	for (vector<MonsterBase*>::iterator i = monFront.begin(); i != monFront.end(); i++) {
		(*i)->renderdc();
	}

	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++) {
		int offset = -i->item.name.length() * 8;
		if (i->x - 30 < pl->getX() && pl->getX() < i->x + 30 &&
			i->z - 30 < pl->getZ() && pl->getZ() < i->z + 30) {
			drawWindow(i->x + offset / 2 - cam.x, i->y + translate(i->z) - 50 - cam.y, (-(offset)), 20);
		}
		drawWindow(i->x + offset / 2 - cam.x, i->y + translate(i->z) - 50 - cam.y, (-(offset)), 20);
		{
			sprintf(tmp, "%s",i->item.name.c_str());
			d3dFont->DrawTextA(
				NULL,
				tmp,
				-1,
				&RectMake(i->x +offset/2 -cam.x,i->y + translate(i->z) - 50 -cam.y,(-(offset)),20),
				DT_CENTER | DT_VCENTER,
				D3DCOLOR_ARGB(0xff, 0x99, 0x99, 0x99));
		}

	}

}

void MirkwoodMap::setMap(const char* tileName, int x, int y)
{
	ImgTile t;
	t.tileImg = IMAGEMANAGER->findImage(tileName);
	t.pos = pointMake(x,y);
	staticTiles.push_back(t);
}
