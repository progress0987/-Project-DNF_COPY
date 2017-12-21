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
public:
	MapBase();
	~MapBase();
	virtual void init();
	virtual void update();
	virtual void render();
	virtual void renderz();
	virtual void renderdc();
	virtual FLOAT getStandardY();
	vector<MapTile> getTiles() { return mapTiles; }


	void setCam(Camera* c) { Cam = c; }
	void setPlayer(player* p) { pl = p; }

};

