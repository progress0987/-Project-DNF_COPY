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
class MapBase
{
protected:
	struct conNodes {
		MapBase* nextNode;
		POINT pos;
	};
	LPD3DXFONT d3dFont;
	void drawWindow(int destX, int destY, int width, int height, int alpha=0xff);
	MapBase* curMap;
	int tileNumX, tileNumY;
	player * pl;
	int mapWidth, mapHeight;
	bool peaceful;
	bool runnable;
	bool attackable;
	int tilewidth;
	vector<MapTile> mapTiles;
	vector<conNodes> connectedNodes;
	vector<ImgTile> staticTiles;
	vector<MonsterBase*> monsterList;
	vector<MonsterBase*> monBack;
	vector<MonsterBase*> monFront;
	vector<DropItemStruct> dropList;
	vector<Item> droppedItemList;
public:
	MapBase();
	~MapBase();

	//////virtual로 안해놓을시 바로 부모의 함수로 가버림. 
	//////virtual을 해야 로컬을 먼저찾고 부모로 감.
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
	virtual MapBase* NextMap(int index) { return connectedNodes[index].nextNode; }
	virtual POINT NextPos(int index) { return connectedNodes[index].pos; }
	virtual vector<MonsterBase*> getMonsterList() { return monsterList; }
	virtual vector<MapTile> getTiles() { return mapTiles; }
	virtual MapBase* getCurMap() { return curMap; }
	virtual void DropItem(DropItemStruct item) { dropList.push_back(item); }

	bool isRunnable() { return runnable; }
	bool isPeaceful() { if (curMap != nullptr) return curMap->isPeaceful(); else return peaceful; }
	bool isAttackable() { return attackable; }	
	
	/////////////////////////////////////setter
	virtual void setWidth(int w) { mapWidth = w; }
	virtual void setHeight(int h) { mapHeight = h; }
	virtual void setTileNumX(int x) { tileNumX = x; }
	virtual void setTileNumY(int y) { tileNumY = y; }
	virtual void putConnectedMap(MapBase* connect, POINT pos) { conNodes t; t.nextNode = connect, t.pos = pos; connectedNodes.push_back(t); }
	virtual void addMapTile(MapTile t) { mapTiles.push_back(t); }
	virtual void setPlayer(player* p) { pl = p; }
	void setPeaceful(bool p) { peaceful = p; }
	void setRunnable(bool r) { runnable = r; }
	void setAttackable(bool a) { attackable = a; }
	bool aboveItem(FLOAT x, FLOAT z);
	DropItemStruct rootItem(FLOAT x, FLOAT z);
	Item* adddroppedItem(Item t) { droppedItemList.push_back(t);return &droppedItemList.back(); }

};

