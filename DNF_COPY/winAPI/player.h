#pragma once
#include "gameNode.h"
#include "MapBase.h"

class MapBase;
enum STANCE {
	stance_idle,				//�⺻�ڼ�(�����ڼ�)
	stance_walk,				//�ȴ��ڼ�
	stance_ready,				//�����غ��ڼ�
	stance_run,					//�ٴ��ڼ�
	stance_jump,				//�����ڼ�
	stance_hit,					//�´��ڼ�
	stance_norm_1,				//��Ÿ 1��
	stance_norm_2,				//��Ÿ 2��
	stance_empowered_norm_1,	//��ȭ��Ÿ1��
	stance_empowered_norm_2,	//��ȭ��Ÿ2��
	stance_empowered_norm_3,	//��ȭ��Ÿ3��
	stance_upper,				//���۽�����
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
	MapBase* getCurMap() { return curMap; }

	player();
	~player();
};

