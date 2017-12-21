#include "stdafx.h"
#include "D2DImage.h"

HRESULT D2DImage::setImage(const char * fileName, DWORD tr)
{
	HRESULT hr = D3DXCreateTextureFromFileEx(
		curDev,						//��µ� ����̽�(HDC�� ����ѵ�)
		_T(fileName),				//�����̸�(�ּ�)
		D3DX_DEFAULT/*_NONPOW2*/,				//��		��ü���Ҷ���0 �Ǵ� D3DX_DEFAULT�� ���
		D3DX_DEFAULT/*_NONPOW2*/,				//����		��
		1,									//�ӷ��� �̶�� �� - 2D������ ������ 1
		0,
		D3DFMT_UNKNOWN,					//���Ϸκ��� ������ �������°�, D3DFMT_UNKNOWN�����ϸ� �ҽ��� ������������ ����:D3DFMT_A8B8G8R8
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		tr,								//�÷�Ű - �ش� ���� ��������ʴ´�(�����ε�)
		&c_ImgInfo,
		NULL,
		&c_pd3dTex);

	//D3DXCreateSprite(curDev, &c_pd3dSprite);
	return hr;
}

HRESULT D2DImage::setImage(const char * fileName, BOOL framed, unsigned int frameX, unsigned int frameY, DWORD tr)
{
	HRESULT hr = D3DXCreateTextureFromFileEx(
		curDev,						//��µ� ����̽�(HDC�� ����ѵ�)
		_T(fileName),				//�����̸�(�ּ�)
		D3DX_DEFAULT_NONPOW2,				//��		��ü���Ҷ���0 �Ǵ� D3DX_DEFAULT�� ���
		D3DX_DEFAULT_NONPOW2,				//����		��
		1,									//�ӷ��� �̶�� �� - 2D������ ������ 1
		0,
		D3DFMT_UNKNOWN,					//���Ϸκ��� ������ �������°�, D3DFMT_UNKNOWN�����ϸ� �ҽ��� ������������ ����:D3DFMT_A8B8G8R8
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		tr,								//�÷�Ű - �ش� ���� ��������ʴ´�(�����ε�)
		&c_ImgInfo,
		NULL,
		&c_pd3dTex);

	//D3DXCreateSprite(curDev, &c_pd3dSprite);
	this->framed = framed;
	if(frameX>0) frameWidth = c_ImgInfo.Width / frameX;
	else frameWidth = c_ImgInfo.Width;
	if(frameY>0) frameHeight = c_ImgInfo.Height / frameY;
	else frameHeight = c_ImgInfo.Height;
	maxFrameX = frameX-1;
	maxFrameY = frameY-1;
	return hr;
}


void D2DImage::release()
{
	if (c_pd3dTex) c_pd3dTex->Release();
}

void D2DImage::render()
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(w/2, h/2);							//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::render(int destX, int destY)
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX+w/2, destY+h/2);					//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::render(int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	//2D�׸��� ����
	int w = sourW;
	int h = sourH;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//�»�� ��ǥ
	RECT rect = { sourX,sourY,sourX + w,sourY + h };	//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}
void D2DImage::blurredrender(int destX, int destY, BYTE alpha)
{

	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0x00ffffff + (alpha << 24);							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������


	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}
//�� �տ��� ���
void D2DImage::framerender()
{
	//2D�׸��� ����
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2, h / 2);							//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::framerender(int curX, int curY)
{
	//2D�׸��� ����
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2, h / 2);							//�»�� ��ǥ
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::framerender(int destX, int destY, int curX, int curY)
{
	//2D�׸��� ����
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2 + destX, h / 2 + destY);							//�»�� ��ǥ
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::rotatedrender(FLOAT angle)
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(w / 2, h / 2);							//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::rotatedrender(int destX, int destY, FLOAT angle)
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(w / 2 + destX, h / 2 + destY);							//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::rotatedrender(int destX, int destY, int sourX, int sourY, int sourW, int sourH, FLOAT angle)
{
	//2D�׸��� ����
	int w = sourW;
	int h = sourH;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//�»�� ��ǥ
	RECT rect = { sourX,sourY,sourX + w,sourY + h };	//�׸��� ũ��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::rotatedframerender(int curX, int curY, FLOAT angle)
{
	//2D�׸��� ����
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2, h / 2);							//�»�� ��ǥ
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//�׸��� ũ��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::rotatedframerender(int destX, int destY, int curX, int curY, FLOAT angle)
{
	//2D�׸��� ����
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2 + destX, h / 2 + destY);							//�»�� ��ǥ
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//�׸��� ũ��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::centerrender(int destX, int destY, FLOAT angle)
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX, destY);					//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::centerrender(int destX, int destY, int sourX, int sourY, int sourW, int sourH, FLOAT angle)
{
	//2D�׸��� ����
	int w = sourW;
	int h = sourH;
	D3DXVECTOR2 pos(destX, destY);					//�»�� ��ǥ
	RECT rect = { sourX,sourY,sourX + w,sourY + h };	//�׸��� ũ��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::centerframerender(int destX, int destY, int curX, int curY, FLOAT angle)
{
	//2D�׸��� ����
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(destX, destY);							//�»�� ��ǥ
	RECT rect = { curX * w,curY * h,w + curX * w,h + curY * h };	//�׸��� ũ��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		angle,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::reversedrender(int destX, int destY,int Width)
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	float pivot;
	if (Width == 0) {
		pivot = c_ImgInfo.Width;
	}
	else {
		pivot = Width;
	}
	D3DXVECTOR2 pos(destX+pivot - w / 2, destY + h / 2);					//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	
	D3DXVECTOR2 scale(-1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::DFcharpointrender(int destX, int destY, bool dir)
{

	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2-230, destY + h / 2-333);					//�»�� ��ǥ
	D3DXVECTOR2 pos2(destX  - w / 2 + 232, destY + h / 2 - 333);
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = 0.0f;							//ȸ������(������ ����������
													//ȸ���� VECTOR3��
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��
	D3DXVECTOR2 scale2(-1.f, 1.f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0xffffffff;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	if (dir) {
		D3DXMatrixTransformation2D(
			&mat,						//���
			NULL,						//�����ϸ��� �߽�
			0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
			&scale,						//�����ϸ�
			NULL,						//ȸ���� �߽�
			radian,						//ȸ����
			&pos);						//��ġ(Ʈ�������̼�)
	}
	else {
		D3DXMatrixTransformation2D(
			&mat,						//���
			NULL,						//�����ϸ��� �߽�
			0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
			&scale2,						//�����ϸ�
			NULL,						//ȸ���� �߽�
			radian,						//ȸ����
			&pos2);						//��ġ(Ʈ�������̼�)
	}
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}
//���߿� ó���Ұ�
void D2DImage::DFpointshadowrender(int destX, int destY, bool dir)
{

	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	//(320, 160);//100,100 - 100,100�� ���������� �׸��ڴ� 320,160�� �ؾ�����
	D3DXVECTOR2 pos(destX + w / 2 + 219 - 500-30, destY + h / 2 - 333+60+30);
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = - PI / 6.f;
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(0.9f, 0.8f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0x88000000;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);

}

void D2DImage::shadowrender(int destX, int destY)
{
	//2D�׸��� ����
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//�»�� ��ǥ
	RECT rect = { 0,0,w,h };						//�׸��� ũ��
	float radian = PI/3.f;
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//�׸��� �߽��� - ȸ���� �߽��ϵ�

	D3DXVECTOR2 scale(0.3f, 0.9f);						//�̹����� ������������(1�� �⺻), �߽��� ��������Ŀ��

	DWORD color = 0x88000000;							//������ ������� ������ ����(�����ٲٸ� �ش� ���� �� ����)ARGB����, A���̸� �̹��������

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//���
		NULL,						//�����ϸ��� �߽�
		0.0f,						//�����ϸ� ȸ����(???) -Ȯ��
		&scale,						//�����ϸ�
		NULL,						//ȸ���� �߽�
		radian,						//ȸ����
		&pos);						//��ġ(Ʈ�������̼�)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}


D2DImage::D2DImage()
{
}


D2DImage::~D2DImage()
{
}