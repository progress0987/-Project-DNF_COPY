#pragma once
#include "player.h"

class player;
class UI
{
private:
	player* pl;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderdc(void);

	void linkPlayer(player* p) { pl = p; }

	UI();
	~UI();
};

