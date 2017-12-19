#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

using namespace std;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> Scenelists;
	typedef map<string, gameNode*>::iterator SceneIter;

private:
	static gameNode* curScene;
	static gameNode* loadingScene;
	static gameNode* readyScene;
	
	Scenelists sceneLists;
	Scenelists loadingSceneLists;

	DWORD loadingThreadID;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	
	//¾À Ãß°¡
	gameNode* addScene(string sceneName, gameNode* scene);
	//·Îµù¾À Ãß°¡
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID lpv);

	sceneManager();
	~sceneManager();
};

