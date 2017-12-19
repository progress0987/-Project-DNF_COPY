#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>														//dx9 로 써야하는데 에러남 - 깔려있던 라이브러리를 강제로 옮겨서 추가해줬음.
//#include "stdafx.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//http://ryuschool.tistory.com/entry/DirectX%EB%A5%BC-%EC%9D%B4%EC%9A%A9%ED%95%9C-%EC%9D%B4%EB%AF%B8%EC%A7%80-%ED%8C%8C%EC%9D%BC-%EB%9D%84%EC%9A%B0%EA%B8%B0
//http://3dapi.com/bs11_2d_basic/ ****** 참고 많이함

//전역변수
//g로 시작하는건 글로벌(전역)

static LPDIRECT3D9					g_pD3D = NULL;						//D3D 디바이스를 생성할 D3D 객체 변수
static LPDIRECT3DDEVICE9			g_pd3dDevice = NULL;					//정점을 보관할 정점 버퍼 - 정점만을 계산하기위해 생성된 버퍼
////스프라이트
//static LPD3DXSPRITE					g_pd3dSprite = NULL;
////이미지를 불러오기 위해서 사용
//static LPDIRECT3DTEXTURE9			g_tex = NULL;
int g_width, g_height;



HRESULT InitD3D(HWND hWnd) {
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {			//디바이스를 생성하기 위한 D3D 객체 생성
		return E_FAIL;
	}
	D3DDISPLAYMODE d3ddm;
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
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
	//////////////////이미지불러오기////////////
	D3DXIMAGE_INFO info;					//이미지 불러오는것
	D3DXIMAGE_INFO next;
	//디바이스에 텍스쳐 불러옴
	D3DXCreateSprite(g_pd3dDevice, &g_pd3dSprite);

	if (FAILED(D3DXCreateTextureFromFileEx(
		g_pd3dDevice,						//출력될 디바이스(HDC랑 비슷한듯)
		_T("sprites/test.jpg"),				//파일이름(주소)
		D3DX_DEFAULT_NONPOW2,				//폭		전체를할때는0 또는 D3DX_DEFAULT로 사용
		D3DX_DEFAULT_NONPOW2,				//높이		상동
		1,									//밉레벨 이라고 함 - 2D에서는 무조건 1
		0,
		D3DFMT_UNKNOWN,					//파일로부터 형식을 가져오는것, D3DFMT_UNKNOWN으로하면 소스를 직접가지고옴 과거:D3DFMT_A8B8G8R8
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		NULL,								//컬러키 - 해당 색을 출력하지않는다(투명인듯)
		&info,
		NULL,
		&g_tex))) return E_FAIL;
	else {
		g_width = info.Width;
		g_height = info.Height;
	}
	return S_OK;														//디바이스 상태정보 처리 완료
}
//릴리즈
void release() {
	if (g_pd3dDevice != NULL) {
		g_pd3dDevice->Release();
	}
	if (g_pD3D != NULL) {
		g_pD3D->Release();
	}
}

HRESULT addImage() {
	HRESULT hr = D3DXCreateTextureFromFileEx(
		g_pd3dDevice				// 디바이스 포인터
		, m_TexName[i]				// 텍스처 이름
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x0000001
		, 0x0000001
		, 0x00FFFFFF				// 컬러 키
		, &m_Img[i]					// 텍스처 인포메이션
		, NULL
		, &m_Tex[i]					// 텍스처 포인터
	);

	return S_OK;
}