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

	D3DXCreateSprite(g_pd3dDevice, &g_pd3dSprite);
	if (FAILED(g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pd3dSurface))) {
		return E_FAIL;
	}
	mainCam = new Camera;
	mainCam->x = 0;
	mainCam->y = 0;

	LoadImages();
	//////////////////////////////////////로딩끝//////////////////////////////////////////////


	seriaRoom = new Seria;
	seriaRoom->init();
	seriaRoom->setCam(mainCam);
	pl = new player;
	pl->setCurScene(seriaRoom, WINSIZEX / 2, 0);
	pl->init();
	pl->linkCam(mainCam);


	return S_OK;
}
//해제
 void mainGame::release(void)
 {//사용한 이미지도 릴리즈해줘야함
	 

	 pl->release();

	 g_pd3dSurface->Release();
	 g_pd3dSprite->Release();
	 g_pd3dDevice->Release();
	 g_pD3D->Release();
	 
	 gameNode::release();
 }
 //연산~
 void mainGame::update(void)
 {
	 pl->update();
	 gameNode::update();

 }
 //여기가 그려주는 곳 - paint 후에 paintDC가 렌더됨 - 순서 바꿀시 주의할것
 void mainGame::render() 
 {
	 if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		 //3D그리기 시작
		 if (SUCCEEDED(g_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND))) {
			 g_pd3dDevice->Clear( 0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0, 128, 255),1.0f,0);
			 paint();
			 g_pd3dSprite->End();
		 }
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
	 //이미지 처리
	 for (int i = 0; i < 210; i++) {
		 char tmp[50];
		 char tmp2[50];

		 sprintf(tmp, "sprites/character_premade/%d.png", i);
		 sprintf(tmp2, "캐릭터_%d", i);
		 IMAGEMANAGER->addImage(tmp2, tmp);

		 //sprintf(tmp, "sprites/weapon/front_0/%d.png", i);
		 //sprintf(tmp2, "무기앞오라_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);

		 //sprintf(tmp, "sprites/weapon/front_1/%d.png", i);
		 //sprintf(tmp2, "무기앞_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);


		 //sprintf(tmp, "sprites/weapon/back_0/%d.png", i);
		 //sprintf(tmp2, "무기뒤오라_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);

		 //sprintf(tmp, "sprites/weapon/back_1/%d.png", i);
		 //sprintf(tmp2, "무기뒤_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);

		 sprintf(tmp, "sprites/weapon/back/%d.png", i);
		 sprintf(tmp2, "무기뒤_%d", i);
		 IMAGEMANAGER->addImage(tmp2, tmp);

		 sprintf(tmp, "sprites/weapon/front/%d.png", i);
		 sprintf(tmp2, "무기앞_%d", i);
		 IMAGEMANAGER->addImage(tmp2, tmp);
	 }
	 IMAGEMANAGER->addImage("X표시", "sprites/invalid.png");
 }

 //이미지들 처리
 void mainGame::paint()
 {
	 seriaRoom->render();
	 pl->render();
	 seriaRoom->renderz();
 }

 //DC단에서 할 일 처리
 void mainGame::paintDC()
 {
	 seriaRoom->renderdc();
	 pl->renderdc();
	 //TIMEMANAGER->render(hdc);
 }

