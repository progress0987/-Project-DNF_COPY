#include "stdafx.h"
#include "imageManager.h"

extern LPDIRECT3DDEVICE9			g_pd3dDevice;
extern LPDIRECT3D9					g_pD3D;
extern LPDIRECT3DSURFACE9			g_pd3dSurface;


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init(void)
{
	return S_OK;
}

void imageManager::release(void)
{
}


D2DImage * imageManager::addImage(string key, LPDIRECT3DDEVICE9 dev, const char * fileName,bool trans, COLORREF transCol)
{
	D2DImage* img = findImage(key);
	if (img) return img;
	img = new D2DImage;
	if (FAILED(img->init(dev))) {
		SAFE_DELETE(img);
		return NULL;
	}
	if (trans)img->setImage(fileName, transCol);
	else img->setImage(fileName);
	ImageList.insert(make_pair(key, img));
	return img;
}

D2DImage * imageManager::addFrameImage(string key, LPDIRECT3DDEVICE9 dev, const char * fileName, int frameX, int frameY, bool trans, COLORREF transCol)
{
	D2DImage* img = findImage(key);
	if (img) return img;
	img = new D2DImage;
	if (FAILED(img->init(dev))) {
		SAFE_DELETE(img);
		return NULL;
	}
	if (trans)img->setImage(fileName, TRUE, frameX, frameY, transCol);
	else img->setImage(fileName, TRUE, frameX, frameY);
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
