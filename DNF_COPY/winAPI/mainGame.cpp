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
	if (FAILED(g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pd3dSurface))) {
		return E_FAIL;
	}

	LoadImages();


	return S_OK;
}
//����
 void mainGame::release(void)
 {//����� �̹����� �������������
	 gameNode::release();
 }
 //����~
 void mainGame::update(void)
 {
	 gameNode::update();

 }
 //���Ⱑ �׷��ִ� �� - paint �Ŀ� paintDC�� ������ - ���� �ٲܽ� �����Ұ�
 void mainGame::render() 
 {
	 if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		 //3D�׸��� ����
		 g_pd3dDevice->Clear(												//�ĸ� ���۸� rgb(0,128,255) �� ä����
			 0,
			 NULL,															//�Ƹ� Ŭ���� ���� ���� ��Ʈ�ε� -Ȯ��
			 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,								//Z���۱��� �����ش�.
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

 //��� �̹����� �ε�
 void mainGame::LoadImages()
 {

 }

 //�̹����� ó��
 void mainGame::paint()
 {
	 //test1.framerender(posx, posy,testx, testy);
 }

 //DC�ܿ��� �� �� ó��
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

	 //D3DXVECTOR3 vEyePt(0.f, .5f, -ptScale);									//1. ���� ��ġ (0,3,-5)
	 //D3DXVECTOR3 vLookatPt(0.f, 0.f, 0.f);								//2. ���� �ٶ󺸴� ��ġ(0,0,0)
	 //D3DXVECTOR3 vUpVec(0.f, 0.f, -1.f);									//3. õ�������� ��Ÿ���� ��溤��(0,1,0) - �Ƹ��� �ϴúκ��� �������ִºκ��ε�? -Ȯ��
	 //D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);			//1,2,3�� ����� �� ��� ���� - �¼���ǥ��(LH)

	 //g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					//������ �� ����� ����̽��� ����

		//																////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//																//�������� ���

		//																//�������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV - Field of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��ϴ�.
	 //D3DXMATRIXA16 matProj;
	 ///*
	 //matProj			���� ������ ���
	 //D3DX_PI/4		FOV(45��)
	 //1.0f			��Ⱦ��
	 //1.0f			���� Ŭ���� ���(near clipping plane)
	 //100.f			���Ÿ� Ŭ���� ���(far clipping plane)
	 //*/
	 //D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.f, 1.f, 100.f);	//�¼���ǥ��(LH)

	 //g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

 }
