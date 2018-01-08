#include "stdafx.h"
#include "imageManager.h"




imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{

	return S_OK;
}

void imageManager::release(void)
{
	for (map<string, D2DImage*>::iterator i = ImageList.begin(); i != ImageList.end(); i++) {
		if (i->second != NULL) i->second->release();
	}
}


D2DImage * imageManager::addImage(string key,const char * fileName,bool trans, COLORREF transCol)
{
	D2DImage* img = findImage(key);
	if (img) return img;
	img = new D2DImage;
	if (FAILED(img->init(g_pd3dDevice))) {
		SAFE_DELETE(img);
		return NULL;
	}
	if (trans)img->setImage(fileName,trans, transCol);
	else img->setImage(fileName);


	ImageList.insert(make_pair(key, img));
	return img;
}

D2DImage * imageManager::addFrameImage(string key, const char * fileName, int frameX, int frameY, bool trans, COLORREF transCol)
{
	D2DImage* img = findImage(key);
	if (img) return img;
	img = new D2DImage;
	if (FAILED(img->init(g_pd3dDevice))) {
		SAFE_DELETE(img);
		return NULL;
	}
	if (trans)img->setImage(fileName, TRUE, frameX, frameY,trans, transCol);
	else img->setImage(fileName, TRUE, frameX,trans, frameY);

	ImageList.insert(make_pair(key, img));
	return img;
}

D2DImage * imageManager::findImage(string key)
{
	mapImagerIter i = ImageList.find(key);

	//키 값을 찾을경우 해당 키에해당되는 값을 리턴
	if (i != ImageList.end()) {
		return i->second;
	}
	return NULL;
}

BOOL imageManager::deleteImage(string key)
{
	mapImagerIter i = ImageList.find(key);

	//키 값을 찾을경우 해당 키에해당되는 값을 리턴
	if (i != ImageList.end()) {
		i->second->release();
		SAFE_DELETE(i->second);
		ImageList.erase(i);
		return true;
	}
	return false;
}

BOOL imageManager::deleteAll()
{
	mapImagerIter i = ImageList.begin();

	for (; i != ImageList.end();) {
		if (i->second != NULL) {
			i->second->release();
			SAFE_DELETE(i->second);
			i = ImageList.erase(i);
		}
		else
			i++;
	}
	ImageList.clear();
	return TRUE;
}
