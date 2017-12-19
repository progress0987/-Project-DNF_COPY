#pragma once
#include"gameNode.h"
#include "D2DImage.h"
#include "Field.h"

static LPDIRECT3D9					g_pD3D;					  //D3D 디바이스를 생성할 D3D 객체 변수
static LPDIRECT3DDEVICE9			g_pd3dDevice;			  //D3D 디바이스
static LPDIRECT3DSURFACE9			g_pd3dSurface;
static HDC							hdc;					  //DC클래스

#define MOVESPEEDX 0.3f
#define MOVESPEEDY MOVESPEEDX/2.f

class mainGame :  public gameNode
{

private:
	Camera* mainCam;
	Field Desert;
	D2DImage test1;
	float posx=300.f, posy=300.f;
	int testx=0,testy = 0;
	int tick = 0;

public:

	HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
	void LoadImages();

	void paint();
	void paintDC();

	void setMatrices();

	mainGame();
	~mainGame();
};

