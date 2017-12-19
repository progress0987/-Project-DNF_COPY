#pragma once

//http://www.gisdeveloper.co.kr/?p=3897

struct ANode {
	int x, y;			//좌표
	DWORD N, S, E, W;	//북,남,동,서 의 가중치 값
	ANode* Parent;		//부모 노드
	//DWORD Depth;		//분기로부터 받아온 깊이
	DWORD F, G, H;		//F : 총 값, G : 시점에서 현재까지의 값, H : 현재에서 종점까지의 값
};


class Astar
{
private:
	list<ANode> CQueue;		//닫힌 큐
	list<ANode> OQueue;		//열린 큐
	ANode* Sour;			//시작 노드
	ANode* Cur;
	ANode* Dest;			//목적지 노드
	ANode** Map;			//현재의 맵
	int depth;
public:
	void setMap(ANode** begin) { Map = begin; }
	list<ANode> findPath(ANode* from, ANode* to);
	Astar();
	~Astar();
};


#pragma once
#include"gameNode.h"

#define TILE_X 20//가로
#define TILE_Y 20//세로
#define WIDTH  40//타일가로길이
#define HEIGHT 40//타일세로길이
#define BIGNUM 5000//충분히 큰 F값(초기값)

//타일을 속성을 정해보자
enum TILE_TYPE
{
	TILE_TYPE_EMPTY,		//빈타일(지나갈수 있는곳)
	TILE_TYPE_START,		//시작
	TILE_TYPE_END,			//끝
	TILE_TYPE_WALL			//장애물
};

//상태값
enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,		//검색중
	ASTAR_STATE_FOUND,			//발견
	ASTAR_STATE_NOWAY,			//길엄ㅅ씀
	ASTAR_STATE_END				//타일 배치 완료 전
};

//타일 구조체
struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;			//지나갈수이쌰냐
	bool listOn;			//오픈리스트에 추가 되었냥
	int i, j;				//배열의 인덱스

	int F = 0;
	int G = 0;
	int H = 0;
	char str[128];
	aStarTile* parent;		//부모타일 주소
	TILE_TYPE type;//타일 속성

};


class aStar : public gameNode
{

private:

	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*>_openList;
	vector<aStarTile*> _closeList;


	ASTAR_STATE _aStarState;


	TILE_TYPE _selectedType;		//타일 배치할때 사용할 속성녀석
	COLORREF _selectedTypeColor;	//타일 배치할때 사용할 타일색	


	int _startX, _startY;		//시작지점의 i,j
	int _endX, _endY;			//도착
	int _lastIndex;				//가장 나중에 추가된 클로즈 리스트의 인덱스

	bool _startPointSet;		//시작지점이 배치 되었냐
	bool _endPointSet;			//도작지점이 배치 되었냐

	int Ci;						//마지막으로 추가된 클로즈 리스트의 i
	int Cj;						//마지막으로 추가된 클로즈 리스트의 j
	int Cg;						//마지막으로 추가된 클로즈 리스트의 g

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void tileComposition();//타일 배치
	void tileInitializing();//타일 배치후 속성에 맞게 타일을 초기화
	void addOpenList();		//오픈리스트 추가
	void calculateH();		//오픈리스트 내 타일의 H계산
	void calculateF();		//오픈리스트 내 타일의 F계산
	void addCloseList();		//가장 작은 F 선택후 클로즈 리스트에추가
	void checkArrive();		//도착했는지 여부 체크

	void showWay(aStarTile* tile);//도착 후 시작지점과 도착지점을 잇는 경로를 보여주자
	aStar();
	~aStar();
};

