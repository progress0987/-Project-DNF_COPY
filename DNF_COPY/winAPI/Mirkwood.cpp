#include "stdafx.h"
#include "Mirkwood.h"


HRESULT Mirkwood::init()
{
	//MapBase::init();
	peaceful = false;
	runnable = true;
	attackable = true;
	showresult = false;



	MirkwoodMap* m1 = new MirkwoodMap;
	MirkwoodMap* m2 = new MirkwoodMap;
	MirkwoodMap* m3 = new MirkwoodMap;
	MirkwoodMap* m4 = new MirkwoodMap;

	MapTile t;
	tilewidth = IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getWidth();
	int zheight;
#pragma region 1����
	m1->init();
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
		m1->setMap("����_��ũ���_����_����_4", rand() % (tilewidth*(tileNum+2) - IMAGEMANAGER->findImage("����_��ũ���_����_����_4")->getWidth()), -rand() % 50-50);
	}


	m1->setWidth(tilewidth*(tileNum + 2));
	m1->setHeight(IMAGEMANAGER->findImage("����_��ũ���_�ٴ�_0")->getHeight());
	zheight = m1->getHeight() + 200;
	m1->setMaxX(m1->getWidth() - 50);
	m1->setMinX(50);
	m1->setMaxZ(m1->getHeight()*2 - 100);
	m1->setMinZ(zheight);

	m1->setTileNumX(m1->getWidth() / 50 + 1);
	m1->setTileNumY(m1->getHeight() / 50 + 1);
	t.type = -1;
	t.moveindex = -1;
	for (int y = 0; y < m1->getTileNumY() / 2 +1; y++) {
		for (int x = 0; x < m1->getTileNumX(); x++) {
			t.rc = RectMake(x * 50, y * 50, 50, 50);
			m1->addMapTile(t);
		}
	}
	t.rc = RectMake(0, 0, 60, m1->getHeight());
	m1->addMapTile(t);



	t.rc = RectMake(m1->getWidth() - 180, 0, 500, 416);
	m1->addMapTile(t);
	t.rc = RectMake(m1->getWidth() - 50, 0, 50, m1->getHeight());
	m1->addMapTile(t);
	t.rc = RectMake(m1->getWidth() - 160, 468, 500, m1->getHeight() - 468);
	m1->addMapTile(t);

	for (int i = 0; i < 5; i++) {
		green_goblin* g = new green_goblin();
		g->setCurmap(m1);
		g->init(800 + i * 150, (WINSIZEY - 50) * 2 -rand()%500);
		m1->addMonster(g);
	}

	t.rc = RectMake(1485, 390, 50, 50);
	t.type = 0;
	t.moveindex = 0;
	m1->addMapTile(t);
	m1->isBossMap = false;




	conNode node;
	node.nextNode = m2;
	node.x = 160;
	node.z = 423 * 2;
	dungeonGate gateinfo;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.movable = false;
	gateinfo.isShow = true;
	gateinfo.x = m1->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m1->setConNode(gateinfo, 1);
	gateinfo.isShow = false;
	gateinfo.movable = false;
	m1->setConNode(gateinfo, 0);
	m1->setConNode(gateinfo, 2);
	m1->setConNode(gateinfo, 3);
#pragma endregion

#pragma region 2����
	m2->init();
	m2->setPlayer(pl);
	m2->setPeaceful(false);
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

	m2->setMaxX(m2->getWidth() - 50);
	m2->setMinX(50);
	m2->setMaxZ(m2->getHeight()*2 - 100);
	m2->setMinZ(zheight);

	m2->setTileNumX(m2->getWidth() / 50 + 1);
	m2->setTileNumY(m2->getHeight() / 50 + 1);
	for (int y = 0; y < m2->getTileNumY() / 2 +1; y++) {
		for (int x = 0; x < m2->getTileNumX(); x++) {
			t.rc = RectMake(x * 50, y * 50, 50, 50);
			t.type = -1;
			m2->addMapTile(t);
		}
	}
	t.type = -1;
	t.rc = RectMake(0, 0, 69, 423);
	m2->addMapTile(t);
	t.rc = RectMake(0, 0, 30, m2->getHeight());
	m2->addMapTile(t);
	t.rc = RectMake(0, 459, 105, m2->getHeight()-459);
	m2->addMapTile(t);

	t.rc = RectMake(m2->getWidth() - 180, 0, 500, 416);
	m2->addMapTile(t);
	t.rc = RectMake(m2->getWidth() - 50, 0, 50, m2->getHeight());
	m2->addMapTile(t);
	t.rc = RectMake(m2->getWidth() - 160, 468, 500, m2->getHeight() - 468);
	m2->addMapTile(t);

	for (int i = 0; i < 5; i++) {
		green_goblin* g = new green_goblin;
		g->setCurmap(m2);
		g->init(800 + i * 150, (WINSIZEY - 50) * 2 - rand()%500);
		m2->addMonster(g);
	}
	m2->isBossMap = false;




	node.nextNode = m3;
	node.x = 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.x = m2->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m2->setConNode(gateinfo, 1);
	gateinfo.isShow = false;
	m2->setConNode(gateinfo, 0);
	m2->setConNode(gateinfo, 2);

	node.nextNode = m1;
	node.x = m1->getWidth() - 160;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.con = node;
	gateinfo.x = 0;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m2->setConNode(gateinfo, 3);

#pragma endregion

#pragma region 3����
	m3->init();
	m3->setPlayer(pl);
	m3->setPeaceful(false);
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

	m3->setMaxX(m3->getWidth() - 50);
	m3->setMinX(50);
	m3->setMaxZ(m3->getHeight()*2 - 100);
	m3->setMinZ(zheight);

	m3->setTileNumX(m3->getWidth() / 50 + 1);
	m3->setTileNumY(m3->getHeight() / 50 + 1);

	t.type = -1;
	for (int y = 0; y < m3->getTileNumY() / 2 +1; y++) {
		for (int x = 0; x < m3->getTileNumX(); x++) {
			t.rc = RectMake(x * 50, y * 50, 50, 50);
			m3->addMapTile(t);
		}
	}

	t.type = -1;
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

	for (int i = 0; i < 5; i++) {
		green_goblin* g = new green_goblin;
		g->setCurmap(m3);
		g->init(800 + i * 150, (WINSIZEY - 50) * 2);
		m3->addMonster(g);
	}


	node.nextNode = m2;
	node.x = m2->getWidth()-160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.x = 0;
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m3->setConNode(gateinfo, 3);
	gateinfo.isShow = false;
	m3->setConNode(gateinfo, 0);
	m3->setConNode(gateinfo, 2);

	node.nextNode = m4;
	node.x = 160;
	gateinfo.con = node;
	gateinfo.isBoss = true;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.x = m3->getWidth() - IMAGEMANAGER->findImage("����_��_���̵�")->getWidth();
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m3->setConNode(gateinfo, 1);
	m3->isBossMap = false;

#pragma endregion

#pragma region 4����
	m4->init();
	m4->setPlayer(pl);
	m4->setPeaceful(false);
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

	m4->setMaxX(m4->getWidth() - 50);
	m4->setMinX(50);
	m4->setMaxZ(m4->getHeight() * 2 - 100);
	m4->setMinZ(zheight);

	m4->setTileNumX(m4->getWidth() / 50 + 1);
	m4->setTileNumY(m4->getHeight() / 50 + 1);

	t.type = -1;
	for (int y = 0; y < m4->getTileNumY() / 2 + 1; y++) {
		for (int x = 0; x < m4->getTileNumX(); x++) {
			t.rc = RectMake(x * 50, y * 50, 50, 50);
			m4->addMapTile(t);
		}
	}

	t.type = -1;
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

	for (int i = 0; i < 5; i++) {
		green_goblin* g = new green_goblin;
		g->setCurmap(m4);
		g->init(800 + i * 150, (WINSIZEY - 50) * 2);
		m4->addMonster(g);
	}
	goblin_thrower* th = new goblin_thrower;
	th->setCurmap(m4);
	th->init(1000, WINSIZEY * 2 - 500);
	m4->addMonster(th);
	m4->setBoss(th);


	node.nextNode = m3;
	node.x = m3->getWidth() - 160;
	node.z = 423 * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.isShow = true;
	gateinfo.movable = false;
	gateinfo.x = 0;
	gateinfo.y = 430 - 192;
	gateinfo.moveRect = RectMake(gateinfo.x + 34, gateinfo.y + 192, 48, 29);
	m4->setConNode(gateinfo, 3);
	gateinfo.isShow = false;
	m4->setConNode(gateinfo, 0);
	m4->setConNode(gateinfo, 2);
	m4->setConNode(gateinfo, 1);
	m4->isBossMap = true;

#pragma endregion


	//Tau* tau = new Tau();
	//tau->setCurmap(m1);
	//tau->init(800 + 100, WINSIZEY * 2 - 500);
	//m1->addMonster(tau);

	//TauAssaulter* ta = new TauAssaulter();
	//ta->setCurmap(m1);
	//ta->init(800 - 100, WINSIZEY * 2 - 300);
	//m1->addMonster(ta);

	Maps.push_back(m1);
	Maps.push_back(m2);
	Maps.push_back(m3);
	Maps.push_back(m4);

	curMap = Maps[0];
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

void Mirkwood::resetDungeon()
{
	for (vector<MapBase*>::iterator i = Maps.begin(); i != Maps.end(); i++) {
		(*i)->resetMonsters();
	}
}

Mirkwood::Mirkwood()
{
}


Mirkwood::~Mirkwood()
{
}


HRESULT MirkwoodMap::init()
{
	movable = false;
	peaceful = false;
	runnable = true;
	attackable = true;
	showresult = false;
	MapBase::init();
	return S_OK;
}

void MirkwoodMap::update()
{
	monBack.clear();
	monFront.clear();
	for (vector<MonsterBase*>::iterator i = monsterList.begin(); i!=monsterList.end(); ){
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
	if (isBossMap) {
		if (Boss->getCurStat() == mon_onDead) {
			showresult = true;
			for (vector<MonsterBase*>::iterator i = monsterList.begin(); i != monsterList.end(); i++) {
				(*i)->setCurStat(mon_onDeadProcess);
			}
		}
	}
}

void MirkwoodMap::render()
{
	for (vector<ImgTile>::iterator i = staticTiles.begin(); i != staticTiles.end(); i++) {
		i->tileImg->render(i->pos.x - cam.x, i->pos.y - cam.y);
	}
	//����Ʈ�� �׷��ֱ�
	if(Gates[0].isShow){				// ����
		if (Gates[0].isBoss) {

		}
		else {

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
				IMAGEMANAGER->findImage("������_�ʵ�_���_1")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle,5,3);
			}
			else if (i->goldamount < 100) {
				IMAGEMANAGER->findImage("������_�ʵ�_���_2")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle,13,9);
			}
			else {
				IMAGEMANAGER->findImage("������_�ʵ�_���_3")->DFpointrotatedrender(i->x - cam.x + 25, (i->y + translate(i->z)) - cam.y + 25, i->angle,10,9);
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
		//IMAGEMANAGER->findImage("������_�ʵ�_�Ǳ�_����")->rotatedrender(i->x - cam.x, i->y -cam.y + translate(i->z), i->angle);
	}
	for (vector<MonsterBase*>::iterator i = monBack.begin(); i != monBack.end(); i++) {
		(*i)->render();
	}

	pl->render();

	for (vector<MonsterBase*>::iterator i = monFront.begin(); i != monFront.end(); i++) {
		(*i)->render();
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

void MirkwoodMap::renderz()
{
	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	IMAGEMANAGER->findImage("Xǥ��")->render(i->rc.left -cam.x, i->rc.top -cam.y);
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

	//for (vector<MapTile>::iterator i = mapTiles.begin(); i != mapTiles.end(); i++) {
	//	Rectangle(hdc, i->rc.left-cam.x, i->rc.top-cam.y, i->rc.right-cam.x, i->rc.bottom-cam.y);
	//}
	for (int i = 0; i < 4; i++) {
		if (Gates[i].isShow) {
			Rectangle(hdc, Gates[i].moveRect.left-cam.x, Gates[i].moveRect.top-cam.y, Gates[i].moveRect.right-cam.x, Gates[i].moveRect.bottom-cam.y);
		}
	}
	MapBase::renderdc();
}


void MirkwoodMap::setMap(const char* tileName, int x, int y)
{
	ImgTile t;
	t.tileImg = IMAGEMANAGER->findImage(tileName);
	t.pos = pointMake(x,y);
	staticTiles.push_back(t);
}
