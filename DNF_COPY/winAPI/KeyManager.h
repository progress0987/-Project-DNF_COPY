#pragma once
#include"singletonBase.h"
#include<bitset>
using namespace std;
//키 입력과 관련된 매니저

#define KEYMAX 256
class KeyManager:public singletonBase<KeyManager>
{

private : 

	bitset<KEYMAX>_keyUp;
	bitset<KEYMAX>_keyDown;
public:

	HRESULT init(void);
	void release(void);

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	bitset<KEYMAX>getKeyUp() { return _keyUp; }
	bitset<KEYMAX>getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	KeyManager();
	~KeyManager();
};

