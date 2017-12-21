#pragma once

#include "singletonBase.h"
#include "D2DImage.h"
#include <map>




class imageManager : public singletonBase<imageManager>
{
private:

	typedef map<string, D2DImage*>mapImageList;
	typedef map<string, D2DImage*>::iterator mapImagerIter;

	mapImageList ImageList;

public:

	HRESULT init();
	void release(void);

	//파일 이미지
	D2DImage* addImage(string key,const char* fileName,bool trans=false, COLORREF transCol=NULL);

	//프레임 이미지
	D2DImage* addFrameImage(string key,  const char* fileName,  int frameX, int frameY, bool trans=false, COLORREF transCol=NULL);

	//키 값으로 이미지 찾아오는 함수
	D2DImage* findImage(string key);

	//이미지 지워주는 함수
	BOOL deleteImage(string key);

	//모든 이미지 삭제
	BOOL deleteAll();

	imageManager();
	~imageManager();
};

