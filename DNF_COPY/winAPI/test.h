#pragma once
/*
	#include <windows.h>
	#include <math.h>

	#define PI 3.141592654

	// 인수목록
	// HDC hdc :
	// HBITMAP hBitmap :
	// int source_x : 회전 이미지 비트맵에서의, 출력할 사각영역의 좌상단x좌표.
	// int source_y : 회전 이미지 비트맵에서의, 출력할 사각영역의 좌상단y좌표.
	// int dest_width : 회전할 비트맵 이미지의 폭 크기 == 회전할 비트맵 이미지가 출력될 폭 크기
	// int dest_heigjt : 회전할 비트맵 이미지의 높이 크기 == 회전할 비트맵 이미지가 출력될 높이 크기
	// float angle : 회전할 각도.
	// COLORREF bkColor : 회전후 생긴 공백영역을 칠할 색상. 이미지 사각형을 회전하면, 공백영역이 생깁니다. (예)다이아몬드 형태로 회전된 사각형에서의 뒤부분 영역
	// 그 공백영역을 미리 채울 색상을 지정합니다.

	HBITMAP GetRotatedBitmap( HDC hdc, HBITMAP hBitmap, int source_x, int source_y,
	int dest_width, int dest_height, float angle, COLORREF bkColor )
	{
	HDC sourceDC = CreateCompatibleDC(hdc); // 회전할 비트맵 원본을 선택할 DC
	HDC destDC = CreateCompatibleDC(hdc); // 회전할 비트맵을 출력받을 DC
	HBITMAP hbmResult = CreateCompatibleBitmap( hdc, dest_width, dest_height ); // 회전할 비트맵을 출력받을 메모리비트맵 핸들

	HBITMAP hbmOldSource= (HBITMAP)SelectObject( sourceDC, hBitmap ); // 회전할 비트맵 원본을 DC에 선택
	HBITMAP hbmOldDest = (HBITMAP)SelectObject( destDC, hbmResult ); // 회전할 비트맵을 출력받을 DC에, 회전할 비트맵을 출력받을 메모리비트맵 선택

	HBRUSH hbrBack = CreateSolidBrush( bkColor ); // 회전으로 인한, 공백영역을 칠할 브러시핸들 생성
	HBRUSH hbrOld = (HBRUSH)SelectObject( destDC, hbrBack ); // 브러시핸들 선택
	PatBlt( destDC, 0, 0, dest_width, dest_height, PATCOPY ); // 선택된 브러시로, 회전할 비트맵을 출력받을 DC에, 미리 색상을 채워 지움
	DeleteObject( SelectObject( destDC, hbrOld ) ); // 브러시 해제

	angle = (float)( angle * PI / 180 ); // 회전할 각도(360분법)를, 라디안단위의 각도로 변경
	float cosine = (float)cos( angle ); // 회전이동변환 행렬에 들어갈 cos세타 값을 구함
	float sine = (float)sin( angle ); // 회전이동변환 행렬에 들어갈 sin세타 값을 구함

	SetGraphicsMode(destDC, GM_ADVANCED); // 윈도우 좌표계의 회전을 위하여, 그래픽모드를 확장모드로 변경합니다.(요구사항:윈98,NT이상)

	// 회전이동변환 행렬을 정의.
	// (윈도우즈 API정복 개정판 2권 Page(1279) 참조.)
	// (게임 프로그래머를 위한 기초수학과 물리 Page(196) 참조.)

	XFORM xform; // 방정식을 표현하는 3행3열의 행렬 선언
	xform.eM11 = cosine; // 1행 1열 성분 설정 (회전성분)
	xform.eM12 = sine; // 1행 2열 성분 설정 (회전성분)
	xform.eM21 = -sine; // 2행 1열 성분 설정 (회전성분)
	xform.eM22 = cosine; // 2행 2열 성분 설정 (회전성분)
	xform.eDx = (FLOAT)dest_width / 2.0f; // 3행 1열 성분 설정 (X축 이동 성분)
	xform.eDy = (FLOAT)dest_height / 2.0f; // 3행 2열 성분 설정 (Y축 이동 성분)

	// 설정한 행렬로, 인수DC의 윈도우즈 좌표계를 변환.
	// 인수DC는 출력대상으로 메모리비트맵을 가지므로,
	// 선택하고 있는 메모리비트맵의 좌표체계가 회전된다.

	SetWorldTransform( destDC, &xform );

	// 회전된 메모리DC에, 회전할 이미지를 출력

	BitBlt(destDC, -(dest_width/2),-(dest_height/2), dest_width, dest_height, sourceDC, source_x, source_y, SRCCOPY );

	// 사용된 자원 해제

	SelectObject( sourceDC, hbmOldSource );
	SelectObject( destDC, hbmOldDest );
	DeleteObject(sourceDC);
	DeleteObject(destDC);

	// 회전된 비트맵 핸들 리턴

	return hbmResult;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 인수 목록
	// HDC hdc : 화면DC의 핸들. GetRotatedBitmap()함수의 인자로 전달하게 됩니다.
	// HDC hOffScreen : 회전 이미지를 출력할, 오프스크린DC의 핸들.
	// int dest_x : 오프스크린 상에서, 회전 이미지가 출력될 x좌표.
	// int dest_y : 오프스크린 상에서, 회전 이미지가 출력될 y좌표.
	// int dest_width : 회전할 비트맵 이미지의 폭 크기 == 회전할 비트맵 이미지가 출력될 폭 크기
	// int dest_heigjt : 회전할 비트맵 이미지의 높이 크기 == 회전할 비트맵 이미지가 출력될 높이 크기
	// HBITMAP hBit : 회전 이미지 비트맵핸들
	// int source_x : 회전 이미지 비트맵에서의, 출력할 사각영역의 좌상단x좌표.
	// int source_y : 회전 이미지 비트맵에서의, 출력할 사각영역의 좌상단y좌표.
	// DWORD dFlag : ROP모드를 나타내는 플래그 매크로
	// float angle : 회전할 각도.
	// COLORREF bkColor : 회전후 생긴 공백영역을 칠할 색상. 이미지 사각형을 회전하면, 공백영역이 생깁니다. (예)다이아몬드 형태로 회전된 사각형에서의 뒤부분 영역
	//
	void RotateBlt( HDC hdc, HDC hOffScreen, int dest_x, int dest_y, int dest_width, int dest_height,
	HBITMAP hBit, int source_x, int source_y, DWORD dFlag, float angle, COLORREF bkColor )
	{
	static HDC hTempMemDC; // 회전한 비트맵을 선택할 메모리DC
	HBITMAP hTempBitmap, hOldBitmap; // 회전한 비트맵을 저장할, 비트맵 핸들

	// 최초 한번만 비트맵DC를 생성합니다.

	if( !hTempMemDC ) hTempMemDC = CreateCompatibleDC( hdc );

	// 비트맵을 회전하는 함수를 호출하여, 리턴되는 회전된 비트맵 핸들을 저장

	hTempBitmap = GetRotatedBitmap( hdc, hBit, source_x, source_y, dest_width, dest_height, angle, bkColor );

	// 회전된 비트맵 핸들을 선택하고,

	hOldBitmap = (HBITMAP)SelectObject( hTempMemDC, hTempBitmap );

	// 오프스크린DC에, 회전된 비트맵 핸들을 선택한, 메모리DC의 이미지를 출력합니다.
	// 안의 주석을 해제하면, 출력좌표를 중심으로 하는 회전이미지가 됩니다.

	BitBlt( hOffScreen, dest_x
	// - dest_width/2
	, dest_y - dest_height/2, dest_width, dest_height,hTempMemDC, 0, 0, dFlag );

	SelectObject(hTempMemDC, hOldBitmap);
	DeleteObject(hTempBitmap);
	}

	HWND hWndMain; // 윈도우 핸들
	HDC hdc; // 화면 DC 핸들
	HDC hOffScreenDC; // 오프스크린 DC 핸들
	HBITMAP hOffScreenBitmap; // 오프스크린 DC 가 선택하는, 메모리 비트맵 핸들
	HBITMAP hMemBitmap; // 이미지를 담을, 메모리 비트맵 핸들

	void OnTimer(); // WM_TIMER메세지의, 핸들러 함수

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	switch (message)
		{
		case WM_CREATE:
			hWndMain = hWnd;
			// 화면DC, 오프스크린DC, 오프스크린의 메모리비트맵을 미리 생성합니다.
			
			hdc = GetDC(hWnd);
			hOffScreenDC = CreateCompatibleDC(hdc);
			hOffScreenBitmap = CreateCompatibleBitmap(hdc, 800, 600);
			SelectObject(hOffScreenDC, hOffScreenBitmap);
			PatBlt(hOffScreenDC, 0, 0, 800, 600, WHITENESS);
		
				// 이미지를 비트맵에 로드합니다.
			
				hMemBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),
					TEXT("player_walk.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_DEFAULTSIZE | LR_LOADFROMFILE);
		
				// 타이머 생성
			
				SetTimer(hWnd, 1, 20, NULL);
			break;
		
				case WM_TIMER:
					OnTimer();
					break;
				
						case WM_DESTROY:
							// 사용된 메모리 비트맵과, 오프스크린 DC, 타이머를 해제합니다.
						DeleteObject(hMemBitmap);
						DeleteObject(hOffScreenBitmap);
						DeleteDC(hOffScreenDC);
							KillTimer(hWnd, 1);
							PostQuitMessage(0);
							break;
							}

	return DefWindowProc(hWnd, message, wParam, lParam);
	}

	void OnTimer()
	{
	// 비트맵을 회전시킬 각도(360분법) 갱신
	
		static FLOAT angle = 0.0f;
	static BOOL bRotate = FALSE;

		if (GetKeyState(VK_LBUTTON) & 0x8000) { bRotate = TRUE; }

		if (bRotate)
		{
		angle += 5.0f;
		if (angle >= 360.0f)
			{
			bRotate = FALSE;
			angle = 0.0f;
			}
		}

		// 오프스크린DC의 이미지를, 하얀색으로 채워, 이전 프레임에서의 이미지를 삭제합니다.
	
		PatBlt(hOffScreenDC, 0, 0, 800, 600, WHITENESS);

		// 오프스크린DC에, 이미지의 마스크를 출력합니다.
	
		RECT Rt;
	GetClientRect(hWndMain, &Rt);
	RotateBlt(hdc, hOffScreenDC, Rt.right / 2, Rt.bottom / 2, 59, 59,
	hMemBitmap, 0, 0, SRCAND, angle, RGB(255, 255, 255));

		// 오프스크린DC에, 이미지를 출력합니다.
	
		RotateBlt(hdc, hOffScreenDC, Rt.right / 2, Rt.bottom / 2, 59, 59,
		hMemBitmap, 60, 0, SRCPAINT, angle, RGB(0, 0, 0));

		// 화면DC에, 오프스크린의 이미지를 출력합니다.
	
		BitBlt(hdc, 0, 0, 800, 600, hOffScreenDC, 0, 0, SRCCOPY);
	}
	*/

