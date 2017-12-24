#pragma once
#include "player.h"
struct Camera;
struct player;

struct MapTile {
	RECT rc;
	int type;
	int moveindex;
};
class MapBase
{
protected:
	struct conNodes {
		MapBase* nextNode;
		POINT pos;
	};
	vector<MapTile> mapTiles;
	int tileNumX, tileNumY;
	Camera * Cam;
	player * pl;
	int mapWidth, mapHeight;
	bool peaceful;
	vector<conNodes> connectedNodes;
public:
	MapBase();
	~MapBase();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void renderz();
	virtual void renderdc();
	int getWidth() { return mapWidth; }
	int getHeight() { return mapHeight; }
	bool isPeaceful() { return peaceful; }
	vector<MapTile> getTiles() { return mapTiles; }
	MapBase* NextMap(int index) { return connectedNodes[index].nextNode; }
	POINT NextPos(int index) { return connectedNodes[index].pos; }
	void putConnectedMap(MapBase* connect, POINT pos) { conNodes t; t.nextNode = connect, t.pos = pos; connectedNodes.push_back(t); }


	void setCam(Camera* c) { Cam = c; }
	void setPlayer(player* p) { pl = p; }

};

