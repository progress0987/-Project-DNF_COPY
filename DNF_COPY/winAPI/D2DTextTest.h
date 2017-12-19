#pragma once
class D2DTextTest
{
private:
	static  D2DTextTest*      TextInst;
	ID3DXFont*  m_pFont;
	int         m_nMax_X;
	int         m_nMax_Y;
public:
	D2DTextTest();
	~D2DTextTest();
	void    Init(void);
	void    Print(LPCSTR cSTR, int nX/*문자열의 왼쪽좌표*/ = 0, int nY/*문자열의 윗쪽좌표*/ = 0, D3DXCOLOR ARGB = 0xFFFFFFFF);
	static  D2DTextTest*      GetInst(void);
	void        FreeInst(void);
};


