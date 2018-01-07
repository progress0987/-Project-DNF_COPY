#pragma once
#include"gameNode.h"
#include "D2DImage.h"
#include "player.h"
#include "Seria.h"
#include "Village.h"
#include "Mirkwood.h"


class mainGame :  public gameNode
{

private:
	Seria* seriaRoom;
	Village* village;
	Mirkwood* mirkwood;
public:

	HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
	void LoadImages();

	void paint();
	void paintDC();


	mainGame();
	~mainGame();
};

