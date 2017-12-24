#include "stdafx.h"
#include "mainGame.h"



RECT rtemp;
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
//�ʱ�ȭ
HRESULT mainGame::init(void) 
{
	gameNode::init(true);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////���� �ε�
	{
		g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (g_pD3D == NULL) {			//����̽��� �����ϱ� ���� D3D ��ü ����
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
		g_pD3D->CreateDevice(					//��µ� ����̽��� �����ϴºκ�
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
	}
	//////////////////////////////////////�ε���//////////////////////////////////////////////


	pl = new player;
	seriaRoom = new Seria;
	village = new Village;


	seriaRoom->setCam(mainCam);
	seriaRoom->init();
	seriaRoom->setPlayer(pl);

	village->setCam(mainCam);
	village->init();
	village->setPlayer(pl);
	seriaRoom->putConnectedMap(village, pointMake(712, 378 * 2));
	village->putConnectedMap(seriaRoom, pointMake(seriaRoom->getWidth() / 2, (seriaRoom->getHeight() - 50) * 2));

	pl->setCurScene(village, WINSIZEX / 2, 0);
	pl->init();
	pl->linkCam(mainCam);


	return S_OK;
}
//����
 void mainGame::release(void)
 {//����� �̹����� �������������
	 

	 pl->release();

	 g_pd3dSurface->Release();
	 g_pd3dSprite->Release();
	 g_pd3dDevice->Release();
	 g_pD3D->Release();
	 
	 gameNode::release();
 }
 //����~
 void mainGame::update(void)
 {
	 pl->update();
	 pl->getCurMap()->update();

	 gameNode::update();

 }
 //���Ⱑ �׷��ִ� �� - paint �Ŀ� paintDC�� ������ - ���� �ٲܽ� �����Ұ�
 void mainGame::render() 
 {
	 if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		 //3D�׸��� ����
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

 //��� �̹����� �ε�
 void mainGame::LoadImages()
 {
	 //�̹��� ó��
	 for (int i = 0; i < 210; i++) {
		 char tmp[50];
		 char tmp2[50];

		 sprintf(tmp, "sprites/character_premade/%d.png", i);
		 sprintf(tmp2, "ĳ����_%d", i);
		 IMAGEMANAGER->addImage(tmp2, tmp);

		 //sprintf(tmp, "sprites/weapon/front_0/%d.png", i);
		 //sprintf(tmp2, "����տ���_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);

		 //sprintf(tmp, "sprites/weapon/front_1/%d.png", i);
		 //sprintf(tmp2, "�����_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);


		 //sprintf(tmp, "sprites/weapon/back_0/%d.png", i);
		 //sprintf(tmp2, "����ڿ���_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);

		 //sprintf(tmp, "sprites/weapon/back_1/%d.png", i);
		 //sprintf(tmp2, "�����_%d", i);
		 //IMAGEMANAGER->addImage(tmp2, tmp);

		 sprintf(tmp, "sprites/weapon/back/%d.png", i);
		 sprintf(tmp2, "�����_%d", i);
		 IMAGEMANAGER->addImage(tmp2, tmp);

		 sprintf(tmp, "sprites/weapon/front/%d.png", i);
		 sprintf(tmp2, "�����_%d", i);
		 IMAGEMANAGER->addImage(tmp2, tmp);
	 }
	 IMAGEMANAGER->addImage("Xǥ��", "sprites/invalid.png");
 }

 //�̹����� ó��
 void mainGame::paint()
 {
	 pl->getCurMap()->render();
	 pl->render();
	 pl->getCurMap()->renderz();
	 pl->getUI()->render();
 }

 //DC�ܿ��� �� �� ó��
 void mainGame::paintDC()
 {
	 pl->getCurMap()->renderdc();
	 pl->renderdc();
	 TIMEMANAGER->render(hdc);
 }

