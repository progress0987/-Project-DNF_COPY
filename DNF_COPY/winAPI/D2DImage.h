#pragma once
//http://3dapi.com/bs11_2d_basic/ ****** ���� ������
#include <Windows.h>
#include <mmsystem.h>
#include "inc\d3dx9.h"

#pragma comment(lib,"d3dx9.lib")


class D2DImage
{
public:
	LPDIRECT3DTEXTURE9	c_pd3dTex = NULL;			//�ؽ�������
	D3DXIMAGE_INFO		c_ImgInfo;					//�̹�������
	LPD3DXVECTOR2		position;					//�׸� ��ġ
	CHAR*				fileAddress;				//���� �̸�
	LPDIRECT3DDEVICE9	curDev;						//��� ��ġ

	BOOL				framed=FALSE;				//������ ȭ �̹�������
	UINT				frameWidth;					//������ �̹��� ����� ���� ũ��
	UINT				frameHeight;				//������ �̹��� ����� ���� ũ��
	UINT				currentFrameX;				//������ �̹��� ��ȣ(����)
	UINT				currentFrameY;				//������ �̹��� ��ȣ(����)
	UINT				maxFrameX;					//������ ����ȣ(����)
	UINT				maxFrameY;					//������ ����ȣ(����)

	HRESULT init(LPDIRECT3DDEVICE9 dev) { curDev = dev; return S_OK; }
	HRESULT setImage(const char* fileName,bool trans = false, DWORD tr=NULL);
	HRESULT setImage(const char* fileName,BOOL framed,unsigned int frameX,unsigned int frameY,bool trans, DWORD tr=NULL);
	LPDIRECT3DDEVICE9 getDev() { return curDev; }

	void release();

	///////////////////////////////////������
	void render();
	void render(int destX, int destY);
	void render(int destX, int destY, FLOAT sourX, FLOAT sourY, FLOAT sourW, FLOAT sourH);

	void scaledrender(int destX, int destY, FLOAT sizeX =1.f, FLOAT sizeY =1.f);

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
	void DFuirender(int destX, int destY,int fromX=0, int fromY=0, int Width=-1, int Height=-1, FLOAT scX =1.0f, FLOAT scY = 1.0f, int fade = 0xFF);
	void DFpointrotatedrender(int destX, int destY, FLOAT angle, int centerX = -1, int centerY = -1);

	void shadowrender(int destX, int destY);


	void superiorrender(D3DXVECTOR2 pos, D3DXVECTOR3 center, D3DXVECTOR2 scale, DWORD color);//�ϴ� �������� ���� �� �߰�



	int getWidth() { return c_ImgInfo.Width; }
	int getHeight() { return c_ImgInfo.Height; }
	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
	int getFrameMaxX() { return maxFrameX; }
	int getFrameMaxY() { return maxFrameY; }


	D2DImage();
	~D2DImage();
};

