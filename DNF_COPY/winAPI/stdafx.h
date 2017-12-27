// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
//#include<iostream>


//자주 쓰는 STL
#include<string>
#include<vector>
#include<list>
#include<map>

#include"commonMacroFunction.h"
#include"randomFuction.h"
#include"KeyManager.h"
#include"utils.h"
#include "collision.h"
#include"imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "soundManager.h"
#include "iniDataManager.h"
#include "effectManager.h"

#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace Util;

struct Camera {
	DOUBLE x, y;
	DOUBLE offsetX, offsetY;
};

//====================================
// ##내가 만든 헤더파일 요기에 추가!!
//====================================


//====================================
//   ##디파인 문 ##(윈도우 초기화 셋팅)
//====================================

#define WINNAME (LPTSTR)(TEXT("DNF_COPY"))
#define WINSTARTX 100
#define WINSTARTY 50
#define WINSIZEX  800
#define WINSIZEY  600
#define WINSTYLE  WS_CAPTION|WS_SYSMENU



//랜덤함수 디파인
#define RND				randomFunction::getSingleton()
//키매니저
#define KEYMANAGER		KeyManager::getSingleton()

#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()

#define SOUNDMANAGER	soundManager::getSingleton()
#define TXTDATA			txtData::getSingleton()

#define INIDATAMANAGER	iniDataManager::getSingleton()
//===============================================
//   ##매크로 함수 ##(메인게임 릴리즈 부분에서 사용)
//===============================================

#define SAFE_DELETE(p)  {if(p) {delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if(p){(p)->release();(p)=nullptr;}}

//=================================================
//   ##전역변수 ## (인스턴스, 윈도우 핸들, 마우스 좌표)
//=================================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT ptMouse;
extern FLOAT ptScale;
extern Camera cam;
extern LPDIRECT3D9					g_pD3D;						//D3D 디바이스를 생성할 D3D 객체 변수
extern LPDIRECT3DDEVICE9			g_pd3dDevice;				//D3D 디바이스
extern LPDIRECT3DSURFACE9			g_pd3dSurface;
extern LPD3DXSPRITE					g_pd3dSprite;
extern HDC							hdc;						//DC클래스


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
