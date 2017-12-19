#include "stdafx.h"
#include "mainGame.h"


RECT rtemp;
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
//초기화
HRESULT mainGame::init(void) 
{
	gameNode::init(true);

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {			//디바이스를 생성하기 위한 D3D 객체 생성
		return E_FAIL;
	}

	D3DDISPLAYMODE d3ddm;
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	g_pD3D->CreateDevice(					//출력될 디바이스를 생성하는부분
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pd3dDevice
	);
	if (FAILED(g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pd3dSurface))) {
		return E_FAIL;
	}

	LoadImages();


	return S_OK;
}
//해제
 void mainGame::release(void)
 {//사용한 이미지도 릴리즈해줘야함
	 gameNode::release();
 }
 //연산~
 void mainGame::update(void)
 {
	 gameNode::update();

 }
 //여기가 그려주는 곳 - paint 후에 paintDC가 렌더됨 - 순서 바꿀시 주의할것
 void mainGame::render() 
 {
	 if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		 //3D그리기 시작
		 g_pd3dDevice->Clear(												//후면 버퍼를 rgb(0,128,255) 로 채워줌
			 0,
			 NULL,															//아마 클리어 해줄 범위 렉트인듯 -확인
			 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,								//Z버퍼까지 지워준다.
			 D3DCOLOR_XRGB(0, 128, 255),
			 1.0f,
			 0);
		 PatBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		 paint();
		 g_pd3dSurface->GetDC(&hdc);
		 paintDC();
		 g_pd3dSurface->ReleaseDC(hdc);

		 g_pd3dDevice->EndScene();
	 }
	 g_pd3dDevice->Present(NULL, NULL, NULL, NULL);



 }

 //모든 이미지들 로드
 void mainGame::LoadImages()
 {

 }

 //이미지들 처리
 void mainGame::paint()
 {
	 //test1.framerender(posx, posy,testx, testy);
 }

 //DC단에서 할 일 처리
 void mainGame::paintDC()
 {
 }

 void mainGame::setMatrices()
 {
	 D3DXMATRIX mat1, mat2;


	 //D3DXMATRIXA16 matWorld;
	 //D3DXMatrixIdentity(&matWorld);
	 ////D3DXMatrixScaling(&matWorld, 1.f, 1.f, ptScale);
	 //g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	 //D3DXMATRIXA16 matView;

	 //D3DXVECTOR3 vEyePt(0.f, .5f, -ptScale);									//1. 눈의 위치 (0,3,-5)
	 //D3DXVECTOR3 vLookatPt(0.f, 0.f, 0.f);								//2. 눈이 바라보는 위치(0,0,0)
	 //D3DXVECTOR3 vUpVec(0.f, 0.f, -1.f);									//3. 천정방향을 나타내는 상방벡터(0,1,0) - 아마도 하늘부분을 설정해주는부분인듯? -확인
	 //D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);			//1,2,3의 값들로 뷰 행렬 생성 - 좌수좌표계(LH)

	 //g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					//생성한 뷰 행렬을 디바이스에 설정

		//																////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//																//프로젝션 행렬

		//																//프로젝션 행렬을 정의하기 위해서는 시야각(FOV - Field of View)과 종횡비(aspect ratio), 클리핑 평면의 값이 필요하다.
	 //D3DXMATRIXA16 matProj;
	 ///*
	 //matProj			값이 설정될 행렬
	 //D3DX_PI/4		FOV(45도)
	 //1.0f			종횡비
	 //1.0f			근접 클리핑 평면(near clipping plane)
	 //100.f			원거리 클리핑 평면(far clipping plane)
	 //*/
	 //D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.f, 1.f, 100.f);	//좌수좌표계(LH)

	 //g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

 }
