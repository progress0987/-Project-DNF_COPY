#include "stdafx.h"
#include "D2DImage.h"

HRESULT D2DImage::setImage(const char * fileName,bool trans, DWORD tr)
{
	DWORD R=0;
	DWORD G=0;
	DWORD B=0;
	if (trans) {
		R = (tr & 0xFF) << 16;
		G = (tr & 0xFF00);
		B = (tr & 0xFF0000) >> 16;
	}

	HRESULT hr = D3DXCreateTextureFromFileEx(
		curDev,						//출력될 디바이스(HDC랑 비슷한듯)
		_T(fileName),				//파일이름(주소)
		D3DX_DEFAULT/*_NONPOW2*/,				//폭		전체를할때는0 또는 D3DX_DEFAULT로 사용
		D3DX_DEFAULT/*_NONPOW2*/,				//높이		상동
		1,									//밉레벨 이라고 함 - 2D에서는 무조건 1
		0,
		D3DFMT_UNKNOWN,					//파일로부터 형식을 가져오는것, D3DFMT_UNKNOWN으로하면 소스를 직접가지고옴 과거:D3DFMT_A8B8G8R8
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,

		trans?D3DCOLOR_XRGB(R,G,B):0,								//컬러키 - 해당 색을 출력하지않는다(투명인듯)
		&c_ImgInfo,
		NULL,
		&c_pd3dTex);

	//D3DXCreateSprite(curDev, &c_pd3dSprite);
	return hr;
}

HRESULT D2DImage::setImage(const char * fileName, BOOL framed, unsigned int frameX, unsigned int frameY,bool trans, DWORD tr)
{
	DWORD R;
	DWORD G;
	DWORD B;


	if (trans) {
		R = (tr & 0xFF) << 16;
		G = (tr & 0xFF00);
		B = (tr & 0xFF0000) >> 16;
	}

	HRESULT hr = D3DXCreateTextureFromFileEx(
		curDev,						//출력될 디바이스(HDC랑 비슷한듯)
		_T(fileName),				//파일이름(주소)
		D3DX_DEFAULT_NONPOW2,				//폭		전체를할때는0 또는 D3DX_DEFAULT로 사용
		D3DX_DEFAULT_NONPOW2,				//높이		상동
		1,									//밉레벨 이라고 함 - 2D에서는 무조건 1
		0,
		D3DFMT_UNKNOWN,					//파일로부터 형식을 가져오는것, D3DFMT_UNKNOWN으로하면 소스를 직접가지고옴 과거:D3DFMT_A8B8G8R8
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		trans ? D3DCOLOR_XRGB(R, G, B) : 0,								//컬러키 - 해당 색을 출력하지않는다(투명인듯)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(w/2, h/2);							//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX+w/2, destY+h/2);					//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = sourW;
	int h = sourH;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//좌상단 좌표
	RECT rect = { sourX,sourY,sourX + w,sourY + h };	//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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

	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0x00ffffff + (alpha << 24);							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐


	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}
//맨 앞에꺼 출력
void D2DImage::framerender()
{
	//2D그리기 시작
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2, h / 2);							//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2, h / 2);							//좌상단 좌표
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2 + destX, h / 2 + destY);							//좌상단 좌표
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(w / 2, h / 2);							//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(w / 2 + destX, h / 2 + destY);							//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = sourW;
	int h = sourH;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//좌상단 좌표
	RECT rect = { sourX,sourY,sourX + w,sourY + h };	//그림의 크기
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2, h / 2);							//좌상단 좌표
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//그림의 크기
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(w / 2 + destX, h / 2 + destY);							//좌상단 좌표
	RECT rect = { 0 + curX * w,0 + curY * h,w + curX * w,h + curY * h };	//그림의 크기
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX, destY);					//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = sourW;
	int h = sourH;
	D3DXVECTOR2 pos(destX, destY);					//좌상단 좌표
	RECT rect = { sourX,sourY,sourX + w,sourY + h };	//그림의 크기
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = frameWidth;
	int h = frameHeight;
	D3DXVECTOR2 pos(destX, destY);							//좌상단 좌표
	RECT rect = { curX * w,curY * h,w + curX * w,h + curY * h };	//그림의 크기
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		angle,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	float pivot;
	if (Width == 0) {
		pivot = c_ImgInfo.Width;
	}
	else {
		pivot = Width;
	}
	D3DXVECTOR2 pos(destX+pivot - w / 2, destY + h / 2);					//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	
	D3DXVECTOR2 scale(-1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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

	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2-230, destY + h / 2-333);					//좌상단 좌표
	D3DXVECTOR2 pos2(destX  - w / 2 + 232, destY + h / 2 - 333);
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐
	D3DXVECTOR2 scale2(-1.f, 1.f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffffff;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	if (dir) {
		D3DXMatrixTransformation2D(
			&mat,						//출력
			NULL,						//스케일링의 중심
			0.0f,						//스케일링 회전률(???) -확인
			&scale,						//스케일링
			NULL,						//회전의 중심
			radian,						//회전률
			&pos);						//위치(트랜슬레이션)
	}
	else {
		D3DXMatrixTransformation2D(
			&mat,						//출력
			NULL,						//스케일링의 중심
			0.0f,						//스케일링 회전률(???) -확인
			&scale2,						//스케일링
			NULL,						//회전의 중심
			radian,						//회전률
			&pos2);						//위치(트랜슬레이션)
	}
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}
//나중에 처리할것
void D2DImage::DFpointshadowrender(int destX, int destY, bool dir)
{

	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	//(320, 160);//100,100 - 100,100에 렌더했을때 그림자는 320,160에 해야했음
	D3DXVECTOR2 pos(destX + w / 2 + 219 - 500-30, destY + h / 2 - 333+60+30);
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = - PI / 6.f;
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(0.9f, 0.8f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0x88000000;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);

}

void D2DImage::DFpointrender(int destX, int destY, int imgRwidth, int stY,FLOAT sc,int fading, bool dir)
{
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2 - imgRwidth/2, destY + h / 2 - stY);					//좌상단 좌표
	D3DXVECTOR2 pos2(destX - w / 2 + imgRwidth/2, destY + h / 2 - stY);
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(sc, sc);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐
	D3DXVECTOR2 scale2(-sc, sc);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffff + (fading<<24);							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	if (dir) {
		D3DXMatrixTransformation2D(
			&mat,						//출력
			NULL,						//스케일링의 중심
			0.0f,						//스케일링 회전률(???) -확인
			&scale,						//스케일링
			NULL,						//회전의 중심
			radian,						//회전률
			&pos);						//위치(트랜슬레이션)
	}
	else {
		D3DXMatrixTransformation2D(
			&mat,						//출력
			NULL,						//스케일링의 중심
			0.0f,						//스케일링 회전률(???) -확인
			&scale2,						//스케일링
			NULL,						//회전의 중심
			radian,						//회전률
			&pos2);						//위치(트랜슬레이션)
	}
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::DFscaledrender(int destX, int destY, int imgRwidth, int stY, FLOAT scaleX, FLOAT scaleY, int fading, bool dir)
{
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2 - imgRwidth / 2, destY + h / 2 - stY);					//좌상단 좌표
	D3DXVECTOR2 pos2(destX - w / 2 + imgRwidth / 2, destY + h / 2 - stY);
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(scaleX, scaleY);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐
	D3DXVECTOR2 scale2(-scaleX, scaleY);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0xffffff + (fading << 24);							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	if (dir) {
		D3DXMatrixTransformation2D(
			&mat,						//출력
			NULL,						//스케일링의 중심
			0.0f,						//스케일링 회전률(???) -확인
			&scale,						//스케일링
			NULL,						//회전의 중심
			radian,						//회전률
			&pos);						//위치(트랜슬레이션)
	}
	else {
		D3DXMatrixTransformation2D(
			&mat,						//출력
			NULL,						//스케일링의 중심
			0.0f,						//스케일링 회전률(???) -확인
			&scale2,						//스케일링
			NULL,						//회전의 중심
			radian,						//회전률
			&pos2);						//위치(트랜슬레이션)
	}
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
}

void D2DImage::DFpointedcirclerender(int destX, int destY, FLOAT scX , FLOAT scY, int fading)
{
	//2D그리기 시작
	int w = c_ImgInfo.Width*2;
	int h = c_ImgInfo.Height*2;
	D3DXVECTOR2 pos(destX, destY);					//좌상단 좌표
	RECT rect = { 0,0,w*scX,h*scY };						//그림의 크기
	float radian = 0.0f;							//회전각도(직각을 기준으로함
													//회전은 VECTOR3로
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale1(-scX, scY);	
	D3DXVECTOR2 scale2(scX, scY);
	D3DXVECTOR2 scale3(scX, -scY);
	D3DXVECTOR2 scale4(-scX, -scY);

	DWORD color = 0xffffff + (fading << 24);							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale1,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale2,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale3,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
	g_pd3dSprite->SetTransform(&mat);
	g_pd3dSprite->Draw(
		c_pd3dTex,
		&rect,
		&center,
		NULL,
		color);
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale4,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
	//2D그리기 시작
	int w = c_ImgInfo.Width;
	int h = c_ImgInfo.Height;
	D3DXVECTOR2 pos(destX + w / 2, destY + h / 2);					//좌상단 좌표
	RECT rect = { 0,0,w,h };						//그림의 크기
	float radian = PI/3.f;
	D3DXVECTOR3 center(w / 2, h / 2, 0);	//그림의 중심점 - 회전의 중심일듯

	D3DXVECTOR2 scale(0.3f, 0.9f);						//이미지의 스케일을결정(1이 기본), 중심을 기준으로커짐

	DWORD color = 0x88000000;							//색들을 출력해줄 정도로 보임(색을바꾸면 해당 색이 좀 빠짐)ARGB순서, A줄이면 이미지흐려짐

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(
		&mat,						//출력
		NULL,						//스케일링의 중심
		0.0f,						//스케일링 회전률(???) -확인
		&scale,						//스케일링
		NULL,						//회전의 중심
		radian,						//회전률
		&pos);						//위치(트랜슬레이션)
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
