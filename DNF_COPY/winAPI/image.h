#pragma once
#include "Animation.h"



/***********************************************************************
						170927
						IMG MANAGER

***********************************************************************/
class image
{
public:
	enum IMAGE_LOAD_KIND {
		LOAD_RESOURCE,		//리소스로부터
		LOAD_FILE,			//파일로부터
		LOAD_EMPTY,
		LOAD_END
	};
	typedef struct imgInfo {

		//Dword는 호환이 아예 불가능. 4byte 가 한계
		//LONG 은 32비트까지 호환이 가능한 4byte
		//int는 64비트까지 호환이 가능한 4byte
		//당연하지만 호환이 가능하다면 불안해지기때문에 컴퓨터는 호환하지않는 DWORD를 선호한다.
		DWORD resID;			//리소스 ID
		HDC hMemDC;				//메모리 DC
		HDC hRMemDC;			//회전 메모리 DC
		HBITMAP hBit;			//새로운 비트맵 핸들
		HBITMAP hRBit;			//회전 비트맵 핸들
		HBITMAP hOBit;			//기존 비트맵 핸들
		float x;
		float y;
		int width;
		int height;
		int currentFrameX;		//프레임 이미지 번호(가로)
		int currentFrameY;		//프레임 이미지 번호(세로)
		int maxFrameX;			//프레임 끝번호(가로)
		int maxFrameY;			//프레임 끝번호(세로)
		int frameWidth;			//프레임 이미지 한장당 가로 크기
		int frameHeight;		//프레임 이미지 한장당 세로 크기

		BYTE loadType;			//로드하는 타입(위에 IMAGE_LOAD_KIND에 정의)

		imgInfo() {
			resID =			0;
			hMemDC =		NULL;
			hBit =			NULL;
			hOBit =			NULL;
			x =				0;
			y =				0;
			width =			0;
			height =		0;

			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX =		0;
			maxFrameY =		0;
			frameWidth =	0;
			frameHeight =	0;

			loadType =		LOAD_RESOURCE;
		}
	}IMG_INFO, *LPIMG_INFO ;//*LPIMG_INFO 는 이미지를 여러곳에 할당해줄 수 있게 하기위함.(동일이미지 다중사용)
private:
		LPIMG_INFO		imgInfo;		//이미지 구조체
		CHAR*			fileName;		//피일 이름
		BOOL			trans;			//없앨 색상이 있는지
		COLORREF		transColor;		//어떤 색상을 날릴지(RGB값으로)
		BLENDFUNCTION	alphaBlendFunc;	//알파블랜드를 위한 정보
		LPIMG_INFO		alphaBlendImg;	//알파블랜드를 위한 이미지 정보

public:
	image();
	~image();
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor=FALSE);							//파일로 이미지 등록
	HRESULT init(const char* fileName,float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor=FALSE);			//자른부분으로 이미지 등록
	HRESULT	init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF tranCol);	//프레임으로 자를것
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transCol);					//전체를 프레임으로 자를것

	void release();
	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY,int sourX, int sourY, int sourWidth, int sourHeight);
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offsetY,BYTE alpha);//alpha - 0-255

	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY,BYTE alpha);
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc,int destX, int destY,int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void aniRender(HDC hdc, int destX, int destY, Animation* ani);
private:
		HBITMAP GetRotatedBitmap(HDC hdc, int source_x, int source_y,
			int dest_width, int dest_height, int pivotX, int pivotY, float angle, COLORREF bkColor);
public:
	void rotatedRender(HDC hdc, int destX, int destY, float angle);
	void rotatedRender(HDC hdc, int destX, int destY, int pivotX, int pivotY, float angle);


	inline HDC getMemDC(void) { return imgInfo->hMemDC; }
	/*****************************************************************************/
	//이미지 조작을 편하게 하기위한 getter, setter
	/*****************************************************************************/
	inline void setX(float x) { imgInfo->x = x; }
	inline float getX() { return imgInfo->x; }

	inline void setY(float y) { imgInfo->y = y; }
	inline float getY() { return imgInfo->y; }

	inline void setCenter(float x, float y) { imgInfo->x = x-(imgInfo->width/2); imgInfo->y = y-(imgInfo->height/2); }
	
	inline float getCenterX() { return imgInfo->maxFrameX <= 0 ? imgInfo->x + (imgInfo->width / 2) : imgInfo->x + (imgInfo->frameWidth / 2); }
	inline float getCenterY() { return imgInfo->maxFrameY <= 0 ? imgInfo->y + (imgInfo->height / 2) : imgInfo->y + (imgInfo->frameHeight / 2); }

	inline void setFrameX(int frameX) { imgInfo->currentFrameX = frameX; if (frameX > imgInfo->maxFrameX)imgInfo->currentFrameX = imgInfo->maxFrameX; }
	inline void setFrameY(int frameY) { imgInfo->currentFrameY = frameY; if (frameY > imgInfo->maxFrameY)imgInfo->currentFrameY = imgInfo->maxFrameY; }

	inline int getMaxFrameX() { return imgInfo->maxFrameX; }
	inline int getMaxFrameY() { return imgInfo->maxFrameY; }

	inline int getFrameX() { return imgInfo->currentFrameX; }
	inline int getFrameY() { return imgInfo->currentFrameY; }
	
	inline int getFrameWidth() { return imgInfo->frameWidth; }
	inline int getFrameHeight() { return imgInfo->frameHeight; }

	inline int getWidth() { return imgInfo->width; }
	inline int getHeight() { return imgInfo->height; }

};

