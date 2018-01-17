#pragma once
#include "player.h"
#include "MonsterBase.h"
struct Camera;
class player;
class MonsterBase;

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
public:
	MapBase();
	~MapBase();

	//////virtual�� ���س����� �ٷ� �θ��� �Լ��� ������. 
	//////virtual�� �ؾ� ������ ����ã�� �θ�� ��.
	virtual void init();
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

};

