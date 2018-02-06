#include "stdafx.h"
#include "lorienDeep.h"
#include "green_goblin.h"
#include "goblin_thrower.h"
#include "Tauamy.h"
#include "TauAssaulter.h"


HRESULT lorienDeep::init()
{
	peaceful = false;
	runnable = true;
	attackable = true;
	showresult = false;



	lorienDeepMap* m1 = new lorienDeepMap;
	lorienDeepMap* m2 = new lorienDeepMap;
	lorienDeepMap* m3 = new lorienDeepMap;
	lorienDeepMap* m4 = new lorienDeepMap;
	lorienDeepMap* m5 = new lorienDeepMap;
	lorienDeepMap* m6 = new lorienDeepMap;

	MapTile t;
	tilewidth = IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getWidth();
	int zheight;
#pragma region 1����
	m1->init();
	m1->isfirstmap = true;
	m1->setPlayer(pl);
	m1->setPeaceful(false);
	int tileNum = 4;
	for (int i = 0; i < tileNum; i++) {
		m1->setMap("����_��ũ���_���_��", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
		m1->setMap("����_��ũ���_���_�߰�", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
	}
	m1->setMap("����_��ũ���_�ٴ�_1", 0, 0);
	for (int i = 0; i < tileNum; i++) {
		m1->setMap("����_��ũ���_�ٴ�_2", tilewidth + tilewidth * i, 0);
	}
	m1->setMap("����_��ũ���_�ٴ�_3", tilewidth*(tileNum + 1), 0);

	for (int i = 0; i < 10; i++) {
		m1->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50 - 50);
	}


	m1->setWidth(tilewidth*(tileNum + 2));
	m1->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());
	zheight = m1->getHeight() + 200;
	m1->setMaxX(m1->getWidth() - 50);
	m1->setMinX(50);
	m1->setMaxZ(m1->getHeight() * 2 - 100);
	m1->setMinZ(zheight);

	m1->setTileNumX(m1->getWidth() / 50 + 1);
	m1->setTileNumY(m1->getHeight() / 50 + 1);
	t.type = -1;
	t.moveindex = -1;
	t.rc = RectMake(0, 0, m1->getWidth(), 330);
	m1->addMapTile(t);

	t.rc = RectMake(0, 0, 40, m1->getHeight());
	m1->addMapTile(t); 


	t.rc = RectMake(m1->getWidth() - 180, 0, 500, 416);
	m1->addMapTile(t);
	t.rc = RectMake(m1->getWidth() - 50, 0, 50, m1->getHeight());
	m1->addMapTile(t);
	t.rc = RectMake(m1->getWidth() - 160, 468, 500, m1->getHeight() - 468);
	m1->addMapTile(t);

	for (int i = 0; i < 4; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m1);
		g->init(800 + (rand()%30)*10, (WINSIZEY - 50) * 2 - rand() % 300);
		m1->addMonster(g);
	}
	for (int i = 0; i < 1; i++) {
		goblin_thrower* th = new goblin_thrower();
		th->setCurmap(m1);
		th->init(750, (WINSIZEY - 100) * 2);
		m1->addMonster(th);
	}

	conNode node;
	node.nextNode = m2;
	node.x = m1->getWidth()/2;
	node.z = 492 * 2;
	dungeonGate gateinfo;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m1->getWidth()/2 - IMAGEMANAGER->findImage("����_��_��")->getWidth()/2;
	gateinfo.y = 156;
	gateinfo.moveRect = RectMake(gateinfo.x + 54, gateinfo.y + 176, 58, 15);
	m1->setConNode(gateinfo, 0);
	//////////////////////////////////////////////////////////////////////////������ ��

	node.nextNode = m3;
	node.x = 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m1->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m1->setConNode(gateinfo, 1);
	////////////////////////////////////////////////////////////////////////��Ȱ��
	gateinfo.isShow = false;
	gateinfo.movable = false;
	m1->setConNode(gateinfo, 2);
	m1->setConNode(gateinfo, 3);
#pragma endregion

#pragma region 2����
	m2->init();
	m2->isfirstmap = false;
	m2->setPlayer(pl);
	m2->setPeaceful(false);
	tileNum = 4;
	for (int i = 0; i < tileNum; i++) {
		m2->setMap("����_��ũ���_���_��", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
		m2->setMap("����_��ũ���_���_�߰�", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
	}
	m2->setMap("����_��ũ���_�ٴ�_1", 0, 0);
	for (int i = 0; i < tileNum; i++) {
		m2->setMap("����_��ũ���_�ٴ�_2", tilewidth + tilewidth * i, 0);
	}
	m2->setMap("����_��ũ���_�ٴ�_3", tilewidth*(tileNum + 1), 0);

	for (int i = 0; i < 10; i++) {
		m2->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50 - 50);
	}


	m2->setWidth(tilewidth*(tileNum + 2));
	m2->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());
	zheight = m2->getHeight() + 200;
	m2->setMaxX(m2->getWidth() - 50);
	m2->setMinX(50);
	m2->setMaxZ(m2->getHeight() * 2 - 100);
	m2->setMinZ(zheight);

	m2->setTileNumX(m2->getWidth() / 50 + 1);
	m2->setTileNumY(m2->getHeight() / 50 + 1);
	t.type = -1;
	t.moveindex = -1;
	t.rc = RectMake(0, 0, m2->getWidth(), 330);
	m2->addMapTile(t);

	t.rc = RectMake(0, 0, 40, m2->getHeight());
	m2->addMapTile(t);


	t.rc = RectMake(m2->getWidth() - 180, 0, 500, 416);
	m2->addMapTile(t);
	t.rc = RectMake(m2->getWidth() - 50, 0, 50, m2->getHeight());
	m2->addMapTile(t);
	t.rc = RectMake(m2->getWidth() - 160, 468, 500, m2->getHeight() - 468);
	m2->addMapTile(t);

	for (int i = 0; i < 5; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m2);
		g->init(800 + (rand() % 30) * 10, (WINSIZEY - 50) * 2 - rand() % 300);
		m2->addMonster(g);
	}
	for (int i = 0; i < 2; i++) {
		goblin_thrower* th = new goblin_thrower();
		th->setCurmap(m2);
		th->init(750+(rand()%15)*20, (WINSIZEY - 100) * 2);
		m2->addMonster(th);
	}

	//////////////////////////////////////////////////////////////////////////�Ʒ��� ��
	node.nextNode = m1;
	node.x = m2->getWidth() / 2;
	node.z = 381 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m2->getWidth() / 2 - IMAGEMANAGER->findImage("����_��_�Ʒ�")->getWidth() / 2;
	gateinfo.y = m2->getHeight() - IMAGEMANAGER->findImage("����_��_�Ʒ�")->getHeight();
	gateinfo.moveRect = RectMake(gateinfo.x + 70, gateinfo.y + 95, 65, 27);
	m2->setConNode(gateinfo, 2);
	//////////////////////////////////////////////////////////////////////////������ ��

	node.nextNode = m4;
	node.x = 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m2->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m2->setConNode(gateinfo, 1);
	////////////////////////////////////////////////////////////////////////��Ȱ��
	gateinfo.isShow = false;
	gateinfo.movable = false;
	m2->setConNode(gateinfo, 0);
	m2->setConNode(gateinfo, 3);
#pragma endregion

#pragma region 3����
	m3->init();
	m3->isfirstmap = false;
	m3->setPlayer(pl);
	m3->setPeaceful(false);
	tileNum = 4;
	for (int i = 0; i < tileNum; i++) {
		m3->setMap("����_��ũ���_���_��", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
		m3->setMap("����_��ũ���_���_�߰�", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
	}
	m3->setMap("����_��ũ���_�ٴ�_1", 0, 0);
	for (int i = 0; i < tileNum; i++) {
		m3->setMap("����_��ũ���_�ٴ�_2", tilewidth + tilewidth * i, 0);
	}
	m3->setMap("����_��ũ���_�ٴ�_3", tilewidth*(tileNum + 1), 0);

	for (int i = 0; i < 10; i++) {
		m3->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50 - 50);
	}


	m3->setWidth(tilewidth*(tileNum + 2));
	m3->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());
	zheight = m3->getHeight() + 200;
	m3->setMaxX(m3->getWidth() - 50);
	m3->setMinX(50);
	m3->setMaxZ(m3->getHeight() * 2 - 100);
	m3->setMinZ(zheight);

	m3->setTileNumX(m3->getWidth() / 50 + 1);
	m3->setTileNumY(m3->getHeight() / 50 + 1);
	t.type = -1;
	t.moveindex = -1;
	t.rc = RectMake(0, 0, m3->getWidth(), 330);
	m3->addMapTile(t);

	t.rc = RectMake(0, 0, 40, m3->getHeight());
	m3->addMapTile(t);

	t.rc = RectMake(0, 0, 69, 423);
	m3->addMapTile(t);
	t.rc = RectMake(0, 0, 30, m3->getHeight());
	m3->addMapTile(t);
	t.rc = RectMake(0, 459, 105, m3->getHeight() - 459);
	m3->addMapTile(t);

	t.rc = RectMake(m3->getWidth() - 180, 0, 500, 416);
	m3->addMapTile(t);
	t.rc = RectMake(m3->getWidth() - 50, 0, 50, m3->getHeight());
	m3->addMapTile(t);
	t.rc = RectMake(m3->getWidth() - 160, 468, 500, m3->getHeight() - 468);
	m3->addMapTile(t);

	for (int i = 0; i < 4; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m3);
		g->init(800 + (rand() % 30) * 10, (WINSIZEY - 50) * 2 - rand() % 300);
		m3->addMonster(g);
	}
	for (int i = 0; i < 3; i++) {
		goblin_thrower* th = new goblin_thrower();
		th->setCurmap(m3);
		th->init(700 + (rand()%5 * 30), (WINSIZEY - 100) * 2);
		m3->addMonster(th);
	}

	//////////////////////////////////////////////////////////////////////////���� ��
	node.nextNode = m4;
	node.x = m3->getWidth() / 2;
	node.z = 492 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m3->getWidth() / 2 - IMAGEMANAGER->findImage("����_��_��")->getWidth() / 2;
	gateinfo.y = 156;
	gateinfo.moveRect = RectMake(gateinfo.x + 54, gateinfo.y + 176, 58, 15);
	m3->setConNode(gateinfo, 0);
	//////////////////////////////////////////////////////////////////////////������ ��

	node.nextNode = m5;
	node.x = 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = true;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m3->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m3->setConNode(gateinfo, 1);
	//////////////////////////////////////////////////////////////////////////���ʹ�
	node.nextNode = m1;
	node.x = m1->getWidth() - 160;
	node.z = 423 * 2;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.con = node;
	gateinfo.x = 0;
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m3->setConNode(gateinfo, 3);
	////////////////////////////////////////////////////////////////////////��Ȱ��
	gateinfo.isShow = false;
	gateinfo.movable = false;
	m3->setConNode(gateinfo, 2);
#pragma endregion

#pragma region 4����
	m4->init();
	m4->isfirstmap = false;
	m4->setPlayer(pl);
	m4->setPeaceful(false);
	tileNum = 4;
	for (int i = 0; i < tileNum; i++) {
		m4->setMap("����_��ũ���_���_��", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
		m4->setMap("����_��ũ���_���_�߰�", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
	}
	m4->setMap("����_��ũ���_�ٴ�_1", 0, 0);
	for (int i = 0; i < tileNum; i++) {
		m4->setMap("����_��ũ���_�ٴ�_2", tilewidth + tilewidth * i, 0);
	}
	m4->setMap("����_��ũ���_�ٴ�_3", tilewidth*(tileNum + 1), 0);

	for (int i = 0; i < 10; i++) {
		m4->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50 - 50);
	}


	m4->setWidth(tilewidth*(tileNum + 2));
	m4->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());
	zheight = m4->getHeight() + 200;
	m4->setMaxX(m4->getWidth() - 50);
	m4->setMinX(50);
	m4->setMaxZ(m4->getHeight() * 2 - 100);
	m4->setMinZ(zheight);

	m4->setTileNumX(m4->getWidth() / 50 + 1);
	m4->setTileNumY(m4->getHeight() / 50 + 1);
	t.type = -1;
	t.moveindex = -1;
	t.rc = RectMake(0, 0, m4->getWidth(), 330);
	m4->addMapTile(t);

	t.rc = RectMake(0, 0, 40, m4->getHeight());
	m4->addMapTile(t);

	t.rc = RectMake(0, 0, 69, 423);
	m4->addMapTile(t);
	t.rc = RectMake(0, 0, 30, m4->getHeight());
	m4->addMapTile(t);
	t.rc = RectMake(0, 459, 105, m4->getHeight() - 459);
	m4->addMapTile(t);

	t.rc = RectMake(m4->getWidth() - 180, 0, 500, 416);
	m4->addMapTile(t);
	t.rc = RectMake(m4->getWidth() - 50, 0, 50, m4->getHeight());
	m4->addMapTile(t);
	t.rc = RectMake(m4->getWidth() - 160, 468, 500, m4->getHeight() - 468);
	m4->addMapTile(t);

	for (int i = 0; i < 4; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m4);
		g->init(800 + (rand() % 30) * 10, (WINSIZEY - 50) * 2 - rand() % 300);
		m4->addMonster(g);
	}
	for (int i = 0; i < 3; i++) {
		goblin_thrower* th = new goblin_thrower();
		th->setCurmap(m4);
		th->init(700 + (rand() % 5 * 30), (WINSIZEY - 100) * 2);
		m4->addMonster(th);
	}

	//////////////////////////////////////////////////////////////////////////�Ʒ� ��

	node.nextNode = m3;
	node.x = m4->getWidth() / 2;
	node.z = 381 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m4->getWidth() / 2 - IMAGEMANAGER->findImage("����_��_�Ʒ�")->getWidth() / 2;
	gateinfo.y = m4->getHeight() - IMAGEMANAGER->findImage("����_��_�Ʒ�")->getHeight();
	gateinfo.moveRect = RectMake(gateinfo.x + 70, gateinfo.y + 95, 65, 27);
	m4->setConNode(gateinfo, 2);
	//////////////////////////////////////////////////////////////////////////������ ��

	node.nextNode = m6;
	node.x = 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m4->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m4->setConNode(gateinfo, 1);
	//////////////////////////////////////////////////////////////////////////���ʹ�
	node.nextNode = m2;
	node.x = m4->getWidth() - 160;
	node.z = 423 * 2;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.con = node;
	gateinfo.x = 0;
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m4->setConNode(gateinfo, 3);
	////////////////////////////////////////////////////////////////////////��Ȱ��
	gateinfo.isShow = false;
	gateinfo.movable = false;
	m4->setConNode(gateinfo, 0);
#pragma endregion

#pragma region 5����
	m5->init();
	m5->isfirstmap = false;
	m5->setPlayer(pl);
	m5->setPeaceful(false);
	for (int i = 0; i < tileNum; i++) {
		m5->setMap("����_��ũ���_���_��", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
		m5->setMap("����_��ũ���_���_�߰�", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
	}
	m5->setMap("����_��ũ���_�ٴ�_1", 0, 0);
	for (int i = 0; i < tileNum; i++) {
		m5->setMap("����_��ũ���_�ٴ�_2", tilewidth + tilewidth * i, 0);
	}
	m5->setMap("����_��ũ���_�ٴ�_3", tilewidth*(tileNum + 1), 0);

	for (int i = 0; i < 10; i++) {
		m5->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50 - 50);
	}


	m5->setWidth(tilewidth*(tileNum + 2));
	m5->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());

	m5->setMaxX(m5->getWidth() - 50);
	m5->setMinX(50);
	m5->setMaxZ(m5->getHeight() * 2 - 100);
	m5->setMinZ(zheight);

	m5->setTileNumX(m5->getWidth() / 50 + 1);
	m5->setTileNumY(m5->getHeight() / 50 + 1);

	t.type = -1;
	for (int y = 0; y < m5->getTileNumY() / 2 + 1; y++) {
		for (int x = 0; x < m5->getTileNumX(); x++) {
			t.rc = RectMake(x * 50, y * 50, 50, 50);
			m5->addMapTile(t);
		}
	}

	t.type = -1;
	t.rc = RectMake(0, 0, 69, 423);
	m5->addMapTile(t);
	t.rc = RectMake(0, 0, 30, m5->getHeight());
	m5->addMapTile(t);
	t.rc = RectMake(0, 459, 105, m5->getHeight() - 459);
	m5->addMapTile(t);

	t.rc = RectMake(m5->getWidth() - 50, 0, 50, m5->getHeight());
	m5->addMapTile(t);

	for (int i = 0; i < 5; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m4);
		g->init(800 + (rand() % 30) * 10, (WINSIZEY - 50) * 2 - rand() % 300);
		m5->addMonster(g);
	}
	for (int i = 0; i < 3; i++) {
		goblin_thrower* th = new goblin_thrower();
		th->setCurmap(m4);
		th->init(700 + (rand() % 5 * 30), (WINSIZEY - 100) * 2);
		m5->addMonster(th);
	}
	Tau* tauamy = new Tau();
	tauamy->setCurmap(m5);
	tauamy->init(1000, 350 * 2);
	m5->addMonster(tauamy);
	m5->setBoss(tauamy);

	node.nextNode = m3;
	node.x = m3->getWidth() - 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = true;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.x = 0;
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m5->setConNode(gateinfo, 3);
	gateinfo.isShow = false;
	m5->setConNode(gateinfo, 0);
	m5->setConNode(gateinfo, 2);
	m5->setConNode(gateinfo, 1);

#pragma endregion

#pragma region 6����
	m6->init();
	m6->isfirstmap = false;
	m6->setPlayer(pl);
	m6->setPeaceful(false);
	for (int i = 0; i < tileNum; i++) {
		m6->setMap("����_��ũ���_���_��", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
		m6->setMap("����_��ũ���_���_�߰�", IMAGEMANAGER->findImage("����_��ũ���_���_��")->getWidth() * i, 0);
	}
	m6->setMap("����_��ũ���_�ٴ�_1", 0, 0);
	for (int i = 0; i < tileNum; i++) {
		m6->setMap("����_��ũ���_�ٴ�_2", tilewidth + tilewidth * i, 0);
	}
	m6->setMap("����_��ũ���_�ٴ�_3", tilewidth*(tileNum + 1), 0);

	for (int i = 0; i < 10; i++) {
		m6->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum + 2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50 - 50);
	}


	m6->setWidth(tilewidth*(tileNum + 2));
	m6->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());

	m6->setMaxX(m6->getWidth() - 50);
	m6->setMinX(50);
	m6->setMaxZ(m6->getHeight() * 2 - 100);
	m6->setMinZ(zheight);

	m6->setTileNumX(m6->getWidth() / 50 + 1);
	m6->setTileNumY(m6->getHeight() / 50 + 1);

	t.type = -1;
	for (int y = 0; y < m6->getTileNumY() / 2 + 1; y++) {
		for (int x = 0; x < m6->getTileNumX(); x++) {
			t.rc = RectMake(x * 50, y * 50, 50, 50);
			m6->addMapTile(t);
		}
	}

	t.type = -1;
	t.rc = RectMake(0, 0, 69, 423);
	m6->addMapTile(t);
	t.rc = RectMake(0, 0, 30, m6->getHeight());
	m6->addMapTile(t);
	t.rc = RectMake(0, 459, 105, m6->getHeight() - 459);
	m6->addMapTile(t);

	t.rc = RectMake(m6->getWidth() - 180, 0, 500, 416);
	m6->addMapTile(t);
	t.rc = RectMake(m6->getWidth() - 50, 0, 50, m6->getHeight());
	m6->addMapTile(t);
	t.rc = RectMake(m6->getWidth() - 160, 468, 500, m6->getHeight() - 468);
	m6->addMapTile(t);

	for (int i = 0; i < 6; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m6);
		g->init(800 + (rand() % 30) * 10, (WINSIZEY - 50) * 2 - rand() % 300);
		m6->addMonster(g);
	}
	for (int i = 0; i < 5; i++) {
		goblin_thrower* th = new goblin_thrower();
		th->setCurmap(m6);
		th->init(700 + (rand() % 5 * 30), (WINSIZEY - 100) * 2);
		m6->addMonster(th);
	}

	TauAssaulter* ta = new TauAssaulter();
	ta->setCurmap(m6);
	ta->init(800 - 100, WINSIZEY * 2 - 300);
	m6->addMonster(ta);

	node.nextNode = m4;
	node.x = m4->getWidth() - 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.x = 0;
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m6->setConNode(gateinfo, 3);
	gateinfo.isShow = false;
	m6->setConNode(gateinfo, 0);
	m6->setConNode(gateinfo, 2);
	m6->setConNode(gateinfo, 1);

#pragma endregion





	Maps.push_back(m1);
	Maps.push_back(m2);
	Maps.push_back(m3);
	Maps.push_back(m4);
	Maps.push_back(m5);
	Maps.push_back(m6);

	curMap = Maps[0];
	return S_OK;
}

void lorienDeep::update()
{
}

void lorienDeep::render()
{
}

void lorienDeep::renderz()
{
}

void lorienDeep::renderdc()
{
}

void lorienDeep::resetDungeon()
{
	for (vector<MapBase*>::iterator i = Maps.begin(); i != Maps.end(); i++) {
		(*i)->resetMonsters();
		(*i)->resetDungeon();
	}
}

lorienDeep::lorienDeep()
{
}


lorienDeep::~lorienDeep()
{
}

HRESULT lorienDeepMap::init()
{
	movable = false;
	peaceful = false;
	runnable = true;
	attackable = true;
	showresult = false;
	showdungeonName = false;
	playendsound = playedendsound = false;
	dunshowTick = 0;
	isBossMap = false;
	MapBase::init();
	return S_OK;
}

void lorienDeepMap::update()
{
	monBack.clear();
	monFront.clear();
	if (showdungeonName&& beginTime + 8000 > GetTickCount()) {
		if (GetTickCount() % 50 == 0) {
			dunshowTick++;
			if (dunshowTick > 13) {
				dunshowTick = 0;
			}
		}
	}
	else {
		showdungeonName = false;
	}
	for (vector<MonsterBase*>::iterator i = monsterList.begin(); i != monsterList.end(); ) {
		(*i)->update();
		if ((*i)->isDead) {							//�׾����� ������
			i = monsterList.erase(i);
			if (monsterList.size() == 0) {
				peaceful = true;
				pl->setOnCombat(!peaceful);
				for (int i = 0; i < 4; i++) {
					if (!Gates[i].isShow) continue;
					Gates[i].movable = true;
				}
			}
		}
		else {
			if ((*i)->getZ() < pl->getZ())monBack.push_back(*i);
			else if ((*i)->getZ() >= pl->getZ())monFront.push_back(*i);
			i++;
		}
	}
	MapBase::update();
	if (playendsound && !SOUNDMANAGER->isPlaySound("ȿ��_������")) {
		SOUNDMANAGER->play("ȿ��_������");
		SOUNDMANAGER->stop("BGM_����_����");
		playedendsound = true;
		playendsound = false;
	}
	if (isBossMap) {
		if (!SOUNDMANAGER->isPlaySound("BGM_����_����") && !playedendsound) {
			playBGM("BGM_����_����");
		}
		if (Boss->getCurStat() == mon_onDead) {
			if (!playedendsound && !playendsound)		playendsound = true;
			showresult = true;
			for (vector<MonsterBase*>::iterator i = monsterList.begin(); i != monsterList.end(); i++) {
				(*i)->setCurStat(mon_onDeadProcess);
			}
		}
	}
	else {
		if (!SOUNDMANAGER->isPlaySound("BGM_����_�Ϲ�"))
			playBGM("BGM_����_�Ϲ�");
	}
}

void lorienDeepMap::render()
{
	for (vector<ImgTile>::iterator i = staticTiles.begin(); i != staticTiles.end(); i++) {
		i->tileImg->render(i->pos.x - cam.x, i->pos.y - cam.y);
	}
	//����Ʈ�� �׷��ֱ�
	if (Gates[0].isShow) {				// ����
		if (Gates[0].isBoss) {
			IMAGEMANAGER->findImage("����_������_��")->render(Gates[0].x - cam.x, Gates[0].y - cam.y);
			if (!Gates[0].movable)
				IMAGEMANAGER->findImage("����_������_��_â��")->render(Gates[0].x - cam.x, Gates[0].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_������_��_��")->render(Gates[0].x - cam.x, Gates[0].y - cam.y);

		}
		else {
			IMAGEMANAGER->findImage("����_��_��")->render(Gates[0].x - cam.x, Gates[0].y - cam.y);
			if (!Gates[0].movable)
				IMAGEMANAGER->findImage("����_��_��_â��")->render(Gates[0].x - cam.x, Gates[0].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_��_��_��")->render(Gates[0].x - cam.x, Gates[0].y - cam.y);

		}
	}
	if (Gates[1].isShow) {
		if (Gates[1].isBoss) {
			IMAGEMANAGER->findImage("����_������_���̵�")->render(Gates[1].x - cam.x, Gates[1].y - cam.y);
			if (!Gates[1].movable)
				IMAGEMANAGER->findImage("����_������_���̵�_â��")->render(Gates[1].x - cam.x, Gates[1].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_������_���̵�_��")->render(Gates[1].x - cam.x, Gates[1].y - cam.y);

		}
		else {
			IMAGEMANAGER->findImage("����_��_���̵�")->render(Gates[1].x - cam.x, Gates[1].y - cam.y);
			if (!Gates[1].movable)
				IMAGEMANAGER->findImage("����_��_���̵�_â��")->render(Gates[1].x - cam.x, Gates[1].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_��_���̵�_��")->render(Gates[1].x - cam.x, Gates[1].y - cam.y);
		}
	}
	for (vector<DropItemStruct>::iterator i = dropList.begin(); i != dropList.end(); i++) {
		//����϶���
		if (i->isGold) {
			if (i->goldamount < 10) {
				IMAGEMANAGER->findImage("������_�ʵ�_���_1")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 5, 3);
			}
			else if (i->goldamount < 100) {
				IMAGEMANAGER->findImage("������_�ʵ�_���_2")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 13, 9);
			}
			else {
				IMAGEMANAGER->findImage("������_�ʵ�_���_3")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 10, 9);
			}
			continue;
		}

		switch (i->item.type) {
		case item_coat: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("������_�ʵ�_�Ǳ�_����")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_pants: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("������_�ʵ�_�Ǳ�_����")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_shoulder: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("������_�ʵ�_�Ǳ�_���")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_belt: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("������_�ʵ�_�Ǳ�_��Ʈ")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_shoes: {
			switch (i->item.detail) {
			case arm_plate:
				IMAGEMANAGER->findImage("������_�ʵ�_�Ǳ�_�Ź�")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle, 60, 60);
				break;
			}
			break;
		}
		case item_weapon: {
			switch (i->item.detail) {
			case wp_sswd:
				IMAGEMANAGER->findImage("������_�ʵ�_�Ұ�")->DFpointrotatedrender(i->x - cam.x, (i->y + translate(i->z)) - cam.y, i->angle, 24, 10);
				break;
			}
			break;
		}
		case item_consume: {
			IMAGEMANAGER->findImage("������_�ʵ�_�Ҹ�ǰ")->DFpointrotatedrender(i->x - cam.x, (i->y + translate(i->z)) - cam.y, i->angle, 7, 10);
			break;
		}
		}
	}
	for (vector<MonsterBase*>::iterator i = monBack.begin(); i != monBack.end(); i++) {
		(*i)->render();
	}

	pl->render();

	for (vector<MonsterBase*>::iterator i = monFront.begin(); i != monFront.end(); i++) {
		(*i)->render();
	}

	//�Ʒ��� ���� ����Ʈ
	if (Gates[2].isShow) {
		if (Gates[2].isBoss) {
			IMAGEMANAGER->findImage("����_������_�Ʒ�")->render(Gates[2].x - cam.x, Gates[2].y - cam.y);
			if (!Gates[2].movable)
				IMAGEMANAGER->findImage("����_������_�Ʒ�_â��")->render(Gates[2].x - cam.x, Gates[2].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_������_�Ʒ�_��")->render(Gates[2].x - cam.x, Gates[2].y - cam.y);

		}
		else {
			IMAGEMANAGER->findImage("����_��_�Ʒ�")->render(Gates[2].x - cam.x, Gates[2].y - cam.y);
			if (!Gates[2].movable)
				IMAGEMANAGER->findImage("����_��_�Ʒ�_â��")->render(Gates[2].x - cam.x, Gates[2].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_��_�Ʒ�_��")->render(Gates[2].x - cam.x, Gates[2].y - cam.y);
		}
	}
	//�������� ���� ����Ʈ
	if (Gates[3].isShow) {
		if (Gates[3].isBoss) {
			IMAGEMANAGER->findImage("����_������_���̵�")->render(Gates[3].x - cam.x, Gates[3].y - cam.y);
			if (!Gates[3].movable)
				IMAGEMANAGER->findImage("����_������_���̵�_â��")->render(Gates[3].x - cam.x, Gates[3].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_������_���̵�_��")->render(Gates[3].x - cam.x, Gates[3].y - cam.y);

		}
		else {
			IMAGEMANAGER->findImage("����_��_���̵�")->render(Gates[3].x - cam.x, Gates[3].y - cam.y);
			if (!Gates[3].movable)
				IMAGEMANAGER->findImage("����_��_���̵�_â��")->render(Gates[3].x - cam.x, Gates[3].y - cam.y);
			else
				IMAGEMANAGER->findImage("����_��_���̵�_��")->render(Gates[3].x - cam.x, Gates[3].y - cam.y);
		}
	}
	renderz();
	renderdc();
}

void lorienDeepMap::renderz()
{
	char tmp[50];
	if (showdungeonName) {
		sprintf(tmp, "����_�θ�������_�̸�_%d", dunshowTick);
		if (GetTickCount() < beginTime + 512) {
			IMAGEMANAGER->findImage(tmp)->blurredrender(WINSIZEX / 2 - 130, WINSIZEY / 2 - 40, (GetTickCount() - beginTime) / 2);
		}
		else if (GetTickCount() > beginTime + 8000 - 512) {
			IMAGEMANAGER->findImage(tmp)->blurredrender(WINSIZEX / 2 - 130, WINSIZEY / 2 - 40, 255 - (GetTickCount() - beginTime - 8000 + 512) / 2);
		}
		else {
			IMAGEMANAGER->findImage(tmp)->render(WINSIZEX / 2 - 130, WINSIZEY / 2 - 40);
		}
	}

	int bossHPX = 10;
	int bossHPY = 100;
	if (isBossMap&&Boss->getCurHP()>0) {
		IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_���")->render(bossHPX, bossHPY);
		IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_�ڶѲ�")->render(bossHPX + IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_���")->getWidth(), bossHPY+IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_���")->getHeight()- IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_�ڶѲ�")->getHeight());
		IMAGEMANAGER->findImage("UI_����_��_Ÿ��ƹ�")->render(bossHPX + 2, bossHPY + 2);
		IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_����")->render(bossHPX + 29, bossHPY + 17, 0, 0, (float)IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_����")->getWidth()*((float)Boss->getCurHP() / (float)Boss->getMaxHP()), IMAGEMANAGER->findImage("UI_����_�Ϲ�_ü�¹�_����")->getHeight());
	}
}

void lorienDeepMap::renderdc()
{
	char tmp[50];


	for (vector<MonsterBase*>::iterator i = monBack.begin(); i != monBack.end(); i++) {
		(*i)->renderdc();
	}


	for (vector<MonsterBase*>::iterator i = monFront.begin(); i != monFront.end(); i++) {
		(*i)->renderdc();
	}
	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	Rectangle(hdc, i->rc.left-cam.x, i->rc.top-cam.y, i->rc.right-cam.x, i->rc.bottom-cam.y);
	//}
	MapBase::renderdc();
}

void lorienDeepMap::resetMonsters()
{
	monsterList.clear();
	for (vector<MonsterBase*>::iterator i = monsterBackup.begin(); i != monsterBackup.end(); i++) {
		(*i)->reset();
		monsterList.push_back(*i);
	}
}

void lorienDeepMap::resetDungeon()
{
	if (isfirstmap) {
		showdungeonName = true;
		beginTime = GetTickCount();
	}
	dropList.clear();
	movable = false;
	peaceful = false;
	runnable = true;
	attackable = true;
	showresult = playendsound = playedendsound = false;
	for (int i = 0; i < 4; i++) {
		Gates[i].movable = false;
	}
}

void lorienDeepMap::setMap(const char * tileName, int x, int y)
{
	ImgTile t;
	t.tileImg = IMAGEMANAGER->findImage(tileName);
	t.pos = pointMake(x, y);
	staticTiles.push_back(t);
}
