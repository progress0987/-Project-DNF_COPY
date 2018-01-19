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
//struct Item {
//	string name;
//	char imgName[50];
//	int branch;							//���ο��� ����� �������ִ���, ������������ �������(������ 0);
//	int id;								//������ �̹��� id
//	int type;							//������ ������ �� ��
//	int detail;							//������ ���λ���
//
//	int stack;							//�Ҹ�/��Ÿ ������ ����
//
//	int phydmgmin;							//��������
//	int magdmgmin;
//	int phydmgmax;
//	int magdmgmax;
//
//	int phydef;
//	int magdef;
//
//	int reachx;							//���⿡ ������
//	int reachz;							//���⿡ ������
//
//	int gainStr;
//	int gainInt;
//	int gainHealth;
//	int gainSpirit;
//
//	int gainHP;
//	int gainMP;
//	
//	int reqlvl;
//
//	bool equipped;
//
//	int price;
//
//	string description;
//};


struct HitQueue {
	bool isCrit;
	FLOAT x, y;
	int dmg;
	DWORD time;
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

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
