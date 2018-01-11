#include"stdafx.h"
#include"mainGame.h"
//API : Application Programming Interface

HINSTANCE _hInstance;		//어플 고유번호
HWND _hWnd;					//조작질

LPDIRECT3D9					g_pD3D;					  //D3D 디바이스를 생성할 D3D 객체 변수
LPDIRECT3DDEVICE9			g_pd3dDevice;			  //D3D 디바이스
LPDIRECT3DSURFACE9			g_pd3dSurface;
LPD3DXSPRITE				g_pd3dSprite;
HDC							hdc;					  //DC클래스
Camera						cam;
player* pl;

LPTSTR _lpszClass = TEXT("API BASE");

POINT ptMouse;
FLOAT ptScale;			//스케일 값(마우스로함)
mainGame _mg;


void setWindowsSize(int x, int y, int width, int height);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;			//메세지
	WNDCLASS wndClass;		//윈도우 정보를 담을 구조체

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 백그라운드 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘
	wndClass.hInstance = hInstance;									//윈도우 인스턴스 번호
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;							//윈도우 클래스 이름
	wndClass.lpszMenuName = NULL;									//윈도우 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 창 스타일

																	//윈도우 정보 등록
	RegisterClass(&wndClass);

	//윈도우 창 생성정보
	_hWnd = CreateWindow(WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
			
	//윈도우 창을 모니터에 띄워줌
	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(_hWnd, cmdShow);


	//메인게임이 초기화가 안되면 끄기
	if (FAILED(_mg.init()))
	{
		return 0;
	}

	//GetMessage : 메시지 정보가 들어오면 그때 반응
	//PeekMessage : 메시지 정보가 들어오든 말든 무조건 반응(상시 루프)
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);	//입력이 들어오는 순간 그 메시지 처리 담당
			DispatchMessage(&message);	//실제로 윈도우에 그 메시지 전달
		}
		else
		{
			TIMEMANAGER->update(120.0);
			_mg.update();
		}

	}
	//메시지 루프를 다 돌았다면 해제.
	_mg.release();

	return message.wParam;
}
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//윈도우 사이즈 재설정(클라이어트 영역을 정확히 잡아준다.)
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;		//가로크기
	winRect.bottom = height;	//세로크기

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}