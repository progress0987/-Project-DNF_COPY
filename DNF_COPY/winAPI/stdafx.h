// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ ��Ÿ�� ��� �����Դϴ�.
//#include<iostream>


//���� ���� STL
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
// ##���� ���� ������� ��⿡ �߰�!!
//====================================


//====================================
//   ##������ �� ##(������ �ʱ�ȭ ����)
//====================================

#define WINNAME (LPTSTR)(TEXT("DNF_COPY"))
#define WINSTARTX 100
#define WINSTARTY 50
#define WINSIZEX  800
#define WINSIZEY  600
#define WINSTYLE  WS_CAPTION|WS_SYSMENU



//�����Լ� ������
#define RND				randomFunction::getSingleton()
//Ű�Ŵ���
#define KEYMANAGER		KeyManager::getSingleton()

#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()

#define SOUNDMANAGER	soundManager::getSingleton()
#define TXTDATA			txtData::getSingleton()

#define INIDATAMANAGER	iniDataManager::getSingleton()
//===============================================
//   ##��ũ�� �Լ� ##(���ΰ��� ������ �κп��� ���)
//===============================================

#define SAFE_DELETE(p)  {if(p) {delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if(p){(p)->release();(p)=nullptr;}}

//=================================================
//   ##�������� ## (�ν��Ͻ�, ������ �ڵ�, ���콺 ��ǥ)
//=================================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT ptMouse;
extern FLOAT ptScale;
extern Camera cam;
extern LPDIRECT3D9					g_pD3D;						//D3D ����̽��� ������ D3D ��ü ����
extern LPDIRECT3DDEVICE9			g_pd3dDevice;				//D3D ����̽�
extern LPDIRECT3DSURFACE9			g_pd3dSurface;
extern LPD3DXSPRITE					g_pd3dSprite;
extern HDC							hdc;						//DCŬ����
extern player*						pl;
extern map<string, Item>			itemList;
extern vector<string>				itemNames;
extern bool							onDebug;

extern bool clicked;
extern bool lstay;
extern bool rclicked;


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
	wp_empty,			//����
	wp_sswd,			//�Ұ�
	wp_gswd,			//���
	wp_kat,				//��
						//���� �� �߰�
};
static enum ArmorType {
	arm_cloth,			//õ����
	arm_leather,		//����
	arm_larmor,			//�氩
	arm_harmor,			//�߰�
	arm_plate			//�Ǳ�
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
	///////////////////�ڸ��� ����
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
	//���ڴ� 30x27��
	char t[50];
	int left = h.x - ((digit) * 30 + odd ? 15 : 0);
	for (int i = 0; i < digit; i++) {//����Ʈ
		if (h.isCrit) {					//ũ��Ƽ���̸�
			if (mod / 10>0) sprintf(t, "�����_ũ��Ƽ��_%d", h.dmg% mod / (mod / 10));
			else sprintf(t, "�����_ũ��Ƽ��_%d", h.dmg % mod);
			IMAGEMANAGER->findImage(t)->blurredrender(left + i * 30 - cam.x, h.y - cam.y, (h.time - now)<0xff ? h.time - now : 0xff);
			mod /= 10;
		}
		else {							//�Ϲ��̸�
			if (mod / 10>0) sprintf(t, "�����_�Ϲ�_%d", h.dmg% mod / (mod / 10));
			else sprintf(t, "�����_�Ϲ�_%d", h.dmg % mod);
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

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
