#pragma once
#include "gameNode.h"



class enemy :public gameNode
{
protected:
public:

	HRESULT init(void);
	HRESULT init(const char* img, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	void move();
	void draw();
	enemy();
	~enemy();
};