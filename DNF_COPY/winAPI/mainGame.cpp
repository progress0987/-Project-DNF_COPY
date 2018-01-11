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
		cam.x = 0;
		cam.y = 0;

		LoadImages();
	}
	//////////////////////////////////////�ε���//////////////////////////////////////////////


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
	 char tmp[100];
	 char tmp2[255];


	 ///�÷��̾�

	 for (int i = 0; i < 210; i++) {

		 sprintf(tmp2, "sprites/character_premade/%d.png", i);
		 sprintf(tmp, "ĳ����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

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

		 sprintf(tmp2, "sprites/weapon/back/%d.png", i);
		 sprintf(tmp, "�����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/weapon/front/%d.png", i);
		 sprintf(tmp, "�����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 ///����

	 //���
	 for (int i = 0; i < 17; i++) {
		 sprintf(tmp2, "sprites/monster/goblin/blue/%d.png", i);
		 sprintf(tmp, "���_�Ķ�_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/darkgreen/%d.png", i);
		 sprintf(tmp, "���_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/green/%d.png", i);
		 sprintf(tmp, "���_�ʷ�_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/red/%d.png", i);
		 sprintf(tmp, "���_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/belt/belt_norm/%d.png", i);
		 sprintf(tmp, "���_���_��Ʈ_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/face/face_blue/%d.png", i);
		 sprintf(tmp, "���_��_�Ķ�_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/face/face_red/%d.png", i);
		 sprintf(tmp, "���_��_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/pants/pants_norm/%d.png", i);
		 sprintf(tmp, "���_���_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/wrist/wrist_norm/%d.png", i);
		 sprintf(tmp, "���_���_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/weapon/weapon_1/%d.png", i);
		 sprintf(tmp, "���_����_Ŭ��_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/weapon/weapon_2/%d.png", i);
		 sprintf(tmp, "���_����_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

	 }

	 ///�� Ÿ��

	 //��ũ��� Ÿ��
	 {
		 IMAGEMANAGER->addImage("����_��ũ���_���_��", "sprites/maps/dungeons/mirkwood/back_far.img/0.png");
		 IMAGEMANAGER->addImage("����_��ũ���_���_�߰�", "sprites/maps/dungeons/mirkwood/back_middle.img/0.png");
		 IMAGEMANAGER->addImage("����_��ũ���_���_������", "sprites/maps/dungeons/mirkwood/tree_backway.img/0.png");

		 IMAGEMANAGER->addImage("����_��ũ���_�ٴ�_0", "sprites/maps/dungeons/mirkwood/tile.img/0.png");
		 IMAGEMANAGER->addImage("����_��ũ���_�ٴ�_1", "sprites/maps/dungeons/mirkwood/tile.img/1.png");
		 IMAGEMANAGER->addImage("����_��ũ���_�ٴ�_2", "sprites/maps/dungeons/mirkwood/tile.img/2.png");
		 IMAGEMANAGER->addImage("����_��ũ���_�ٴ�_3", "sprites/maps/dungeons/mirkwood/tile.img/3.png");
		 IMAGEMANAGER->addImage("����_��ũ���_�ٴ�_������", "sprites/maps/dungeons/mirkwood/tile_ex.img/0.png");

		 IMAGEMANAGER->addImage("����_��ũ���_����_��_0", "sprites/maps/dungeons/mirkwood/stone.img/0.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_��_1", "sprites/maps/dungeons/mirkwood/stone.img/1.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_��_2", "sprites/maps/dungeons/mirkwood/stone.img/2.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_��_3", "sprites/maps/dungeons/mirkwood/stone.img/3.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_��_4", "sprites/maps/dungeons/mirkwood/stone.img/4.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_��_5", "sprites/maps/dungeons/mirkwood/stone.img/5.png");

		 IMAGEMANAGER->addImage("����_��ũ���_����_����_0", "sprites/maps/dungeons/mirkwood/tree.img/0.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_1", "sprites/maps/dungeons/mirkwood/tree.img/1.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_2", "sprites/maps/dungeons/mirkwood/tree.img/2.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_3", "sprites/maps/dungeons/mirkwood/tree.img/3.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_4", "sprites/maps/dungeons/mirkwood/tree.img/4.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_5", "sprites/maps/dungeons/mirkwood/tree.img/5.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_6", "sprites/maps/dungeons/mirkwood/tree.img/6.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_7", "sprites/maps/dungeons/mirkwood/tree.img/7.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_8", "sprites/maps/dungeons/mirkwood/tree.img/8.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_9", "sprites/maps/dungeons/mirkwood/tree.img/9.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_10", "sprites/maps/dungeons/mirkwood/tree.img/10.png");
		 IMAGEMANAGER->addImage("����_��ũ���_����_����_11", "sprites/maps/dungeons/mirkwood/tree.img/11.png");
	 }


	 ///ȿ�� ����Ʈ

	 //����

	 for (int i = 0; i < 7; i++) {
		 sprintf(tmp2, "sprites/effects/game/hit/bloodlarge.img/%d.png", i);
		 sprintf(tmp, "����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //����
	 {
		 sprintf(tmp2, "sprites/status/freeze/4.png");
		 sprintf(tmp, "����_0");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/5.png");
		 sprintf(tmp, "����_1");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/6.png");
		 sprintf(tmp, "����_2");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/7.png");
		 sprintf(tmp, "����_3");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/18.png");
		 sprintf(tmp, "����_����_0");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/19.png");
		 sprintf(tmp, "����_����_1");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/20.png");
		 sprintf(tmp, "����_����_2");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/21.png");
		 sprintf(tmp, "����_����_3");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/22.png");
		 sprintf(tmp, "����_����_4");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/23.png");
		 sprintf(tmp, "����_����_5");
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 ///��ų �̹����� ��������
	 
	 //���۽�����
	 for (int i = 0; i < 9; i++) {
		 sprintf(tmp2, "sprites/skill/upperslash/%d.png", i);
		 sprintf(tmp, "���۽�����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }


	 //�ĵ���
	 for (int i = 0; i < 5; i++) {
		 sprintf(tmp2, "sprites/skill/wave/hadouken_hadou.img/%d.png", i);
		 sprintf(tmp, "�ĵ���_����_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/wave/hadouken_ken.img/%d.png", i);
		 sprintf(tmp, "�ĵ���_ȿ��_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //�ĵ��� ����
	 {
		 for (int i = 0; i < 6; i++) {
			 sprintf(tmp2, "sprites/skill/icewave/icewave1.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_����ȿ��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 11; i++) {
			 sprintf(tmp2, "sprites/skill/icewave/icewave2.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_�������_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 64; i++) {

			 sprintf(tmp2, "sprites/skill/icewave/icewaveparticle.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_��������_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 3; i++) {
			 sprintf(tmp2, "sprites/skill/icewave/icewaveparticlesmoke.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_��������_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 }
	 
	 //�ĵ��� ����
	 {
		 for (int i = 0; i < 10; i++) {
			 sprintf(tmp2, "sprites/skill/firewave/flame_dodge.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_ȭ��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/firewave/flame_normal.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_����_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }

		 sprintf(tmp2, "sprites/skill/firewave/flame_ground.img/0.png");
		 sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_ȭ��");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/firewave/flame_ground.img/1.png");
		 sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_����");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/firewave/flame_line.img/0.png");
		 sprintf(tmp, "�ĵ���_����_ȭ��_�ٴ�_����");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 for (int i = 0; i < 10; i++) {
			 sprintf(tmp2, "sprites/skill/firewave/sword_effect.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_Į_ȭ��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2,true,RGB(0,0,0));
			 sprintf(tmp2, "sprites/skill/firewave/sword_dodge.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_Į_�ܿ�_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2,true,RGB(0,0,0));
			 sprintf(tmp2, "sprites/skill/firewave/sword_normal.img/%d.png", i);
			 sprintf(tmp, "�ĵ���_����_Į_����_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2,true,RGB(0,0,0));
		 }
	 }

	 //������
	 {
			 sprintf(tmp2,"sprites/skill/vaccumslash/grandwave.img/0.png");
			 sprintf(tmp, "������_��");
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwave.img/1.png");
			 sprintf(tmp, "������_��");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/skill/vaccumslash/surajin.img/0.png");
			 sprintf(tmp, "����������_��");
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/surajin.img/1.png");
			 sprintf(tmp, "����������_��");
			 IMAGEMANAGER->addImage(tmp, tmp2);

		 for (int i = 0; i < 4; i++) {
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwaveblade.img/%d.png", i);
			 sprintf(tmp, "������_���_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwavefullcharge.img/%d.png", i);
			 sprintf(tmp, "������_Ǯ����_��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwavefullcharge.img/%d.png", i+5);
			 sprintf(tmp, "������_Ǯ����_��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 13; i++) {
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwaveoncharge.img/%d.png", i+13);
			 sprintf(tmp, "������_������_��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwaveoncharge.img/%d.png", i);
			 sprintf(tmp, "������_������_��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 }

	 //�ĵ�����
	 {
		 for (int i = 0; i < 5; i++) {
			 sprintf(tmp2, "sprites/skill/releasewave/releasewave1.img/%d.png", i);
			 sprintf(tmp, "�ĵ�����_�ذ�_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/releasewave/releasewave2.img/%d.png", i);
			 sprintf(tmp, "�ĵ�����_ȿ��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }

		 sprintf(tmp2, "sprites/skill/releasewave/releasewave1.img/5.png");
		 sprintf(tmp, "�ĵ�����_�ذ�_5");
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //�ε������
	 {
		 for (int i = 0; i < 6; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/1-dodge.img/%d.png", i);
			 sprintf(tmp, "�ε�_����_1_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/2-dodge.img/%d.png", i);
			 sprintf(tmp, "�ε�_����_2_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/3-dodge.img/%d.png", i);
			 sprintf(tmp, "�ε�_����_3_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/effect.img/%d.png", i);
			 sprintf(tmp, "�ε�_��ü_ȿ��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/target-effect.img/%d.png", i);
			 sprintf(tmp, "�ε�_����_ȿ��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/target-effect-dodge.img/%d.png", i);
			 sprintf(tmp, "�ε�_����_ȿ��_���_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 5; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/action.img/%d.png", i);
			 sprintf(tmp, "�ε�_�õ�_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 3; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/bead_disappear_dodge.img/%d.png", i);
			 sprintf(tmp, "�ε�_�Ҹ�����Ʈ_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 sprintf(tmp2, "sprites/skill/wavespin/bead-dodge.img/1.png");
		 sprintf(tmp, "�ε�_��ü");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/wavespin/bead-dodge.img/2.png");
		 sprintf(tmp, "�ε�_��ü_����");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/wavespin/mg-circle.img/0.png");
		 sprintf(tmp, "�ε�_������");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 for (int i = 0; i < 9; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/mg-circle-back.img/%d.png", i);
			 sprintf(tmp, "�ε�_������_����Ʈ_��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/mg-circle-front.img/%d.png", i);
			 sprintf(tmp, "�ε�_������_����Ʈ_��_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 }

	 //������ �ĵ�



	 //��Ÿ �̹���
	 IMAGEMANAGER->addImage("Xǥ��", "sprites/invalid.png");
 }

 //�̹����� ó��
 void mainGame::paint()
 {
	 pl->getCurMap()->render();
	 pl->getUI()->render();
 }

 //DC�ܿ��� �� �� ó��
 void mainGame::paintDC()
 {
	 pl->getCurMap()->renderdc();
	 pl->renderdc();
	 TIMEMANAGER->render(hdc);
 }

