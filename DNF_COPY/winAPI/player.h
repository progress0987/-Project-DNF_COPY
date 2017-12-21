#pragma once
#include "gameNode.h"
#include "MapBase.h"

class MapBase;
enum STANCE {
	stance_idle,				//기본자세(마을자세)
	stance_walk,				//걷는자세
	stance_ready,				//전투준비자세
	stance_run,					//뛰는자세
	stance_jump,				//점프자세
	stance_hit,					//맞는자세
	stance_norm_1,				//평타 1번
	stance_norm_2,				//평타 2번
	stance_empowered_norm_1,	//강화평타1번
	stance_empowered_norm_2,	//강화평타2번
	stance_empowered_norm_3,	//강화평타3번
	stance_upper,				//어퍼슬래시
};
class player
{
private:
	Camera * cam;
	RECT terColRect;

	int temp;
	DWORD beginTime;
	DWORD tick;
	
	STANCE curStance;
	bool curDir;
	FLOAT x, y, z;
	MapBase* curMap;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);
	void linkCam(Camera* camera) { cam = camera; }
	void setCurScene(MapBase* map, FLOAT x, FLOAT z) { curMap = map; this->x = x; this->z = z; }
	FLOAT translate(FLOAT zval);

	player();
	~player();
};

