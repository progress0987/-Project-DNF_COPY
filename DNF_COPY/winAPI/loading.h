#pragma once
#include "gameNode.h"
#include "progressBar.h"


enum LOAD_KIND {
	LOAD_KIND_IMAGE_0,		//빈이미지
	LOAD_KIND_IMAGE_1,		//일반이미지
	LOAD_KIND_IMAGE_2,		//일반이미지인데 좌표있음
	LOAD_KIND_FRAMEIMAGE_0,	//프레임
	LOAD_KIND_FRAMEIMAGE_1,	//위와 동일한데 좌표있음
	LOAD_KIND_SOUND,
	LOAD_KIND_END,
};

struct ImageResouce {
	string keyName;				//이미지 키값
	const char* fileName;		//파일이름
	float x, y;					//위치좌표
	int width, height;			//가로세로 크기
	bool trans;					//투명여부
	COLORREF transCol;			//투명 색
};

class loadItem {
private:
	LOAD_KIND kind;
	ImageResouce imgResource;
public:
	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* filename, int width, int height, BOOL trans = FALSE, COLORREF transcol = FALSE);
	HRESULT initForImage(string keyName, const char* filename,float x, float y, int width, int height,BOOL trans = FALSE,COLORREF transcol = FALSE);

	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transcol = FALSE);
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transcol = FALSE);

	LOAD_KIND getLoadingKind() { return this->kind; }

	ImageResouce getImageResource(){ return this->imgResource; }
	loadItem();
	~loadItem();
};

class loading
{
private:
	typedef vector<loadItem*> items;
	typedef vector<loadItem*>::iterator itemsIter;

	items _vitems;

	image* bg;
	progressBar* loadingbar;
	int currGauge;
public:
	loading();
	~loading();

	void loadImage(string keyName, int width, int height);
	void loadImage(string keyName, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF col = FALSE);

	//void loadFrameImage(string keyName, const char* fileName, int width, int height, ...);

	//BOOL loadingDone();
	//vector<loadItem*>

};

