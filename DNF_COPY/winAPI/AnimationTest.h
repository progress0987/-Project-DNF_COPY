#pragma once
#include "gameNode.h"
#include "Animation.h"

//받아서 테스트해볼것.
class AnimationTest
{
	image* test;

	Animation* ani1, *ani2, *ani3;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();


	AnimationTest();
	~AnimationTest();
};

