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


#include "player.h"

#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace Util;

struct Camera {
	DOUBLE x, y;
	DOUBLE offsetX, offsetY;
};
struct Item {
	string name;
	char imgName[50];
	int branch;							//내부에서 몇개까지 갈라져있는지, 갈라져있으면 몇번인지(없으면 0);
	int id;								//아이템 이미지 id
	int type;							//아이템 종류로 할 것
	int detail;							//아이템 세부사항

	int phydmgmin;							//무기한정
	int magdmgmin;
	int phydmgmax;
	int magdmgmax;

	int phydef;
	int magdef;

	int reachx;							//무기에 한정됨
	int reachz;							//무기에 한정됨

	int gainStr;
	int gainInt;
	int gainHealth;
	int gainSpirit;

	int gainHP;
	int gainMP;
	
	int reqlvl;

	bool equipped;

	string description;
};


struct HitQueue {
	bool isCrit;
	FLOAT x, y;
	int dmg;
	DWORD time;
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
extern player*						pl;
extern map<string, Item>			itemList;
extern vector<string>				itemNames;
extern bool							onDebug;


static FLOAT translate(FLOAT zval)
{
	FLOAT transVal = zval / 2;

	return transVal;
}
static enum Abnormal {
	abfreeze,
	abonhold,
	abforcemove,
};

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
