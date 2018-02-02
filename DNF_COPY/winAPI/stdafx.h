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
//#include "Universal_structs.h"

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
extern player*						pl;
extern map<string, Item>			itemList;
extern vector<string>				itemNames;
extern bool							onDebug;

extern bool clicked;
extern bool lstay;
extern bool rclicked;


extern vector<string> bgmNames;
static void playBGM(string bgm) {
	for (vector<string>::iterator i = bgmNames.begin(); i != bgmNames.end(); i++) {
		SOUNDMANAGER->stop(*i);
	}
	SOUNDMANAGER->play(bgm);
}


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

static enum itemType {
	item_weapon = 1,
	item_coat,
	item_shoulder,
	item_belt,
	item_pants,
	item_shoes,
	item_ring,
	item_necklace,
	item_braclet,
	item_consume,
	item_etc,
};

static enum WeaponType {
	wp_empty,			//없음
	wp_sswd,			//소검
	wp_gswd,			//대검
	wp_kat,				//도
						//이후 더 추가
};
static enum ArmorType {
	arm_cloth,			//천갑옷
	arm_leather,		//가죽
	arm_larmor,			//경갑
	arm_harmor,			//중갑
	arm_plate			//판금
};
static struct HitQueue {
	bool isCrit;
	FLOAT x, y;
	int dmg;
	DWORD time;
};

static void printNumber(HitQueue h)
{
	int digit;
	bool odd;
	DWORD now = GetTickCount();
	///////////////////자릿수 설정
	if (h.dmg / 1000000 > 0) digit = 7;
	else if (h.dmg / 100000 > 0)digit = 6;
	else if (h.dmg / 10000 > 0)digit = 5;
	else if (h.dmg / 1000 > 0)digit = 4;
	else if (h.dmg / 100 > 0)digit = 3;
	else if (h.dmg / 10 > 0)digit = 2;
	else digit = 1;
	odd = digit % 2;
	int mod = 1;
	for (int i = 0; i < digit; i++) {
		mod *= 10;
	}
	//글자는 30x27로
	char t[50];
	int left = h.x - ((digit) * 30 + odd ? 15 : 0);
	for (int i = 0; i < digit; i++) {//프린트
		if (h.isCrit) {					//크리티컬이면
			if (mod / 10>0) sprintf(t, "대미지_크리티컬_%d", h.dmg% mod / (mod / 10));
			else sprintf(t, "대미지_크리티컬_%d", h.dmg % mod);
			IMAGEMANAGER->findImage(t)->blurredrender(left + i * 30 - cam.x, h.y - cam.y, (h.time - now)<0xff ? h.time - now : 0xff);
			mod /= 10;
		}
		else {							//일반이면
			if (mod / 10>0) sprintf(t, "대미지_일반_%d", h.dmg% mod / (mod / 10));
			else sprintf(t, "대미지_일반_%d", h.dmg % mod);
			IMAGEMANAGER->findImage(t)->blurredrender(left + i * 30 - cam.x, h.y - cam.y, (h.time - GetTickCount())<0xff ? h.time - GetTickCount() : 0xff);
			mod /= 10;

		}
	}

}

static struct projectile {
	string imgName;
	int dmgmin, dmgmax;
	FLOAT distance;
	int frame;
	int framemax;
	int imgOffsetX, imgOffsetY;
	FLOAT x, y, z;
	FLOAT sizex, sizey, sizez;
	FLOAT speedx, speedy, speedz;
	FLOAT accelx, accely, accelz;
	effectedOnTime dmginfo;
	int abnormal;
	bool gravity;
	int hitCount;
};

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
