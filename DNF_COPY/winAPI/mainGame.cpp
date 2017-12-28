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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////이하 로딩
	{
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
		cam.x = 0;
		cam.y = 0;

		LoadImages();
	}
	//////////////////////////////////////로딩끝//////////////////////////////////////////////


	pl = new player;
	seriaRoom = new Seria;
	village = new Village;
	mirkwood = new Mirkwood;


	seriaRoom->init();
	seriaRoom->setPlayer(pl);

	village->init();
	village->setPlayer(pl);
	seriaRoom->putConnectedMap(village, pointMake(712, 378 * 2));
	village->putConnectedMap(seriaRoom, pointMake(seriaRoom->getWidth() / 2, (seriaRoom->getHeight() - 50) * 2));

	mirkwood->setPlayer(pl);
	mirkwood->init();

	pl->setCurScene(mirkwood);
	pl->init();


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
	 pl->getCurMap()->update();

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
		 char tmp[50];
		 char tmp2[100];
	 for (int i = 0; i < 210; i++) {

		 sprintf(tmp2, "sprites/character_premade/%d.png", i);
		 sprintf(tmp, "캐릭터_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

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

		 sprintf(tmp2, "sprites/weapon/back/%d.png", i);
		 sprintf(tmp, "무기뒤_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/weapon/front/%d.png", i);
		 sprintf(tmp, "무기앞_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 for (int i = 0; i < 17; i++) {
		 sprintf(tmp2, "sprites/monster/goblin/blue/%d.png", i);
		 sprintf(tmp, "고블린_파랑_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/darkgreen/%d.png", i);
		 sprintf(tmp, "고블린_십장_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/green/%d.png", i);
		 sprintf(tmp, "고블린_초록_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/red/%d.png", i);
		 sprintf(tmp, "고블린_빨강_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/belt/belt_norm/%d.png", i);
		 sprintf(tmp, "고블린_장비_벨트_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/face/face_blue/%d.png", i);
		 sprintf(tmp, "고블린_얼굴_파랑_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/face/face_red/%d.png", i);
		 sprintf(tmp, "고블린_얼굴_빨강_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/pants/pants_norm/%d.png", i);
		 sprintf(tmp, "고블린_장비_바지_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/wrist/wrist_norm/%d.png", i);
		 sprintf(tmp, "고블린_장비_팔찌_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/weapon/weapon_1/%d.png", i);
		 sprintf(tmp, "고블린_무기_클럽_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/weapon/weapon_2/%d.png", i);
		 sprintf(tmp, "고블린_무기_십장_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

	 }


	 //머크우드 타일들
	 {
		 IMAGEMANAGER->addImage("던전_머크우드_배경_뒤", "sprites/maps/dungeons/mirkwood/back_far.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_배경_중간", "sprites/maps/dungeons/mirkwood/back_middle.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_배경_나무길", "sprites/maps/dungeons/mirkwood/tree_backway.img/0.png");

		 IMAGEMANAGER->addImage("던전_머크우드_바닥_0", "sprites/maps/dungeons/mirkwood/tile.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_1", "sprites/maps/dungeons/mirkwood/tile.img/1.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_2", "sprites/maps/dungeons/mirkwood/tile.img/2.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_3", "sprites/maps/dungeons/mirkwood/tile.img/3.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_덧붙임", "sprites/maps/dungeons/mirkwood/tile_ex.img/0.png");

		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_0", "sprites/maps/dungeons/mirkwood/stone.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_1", "sprites/maps/dungeons/mirkwood/stone.img/1.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_2", "sprites/maps/dungeons/mirkwood/stone.img/2.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_3", "sprites/maps/dungeons/mirkwood/stone.img/3.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_4", "sprites/maps/dungeons/mirkwood/stone.img/4.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_5", "sprites/maps/dungeons/mirkwood/stone.img/5.png");

		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_0", "sprites/maps/dungeons/mirkwood/tree.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_1", "sprites/maps/dungeons/mirkwood/tree.img/1.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_2", "sprites/maps/dungeons/mirkwood/tree.img/2.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_3", "sprites/maps/dungeons/mirkwood/tree.img/3.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_4", "sprites/maps/dungeons/mirkwood/tree.img/4.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_5", "sprites/maps/dungeons/mirkwood/tree.img/5.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_6", "sprites/maps/dungeons/mirkwood/tree.img/6.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_7", "sprites/maps/dungeons/mirkwood/tree.img/7.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_8", "sprites/maps/dungeons/mirkwood/tree.img/8.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_9", "sprites/maps/dungeons/mirkwood/tree.img/9.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_10", "sprites/maps/dungeons/mirkwood/tree.img/10.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_11", "sprites/maps/dungeons/mirkwood/tree.img/11.png");
	 }

	 IMAGEMANAGER->addImage("X표시", "sprites/invalid.png");
 }

 //이미지들 처리
 void mainGame::paint()
 {
	 pl->getCurMap()->render();
	 pl->render();
	 pl->getCurMap()->renderz();
	 pl->getUI()->render();
 }

 //DC단에서 할 일 처리
 void mainGame::paintDC()
 {
	 pl->getCurMap()->renderdc();
	 pl->renderdc();
	 TIMEMANAGER->render(hdc);
 }

