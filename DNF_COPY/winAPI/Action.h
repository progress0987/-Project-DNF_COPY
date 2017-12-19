#pragma once
//#include "gameNode.h"
//
//typedef void(*CALLBACK_FUNCTION)();
//class Action:public gameNode
//{
//private:
//
//	image* img;				//이미지
//	float startX, startY;	//시작좌표
//	float endX, endY;		
//
//	float angle;			//각도
//	float travelRange;		//이동거리
//	float worldTimeCount;	//
//	float time;
//
//	bool isMoving;
//
//	CALLBACK_FUNCTION callbackfunc;
//public:
//
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//	void render();
//
//	void moveTo(image* image, float endx, float endy,float time);
//	void moveTo(image* image, float endx, float endy, float time, CALLBACK_FUNCTION cbfunc);
//
//	void moving();
//
//	bool getIsMoving() { return this->isMoving; }
//
//
//	Action();
//	~Action();
//};
//
