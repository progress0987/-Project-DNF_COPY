#pragma once
#include "gameNode.h"

#define TILEHEIGHT 64
#define TILEWIDTH TILEHEIGHT*2


#define TILENUMX 50
#define TILENUMY 50

enum TILE_TYPE
{
	TILE_TYPE_EMPTY,		//빈타일(지나갈수 있는곳)
	TILE_TYPE_START,		//시작
	TILE_TYPE_END,			//끝
	TILE_TYPE_WALL			//장애물
};
struct tile {
	RECT rc;
	POINT pos;
	POINT index;

	bool walkable;			//지나갈수이쌰냐
	bool listOn;			//오픈리스트에 추가 되었냥

	int F = 0;
	int G = 0;
	int H = 0;
	char str[128];
	tile* parent;		//부모타일 주소
	TILE_TYPE type;//타일 속성

};

class Field
{
private:
	Camera * cam;
	D2DImage* tileset;
	tile map[TILENUMX][TILENUMY];
	//FLOAT scale;
public:
	void init();
	void update();
	void render();
	void setCam(Camera* cam) { this->cam = cam; }
	Field();
	~Field();
};

