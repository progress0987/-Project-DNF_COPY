#pragma once
#include "gameNode.h"
//상호 참조중
class player:public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	player();
	~player();
};

