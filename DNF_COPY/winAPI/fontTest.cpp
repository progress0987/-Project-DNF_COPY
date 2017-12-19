#include "stdafx.h"
#include "fontTest.h"


HRESULT fontTest::init(void)
{
	return E_NOTIMPL;
}

void fontTest::render()
{
	char str[128];
	HFONT oldFont, font1;
	//CreateFont(
	//	40,					//문자폭
	//	0,					//문자 넓이
	//	40,					//문자 기울기(각도)
	//	0,					//문자 방향
	//	600,				//문자 굵기
	//	0,					//bool 문자 기울기 true/false
	//	0,					//bool 문자 밑줄 true/false
	//	0,					//bool 문자 취소선 true/false
	//	HANGUL_CHARSET,		//문자 세팅
	//	0,					//출력정확도(?)
	//	0,					//클리핑 정확도
	//	0,					//출력의 퀄리티
	//	0,					//자간
	//	TEXT("궁서체")		//내부시스템폰트가져옴
	//);
	//FillRect(hdc, &RectMake(0, 0, WINSIZEX, WINSIZEY), CreateSolidBrush(RGB(255, 0, 0)));
	//font1 = CreateFont(80, 0, 0, 0, 300, true, 1, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("돋움체"));
	//SetBkMode(hdc,TRANSPARENT);
	//oldFont = (HFONT)SelectObject(hdc, font1);
	//sprintf(str, "배고프다");
	//
	//TextOut(hdc, 10, 100, str, strlen(str));

	DeleteObject(oldFont);
	DeleteObject(font1);

	//RECT rcText = RectMake(10, 300, 400, 100);
	//HFONT font2 = CreateFont(80, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH|FF_SWISS, TEXT("Import"));

	//HFONT oldfont2 = (HFONT)SelectObject(hdc, font2);
	//DrawText(hdc, TEXT("테스팅중"), 8, &rcText, DT_CENTER | DT_VCENTER|DT_SINGLELINE);
	//DeleteObject(oldfont2);
	//DeleteObject(font2);

}

fontTest::fontTest()
{
}


fontTest::~fontTest()
{
}
