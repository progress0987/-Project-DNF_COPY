//#pragma once
//#include "stdafx.h"
//class CFastPixel
//{
//public:
//	CFastPixel(CDC* pSrc);
//	~CFastPixel();
//	COLORREF GetPixel(int x, int y);
//protected:
//	CFastPixel();
//	LPVOID m_pBits;
//	int m_nBytePerLine;
//	BITMAPINFO* m_pbmi;
//	COLORREF(CFastPixel::*m_pGetPixel)(int x, int y);
//	COLORREF GetPixel8(int x, int y);
//	COLORREF GetPixel16(int x, int y);
//	COLORREF GetPixel24(int x, int y);
//	COLORREF GetPixel32(int x, int y);
//	COLORREF GetPixel16ByTable555(int x, int y);
//	COLORREF GetPixel16ByTable565(int x, int y);
//	COLORREF GetPixel32ByTable(int x, int y);
//};
//// 구현부
//CFastPixel::CFastPixel(CDC* pSrc)
//{
//	BITMAPINFO bmi;
//	ZeroMemory(&bmi, sizeof(bmi));
//	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
//	CBitmap* pBmSrc = pSrc->GetCurrentBitmap();
//	::GetDIBits(pSrc->m_hDC, *pBmSrc, 0, 0, NULL, &bmi, DIB_RGB_COLORS);
//	if (bmi.bmiHeader.biBitCount <= 4) // 16컬러 이하는 지원하지 않는다.
//	{
//		TRACE(_T("16컬러 이하는 지원하지 않는다.\n"));
//		_ASSERTE(0);
//		return;
//	}
//	// 압축포맷 지원안함.
//	if (bmi.bmiHeader.biCompression != BI_RGB && bmi.bmiHeader.biCompression != BI_BITFIELDS)
//	{
//		TRACE(_T("압축포맷 지원안함.\n"));
//		_ASSERTE(0);
//		return;
//	}
//	int nColor = 0;
//	if (bmi.bmiHeader.biBitCount == 8)
//		nColor = 1 << bmi.bmiHeader.biBitCount;
//	else if (bmi.bmiHeader.biCompression == BI_BITFIELDS)
//		nColor = 3;
//	else
//		nColor = 0;
//	m_pbmi = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFOHEADER) + nColor * sizeof(RGBQUAD)];
//	memcpy(m_pbmi, &bmi, sizeof(bmi.bmiHeader));
//	m_nBytePerLine = bmi.bmiHeader.biBitCount / 8 * bmi.bmiHeader.biWidth;
//	m_nBytePerLine = (m_nBytePerLine + 3) & ~3; // The scan lines must be aligned on a DWORD
//	m_pBits = new char[m_nBytePerLine * abs(bmi.bmiHeader.biHeight)];
//	m_pbmi->bmiHeader.biHeight = abs(bmi.bmiHeader.biHeight) * -1; // top-down
//	::GetDIBits(pSrc->m_hDC, *pBmSrc, 0, abs(bmi.bmiHeader.biHeight), m_pBits, m_pbmi, DIB_RGB_COLORS);
//	switch (m_pbmi->bmiHeader.biBitCount)
//	{
//	case 8:
//		m_pGetPixel = GetPixel8;
//		break;
//	case 16:
//		if (m_pbmi->bmiColors)
//		{
//			if (0x00007C00 == *(int*)&m_pbmi->bmiColors[0]) // 555
//			{
//				m_pGetPixel = GetPixel16ByTable555;
//			}
//			else
//			{
//				m_pGetPixel = GetPixel16ByTable565;
//			}
//		}
//		else
//		{
//			m_pGetPixel = GetPixel16;
//		}
//		break;
//	case 24:
//		m_pGetPixel = GetPixel24;
//		break;
//	case 32:
//		if (m_pbmi->bmiColors)
//		{
//			m_pGetPixel = GetPixel32ByTable;
//		}
//		else
//		{
//			m_pGetPixel = GetPixel32;
//		}
//		break;
//	default:
//		TRACE(_T("지원하지 않는 비트카운트\n"));
//		_ASSERTE(false);
//	}
//}
//CFastPixel::~CFastPixel()
//{
//	delete[] m_pBits;
//	delete[] m_pbmi;
//}
//COLORREF CFastPixel::GetPixel(int x, int y)
//{
//	return (this->*m_pGetPixel)(x, y);
//}
//COLORREF CFastPixel::GetPixel8(int x, int y)
//{
//	BYTE c = ((BYTE*)m_pBits)[x + (y * m_nBytePerLine)];
//	return RGB(m_pbmi->bmiColors[c].rgbRed,
//		m_pbmi->bmiColors[c].rgbGreen,
//		m_pbmi->bmiColors[c].rgbBlue);
//}
//// 1 pixel is 5bit
//COLORREF CFastPixel::GetPixel16(int x, int y)
//{
//	return GetPixel16ByTable555(x, y);
//}
//// 1 pixel is 8bit
//COLORREF CFastPixel::GetPixel24(int x, int y)
//{
//	int offset = (3 * x) + (y * m_nBytePerLine);
//	BYTE b = ((BYTE*)m_pBits)[offset];
//	BYTE g = ((BYTE*)m_pBits)[offset + 1];
//	BYTE r = ((BYTE*)m_pBits)[offset + 2];
//	return RGB(r, g, b);
//}
//// 1 pixel is 8bit
//COLORREF CFastPixel::GetPixel32(int x, int y)
//{
//	DWORD dw = ((DWORD*)m_pBits)[x + (y * (m_nBytePerLine / sizeof(DWORD)))];
//	return ((dw & 0x000000FF) << 24) + (dw & 0x0000FF00) + ((dw & 0x00FF0000) >> 24);
//}
//COLORREF CFastPixel::GetPixel16ByTable555(int x, int y)
//{
//	WORD* pBits = (WORD*)(m_pBits);
//	DWORD dwBit = pBits[x + (y * m_nBytePerLine / sizeof(WORD))];
//	// make 888
//	DWORD dwR = (0x00007C00 & dwBit) >> 10;
//	DWORD dwG = (0x000003E0 & dwBit) >> 5;
//	DWORD dwB = (0x0000001F & dwBit);
//	return RGB(((dwR << 8) - dwR) / 31, ((dwG << 8) - dwG) / 31, ((dwB << 8) - dwB) / 31);
//}
//COLORREF CFastPixel::GetPixel16ByTable565(int x, int y)
//{
//	WORD* pBits = (WORD*)(m_pBits);
//	DWORD dwBit = pBits[x + (y * m_nBytePerLine / sizeof(WORD))];
//	// make 888
//	DWORD dwR = (0x0000F800 & dwBit) >> 11;
//	DWORD dwG = (0x000007E0 & dwBit) >> 5;
//	DWORD dwB = (0x0000001F & dwBit);
//	return RGB(((dwR << 8) - dwR) / 31, ((dwG << 8) - dwG) / 63, ((dwB << 8) - dwB) / 31);
//}
//COLORREF CFastPixel::GetPixel32ByTable(int x, int y)
//{
//	DWORD dw = ((DWORD*)m_pBits)[x + (y * (m_nBytePerLine / sizeof(DWORD)))];
//	return ((dw & 0x000000FF) << 16) + (dw & 0x0000FF00) + ((dw & 0x00FF0000) >> 16);
//}
//
//
//출처: http://succubus93.tistory.com/120 [악마주식회사]