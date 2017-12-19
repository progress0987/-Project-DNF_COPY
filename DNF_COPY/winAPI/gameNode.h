#pragma once
#include "image.h"


class gameNode
{

private:
	bool managerInit;
public:
	HRESULT init(void);
	HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render();


	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual~gameNode();
};

