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
	void initItems();
	Seria* seriaRoom;
	Village* village;
	Mirkwood* mirkwood;
	vector<MapBase*> Maps;
	bool showDungeonSelect;
	bool showDungeonMoveScene;
	vector<RECT> dunRect;
	vector<string> dunName;
	bool onOpening;
	int openingPhase;
	int openingTick;
	int dunselected;
	int dunmovetick;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
	void LoadImages();
	void showdungeonselect();
	void showdunmoveScene();
	void showOpening();

	void paint();
	void paintDC();


	mainGame();
	~mainGame();
};

