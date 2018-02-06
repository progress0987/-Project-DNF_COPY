#pragma once
#include "player.h"
#include "MonsterBase.h"
#include "NPC_Base.h"
struct Camera;
class player;
class MonsterBase;
extern struct Item;
extern struct DropItemStruct;


struct MapTile {
	RECT rc;
	int type;
	int moveindex;
};
struct ImgTile {
	D2DImage* tileImg;
	POINT pos;
};
struct conNode {
	MapBase* nextNode;
	FLOAT x, z;
};
struct dungeonGate {
	bool isShow;	//�������°�����
	bool movable;	//�̵� �ϴ� ����Ʈ����
	int x, y;		//��� ��ǥ
	bool isBoss;
	RECT moveRect;
	conNode con;
};
class MapBase
{
protected:
	LPD3DXFONT d3dFont;
	void drawWindow(int destX, int destY, int width, int height, int alpha=0xff);
	MapBase* curMap;
	int tileNumX, tileNumY;
	player * pl;
	int mapWidth, mapHeight;
	int minX, maxX, minZ, maxZ;
	bool peaceful;
	bool runnable;
	bool attackable;
	bool playendsound;
	bool playedendsound;
	bool showdungeonName;
	int tilewidth;
	dungeonGate Gates[4];

	vector<MapTile> mapTiles;
	vector<ImgTile> staticTiles;
	vector<MonsterBase*> monsterList;
	vector<MonsterBase*> monsterBackup;
	vector<MonsterBase*> monBack;
	vector<MonsterBase*> monFront;
	vector<DropItemStruct> dropList;
	vector<Item> droppedItemList;
public:
	bool showresult;
	bool isChangable;		//�� ���� ��������
	MapBase();
	~MapBase();

	//////virtual�� ���س����� �ٷ� �θ��� �Լ��� ������. 
	//////virtual�� �ؾ� ������ ����ã�� �θ�� ��.
	virtual HRESULT init();
	virtual void update();
	virtual void render();
	virtual void renderz();
	virtual void renderdc();

	////////////////////////////////////getter
	virtual int getWidth() { return mapWidth; }
	virtual int getHeight() { return mapHeight; }
	virtual int getTileNumX() { return tileNumX; }
	virtual int getTileNumY() { return tileNumY; }
	virtual player* getPlayer() { return pl; }
	virtual vector<MonsterBase*> getMonsterList() { return monsterList; }
	virtual vector<MapTile> getTiles() { return mapTiles; }
	virtual MapBase* getCurMap() { return curMap; }
	virtual void DropItem(DropItemStruct item) { dropList.push_back(item); }

	bool getMove(conNode* next, FLOAT x, FLOAT z);

	bool isRunnable() { return runnable; }
	bool isPeaceful() { if (curMap != nullptr) return curMap->isPeaceful(); else return peaceful; }
	bool isAttackable() { return attackable; }	
	
	/////////////////////////////////////setter
	virtual void setWidth(int w) { mapWidth = w; }
	virtual void setHeight(int h) { mapHeight = h; }
	virtual void setTileNumX(int x) { tileNumX = x; }
	virtual void setTileNumY(int y) { tileNumY = y; }
	//virtual void putConnectedMap(MapBase* connect, POINT pos, int direction) { conNodes t; t.nextNode = connect, t.pos = pos; Gates[direction].con = t; }
	virtual void setConNode(dungeonGate con, int index) { Gates[index] = con; }
	virtual void addMapTile(MapTile t) { mapTiles.push_back(t); }
	virtual void setPlayer(player* p) { pl = p; }
	virtual void setMinX(int a) { minX = a; }
	virtual void setMaxX(int a) { maxX = a; }
	virtual void setMinZ(int a) { minZ = a; }
	virtual void setMaxZ(int a) { maxZ = a; }
	virtual void resetDungeon() {};
	virtual void resetMonsters();

	void setPeaceful(bool p) { peaceful = p; }
	void setRunnable(bool r) { runnable = r; }
	void setAttackable(bool a) { attackable = a; }
	int aboveItem(FLOAT x, FLOAT z);
	DropItemStruct rootItem(FLOAT x, FLOAT z);
	Item* adddroppedItem(Item t) { droppedItemList.push_back(t);return &droppedItemList.back(); }

};

