#pragma once
#include "player.h"
struct Camera;
struct player;

struct MapTile {
	RECT rc;
	int type;
};
class MapBase
{
protected:
	vector<MapTile> mapTiles;
	int tileNumX, tileNumY;
	Camera * Cam;
	player * pl;
	int mapWidth, mapHeight;
	bool peaceful;
	vector<MapBase*> connectedNodes;
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
	MapBase* NextMap(int index) { connectedNodes[index]; }
	void putConnectedMap(MapBase* connect) { connectedNodes.push_back(connect); }


	void setCam(Camera* c) { Cam = c; }
	void setPlayer(player* p) { pl = p; }

};

