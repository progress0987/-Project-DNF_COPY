#pragma once
//http://3dapi.com/bs11_2d_basic/ ****** 참고 많이함
#include <Windows.h>
#include <mmsystem.h>
#include "inc\d3dx9.h"

#pragma comment(lib,"d3dx9.lib")


class D2DImage
{
public:
	LPDIRECT3DTEXTURE9	c_pd3dTex = NULL;			//텍스쳐정보
	D3DXIMAGE_INFO		c_ImgInfo;					//이미지정보
	LPD3DXVECTOR2		position;					//그림 위치
	CHAR*				fileAddress;				//파일 이름
	LPDIRECT3DDEVICE9	curDev;						//출력 장치

	BOOL				framed=FALSE;				//프레임 화 이미지인지
	UINT				frameWidth;					//프레임 이미지 한장당 가로 크기
	UINT				frameHeight;				//프레임 이미지 한장당 세로 크기
	UINT				currentFrameX;				//프레임 이미지 번호(가로)
	UINT				currentFrameY;				//프레임 이미지 번호(세로)
	UINT				maxFrameX;					//프레임 끝번호(가로)
	UINT				maxFrameY;					//프레임 끝번호(세로)

	HRESULT init(LPDIRECT3DDEVICE9 dev) { curDev = dev; return S_OK; }
	HRESULT setImage(const char* fileName,bool trans = false, DWORD tr=NULL);
	HRESULT setImage(const char* fileName,BOOL framed,unsigned int frameX,unsigned int frameY,bool trans, DWORD tr=NULL);
	LPDIRECT3DDEVICE9 getDev() { return curDev; }

	void release();

	///////////////////////////////////렌더들
	void render();
	void render(int destX, int destY);
	void render(int destX, int destY,int sourX,int sourY,int sourW, int sourH);

	void blurredrender(int destX, int destY,BYTE alpha);

	void framerender();
	void framerender(int curX,int curY);
	void framerender(int destX, int destY, int curX, int curY);

	void rotatedrender(FLOAT angle = 0.0f);
	void rotatedrender(int destX, int destY,FLOAT angle = 0.0f);
	void rotatedrender(int destX, int destY, int sourX, int sourY, int sourW, int sourH, FLOAT angle = 0.0f);

	void rotatedframerender(int curX, int curY, FLOAT angle = 0.0f);
	void rotatedframerender(int destX, int destY, int curX,int curY,FLOAT angle = 0.0f);

	void centerrender(int destX, int destY,FLOAT angle = 0.0f);
	void centerrender(int destX, int destY, int sourX, int sourY, int sourW, int sourH, FLOAT angle = 0.0f);

	void centerframerender(int destX, int destY, int curX, int curY, FLOAT angle = 0.0f);

	void reversedrender(int destX, int destY,int imgWidth=0);

	void DFcharpointrender(int destX, int destY, bool dir = true);
	void DFpointshadowrender(int destX, int destY, bool dir = true);
	void DFpointrender(int destX, int destY, int imgRwidth, int stY, FLOAT scale = 1.f,int fading = 0xFF, bool dir = true);
	void DFscaledrender(int destX, int destY, int imgRwidth, int stY, FLOAT scaleX = 1.f,FLOAT scaleY = 1.f, int fading = 0xFF, bool dir = true);
	void DFpointedcirclerender(int destX, int destY,FLOAT scX=1.f,FLOAT scY=1.f, int fading = 0xFF);

	void shadowrender(int destX, int destY);


	void superiorrender(D3DXVECTOR2 pos, D3DXVECTOR3 center, D3DXVECTOR2 scale, DWORD color);//일단 이정도만 추후 더 추가



	int getWidth() { return c_ImgInfo.Width; }
	int getHeight() { return c_ImgInfo.Height; }
	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
	int getFrameMaxX() { return maxFrameX; }
	int getFrameMaxY() { return maxFrameY; }


	D2DImage();
	~D2DImage();
};

