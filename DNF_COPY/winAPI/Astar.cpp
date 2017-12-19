#include "stdafx.h"
#include "Astar.h"


list<ANode> Astar::findPath(ANode * from, ANode * to)
{
	return list<ANode>();
}

Astar::Astar()
{
}


Astar::~Astar()
{
}
//
//#include "stdafx.h"
//#include "aStar.h"
//
//
//
//aStar::aStar()
//{
//}
//
//
//aStar::~aStar()
//{
//}
//
//HRESULT aStar::init(void)
//{
//	_aStarState = ASTAR_STATE_END;//초기=타일배치 완료전
//
//	_selectedType = TILE_TYPE_EMPTY;//배치할 타일 속성 = 빈거
//	_selectedTypeColor = RGB(255, 255, 255);		//색은 하양이로
//
//	_startPointSet = false;	//시작지점 배치 여부
//	_endPointSet = false;	//도작지점 배치여부
//
//
//
//
//	for (int i = 0; i < TILE_Y; i++)
//	{
//		for (int j = 0; j < TILE_X; j++)
//		{
//			_tile[i][j].type = TILE_TYPE_EMPTY;
//			_tile[i][j].color = RGB(255, 255, 255);
//			_tile[i][j].parent = nullptr;//부모타일
//			_tile[i][j].F = BIGNUM;
//			_tile[i][j].H = 0;//당연히 계산전이니까
//			_tile[i][j].i = i;
//			_tile[i][j].j = j;
//			_tile[i][j].rc =
//				RectMake(WINSIZEX - (TILE_X + 1)* WIDTH + WIDTH * j,
//					WINSIZEY / 2 - (TILE_Y / 2) * HEIGHT + HEIGHT * i,
//					WIDTH, HEIGHT);//렉트 할당
//
//		}
//	}
//
//	return S_OK;
//}
//
//void aStar::release(void)
//{
//}
//
//void aStar::update(void)
//{
//	if (_aStarState == ASTAR_STATE_END)//배치가 끝나지 않았다면
//	{
//		tileComposition();//타일을 배치하자
//	}
//	//시작이랑 도착이 설치 되어있고 스페이스 누르면 초기화
//	if (KEYMANAGER->isonceKeyDown(VK_SPACE)
//		&& _startPointSet && _endPointSet && _aStarState == ASTAR_STATE_END)
//	{
//		tileInitializing();
//	}
//	//배치중이거나 탐색했거나 길이엄쓰면 실행 ㄴㄴ
//	if (_aStarState == ASTAR_STATE_END || _aStarState == ASTAR_STATE_FOUND || _aStarState == ASTAR_STATE_NOWAY)return;
//
//
//	addOpenList();          //오픈리스트에 추가 후 G값 계산
//	calculateH();           //H계산
//	calculateF();           //F계산
//	addCloseList();         //클로즈리스트에 추가
//	checkArrive();          //도착 여부 체크
//}
//
//void aStar::render(void)
//{
//	PatBlt(getMemDc(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//
//	TextOut(getMemDc(), 15, 15, "1 : empty", strlen("1 : empty"));
//	TextOut(getMemDc(), 15, 35, "2 : Start", strlen("2 : Start"));
//	TextOut(getMemDc(), 15, 55, "3 : End", strlen("3 : End"));
//	TextOut(getMemDc(), 15, 75, "4 : Wall", strlen("4 : Wall"));
//
//
//	char str[128];
//	if (_aStarState == ASTAR_STATE_END)
//		sprintf_s(str, "space press");
//	else if (_aStarState == ASTAR_STATE_FOUND)
//		sprintf_s(str, "way found");
//	else if (_aStarState == ASTAR_STATE_NOWAY)
//		sprintf_s(str, "no way");
//	else if (_aStarState == ASTAR_STATE_SEARCHING)
//		sprintf_s(str, "serching...");
//
//	TextOut(getMemDc(), 15, 150, str, strlen(str));
//
//	HBRUSH newBrush, oldBrush;
//	/*HFONT newFont, oldFont;
//
//	newFont = CreateFont(9, 0, 0, 0, FW_NORMAL, false, false, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
//	PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림");
//	*/
//
//
//	for (int i = 0; i < TILE_Y; i++)
//	{
//		for (int j = 0; j < TILE_X; j++)
//		{
//			newBrush = CreateSolidBrush(_tile[i][j].color);
//			oldBrush = (HBRUSH)SelectObject(getMemDc(), newBrush);
//
//
//			Rectangle(getMemDc(), _tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].rc.right, _tile[i][j].rc.bottom);
//			SelectObject(getMemDc(), oldBrush);
//			DeleteObject(newBrush);
//
//			//F가 BIGNUM보다 작을때만 (F/G/H)를 화면에 표시하자
//			if (_tile[i][j].F < BIGNUM)
//			{
//				SetBkMode(getMemDc(), TRANSPARENT);
//				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].F);
//				TextOut(getMemDc(), _tile[i][j].rc.left + 2, _tile[i][j].rc.top + 2, _tile[i][j].str, strlen(_tile[i][j].str));
//
//				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].G);
//				TextOut(getMemDc(), _tile[i][j].rc.left + 2, _tile[i][j].rc.top + 22, _tile[i][j].str, strlen(_tile[i][j].str));
//
//				sprintf_s(_tile[i][j].str, "%d", _tile[i][j].H);
//				TextOut(getMemDc(), _tile[i][j].rc.left + 22, _tile[i][j].rc.top + 22, _tile[i][j].str, strlen(_tile[i][j].str));
//			}
//			if (_tile[i][j].parent == NULL)continue;
//
//			int length = 15;
//
//
//			MoveToEx(getMemDc(), (_tile[i][j].rc.left + _tile[i][j].rc.right) / 2,
//				(_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2, NULL);
//
//			LineTo(getMemDc(), (_tile[i][j].parent->j - _tile[i][j].j)* length +
//				(_tile[i][j].rc.left + _tile[i][j].rc.right) / 2,
//				(_tile[i][j].parent->i - _tile[i][j].i) * length + (_tile[i][j].rc.top + _tile[i][j].rc.bottom) / 2);
//
//		}
//	}
//
//	//SelectObject(getMemDc(), oldFont);
//	//DeleteObject(newFont);
//
//}
//
//void aStar::tileComposition()
//{
//	if (KEYMANAGER->isonceKeyDown('1')) { _selectedType = TILE_TYPE_EMPTY; _selectedTypeColor = RGB(255, 255, 255); }
//	if (KEYMANAGER->isonceKeyDown('2')) { _selectedType = TILE_TYPE_START; _selectedTypeColor = RGB(100, 255, 100); }
//	if (KEYMANAGER->isonceKeyDown('3')) { _selectedType = TILE_TYPE_END; _selectedTypeColor = RGB(255, 100, 100); }
//	if (KEYMANAGER->isonceKeyDown('4')) { _selectedType = TILE_TYPE_WALL; _selectedTypeColor = RGB(100, 100, 255); }
//
//
//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
//	{
//		for (int i = 0; i < TILE_Y; i++)
//		{
//			for (int j = 0; j < TILE_X; j++)
//			{
//				if (PtInRect(&_tile[i][j].rc, _ptMouse))
//				{
//					//시작지점 및 끝지점 셋틷
//					if (_tile[i][j].type == TILE_TYPE_START)_startPointSet = false;
//					if (_tile[i][j].type == TILE_TYPE_END)_endPointSet = false;
//
//					_tile[i][j].type = _selectedType;
//					_tile[i][j].color = _selectedTypeColor;
//
//
//					if (_selectedType == TILE_TYPE_START)
//					{
//						if (_startPointSet)
//						{
//							_tile[_startY][_startX].color = RGB(255, 255, 255);
//							_tile[_startY][_startX].type = TILE_TYPE_EMPTY;
//						}
//						_startPointSet = true;
//						_startX = j;
//						_startY = i;
//					}
//					if (_selectedType == TILE_TYPE_END)
//					{
//						if (_endPointSet)
//						{
//							_tile[_endY][_endX].color = RGB(255, 255, 255);
//							_tile[_endY][_endX].type = TILE_TYPE_EMPTY;
//						}
//						_endPointSet = true;
//						_endX = j;
//						_endY = i;
//					}
//				}
//			}
//		}
//	}
//}
//
//void aStar::tileInitializing()
//{
//	for (int i = 0; i < TILE_Y; i++)
//	{
//		for (int j = 0; j < TILE_X; j++)
//		{
//			if (_tile[i][j].type == TILE_TYPE_EMPTY)                     //일반타일
//			{
//				_tile[i][j].walkable = true;
//				_tile[i][j].listOn = false;
//			}
//			else if (_tile[i][j].type == TILE_TYPE_WALL)                 //에베레스트산
//			{
//				_tile[i][j].walkable = false;
//				_tile[i][j].listOn = false;
//			}
//			else if (_tile[i][j].type == TILE_TYPE_START)                //ㄱㄱ
//			{
//				_tile[i][j].walkable = true;
//				_tile[i][j].listOn = true;
//				_closeList.push_back(&_tile[i][j]);
//			}
//			else if (_tile[i][j].type == TILE_TYPE_END)                  //종료
//			{
//				_endX = j;
//				_endY = i;
//				_tile[i][j].walkable = true;
//				_tile[i][j].listOn = false;
//			}
//		}
//	}
//
//	_aStarState = ASTAR_STATE_SEARCHING;
//	_lastIndex = 0;
//}
//
//void aStar::addOpenList()
//{
//	Ci = _closeList[_lastIndex]->i;		//마지막으로 추가된 클로즈 리스트의 i - y
//	Cj = _closeList[_lastIndex]->j;		//마지막으로 추가된 클로즈 리스트의 j - x
//	Cg = _closeList[_lastIndex]->G;		//마지막으로 추가된 클로즈 리스트의 g
//
//										/*
//										123
//										456
//										789
//										순서
//										*/
//	if (Ci != 0)//0번째 줄이 아니면 상단라인을 연산하자
//	{
//		//2
//		if (_tile[Ci - 1][Cj].walkable)//상단 가운데 타일이 지나갈수 이쓰면
//		{
//			if (!_tile[Ci - 1][Cj].listOn)//오픈리스트에 포함이 안된 타일이면
//			{
//				_tile[Ci - 1][Cj].listOn = true;//오픈리스트에 포함되었다.
//				_tile[Ci - 1][Cj].color = RGB(220, 255, 220);//
//				_tile[Ci - 1][Cj].G = Cg + 10;//타일의 g값을 클로즈 리스트의 누적 G+10
//											  //타일의 부모를 클로즈 리스트의 마지막으로 추가된 타일로 설정
//				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
//				_openList.push_back(&_tile[Ci - 1][Cj]);//오픈리스트를 푸시푸시베이베
//
//			}
//			else //오픈리스트에 포함이 되어있던 타일이면
//			{
//				if (Cg + 10 < _tile[Ci - 1][Cj].G)//기존 G값보다 새로 계산 G값이 작다면
//				{
//					_tile[Ci - 1][Cj].G = Cg + 10;//새로계산
//					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
//				}
//			}
//		}
//		//1
//		if (Cj != 0)//좌상단 : 0번쨰 열이 아니라면
//		{
//			//좌상단 타일의 왼쪽이나 아래에 벽이 엄쓰면
//			if (_tile[Ci - 1][Cj - 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)
//			{
//				if (!_tile[Ci - 1][Cj - 1].listOn)
//				{
//					_tile[Ci - 1][Cj - 1].listOn = true;
//					_tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
//					_tile[Ci - 1][Cj - 1].G = Cg + 14;//대각선이므로
//					_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
//					_openList.push_back(&_tile[Ci - 1][Cj - 1]);
//				}
//				else
//				{
//					if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
//					{
//						_tile[Ci - 1][Cj - 1].G = Cg + 14;
//						_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
//					}
//				}
//			}
//		}
//		//3
//		if (Cj != TILE_X - 1)//우상단 : 마지막 열이 아니면
//		{//우상담 타일의 왼쪽이나 아래에 벽이 엄쓰면
//			if (_tile[Ci - 1][Cj + 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)
//			{
//				if (!_tile[Ci - 1][Cj + 1].listOn)
//				{
//					_tile[Ci - 1][Cj + 1].listOn = true;
//					_tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
//					_tile[Ci - 1][Cj + 1].G = Cg + 14;
//					_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
//					_openList.push_back(&_tile[Ci - 1][Cj + 1]);
//				}
//				else
//				{
//					if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
//					{
//						_tile[Ci - 1][Cj + 1].G = Cg + 14;
//						_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
//					}
//				}
//			}
//		}
//	}
//	//4
//	if (Cj != 0)//좌측 :  0번째 열이 아니라면
//	{
//		if (_tile[Ci][Cj - 1].walkable)//좌측타일이 이동가능 하면
//		{
//			if (!_tile[Ci][Cj - 1].listOn)
//			{
//				_tile[Ci][Cj - 1].listOn = true;
//				_tile[Ci][Cj - 1].color = RGB(220, 255, 220);
//				_tile[Ci][Cj - 1].G = Cg + 10;
//				_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
//				_openList.push_back(&_tile[Ci][Cj - 1]);
//			}
//			else
//			{
//				if (Cg + 10 < _tile[Ci][Cj - 1].G)
//				{
//					_tile[Ci][Cj - 1].G = Cg + 10;
//					_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
//				}
//			}
//		}
//	}
//	//6
//	if (Cj != TILE_X - 1)//우측 : 마지막 열이 아니라면
//	{
//		if (_tile[Ci][Cj + 1].walkable)//우측 타일이 이동가능하다면
//		{
//			if (!_tile[Ci][Cj + 1].listOn)
//			{
//				_tile[Ci][Cj + 1].listOn = true;
//				_tile[Ci][Cj + 1].color = RGB(220, 255, 220);
//				_tile[Ci][Cj + 1].G = Cg + 10;
//				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
//				_openList.push_back(&_tile[Ci][Cj + 1]);
//			}
//			else
//			{
//				if (Cg + 10 < _tile[Ci][Cj + 1].G)
//				{
//					_tile[Ci][Cj + 1].G = Cg + 10;
//					_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
//				}
//			}
//		}
//	}
//	if (Ci != TILE_Y - 1)//마지막 행이 아니라면 하단 라인 계산
//	{
//		//8
//		if (_tile[Ci + 1][Cj].walkable)//하단 가운데 이동이 가능하면
//		{
//			if (!_tile[Ci + 1][Cj].listOn)
//			{
//				_tile[Ci + 1][Cj].listOn = true;
//				_tile[Ci + 1][Cj].color = RGB(220, 255, 220);
//				_tile[Ci + 1][Cj].G = Cg + 10;
//				_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
//
//				_openList.push_back(&_tile[Ci + 1][Cj]);
//			}
//			else
//			{
//				if (Cg + 10 < _tile[Ci + 1][Cj].G)
//				{
//					_tile[Ci + 1][Cj].G = Cg + 10;
//					_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
//				}
//			}
//		}
//		//7
//		if (Cj != 0)// 좌하단 : 0번째 열이 아니라면
//		{
//			//좌하단 타일의 오른쪽이나 위에 벽이 없으면
//			if (_tile[Ci + 1][Cj - 1].walkable && _tile[Ci + 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)
//			{
//				if (!_tile[Ci + 1][Cj - 1].listOn)
//				{
//					_tile[Ci + 1][Cj - 1].listOn = true;
//					_tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
//					_tile[Ci + 1][Cj - 1].G = Cg + 14;
//					_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
//					_openList.push_back(&_tile[Ci + 1][Cj - 1]);
//				}
//				else
//				{
//					if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
//					{
//						_tile[Ci + 1][Cj - 1].G = Cg + 14;
//						_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
//					}
//				}
//			}
//		}
//		//9
//		if (Cj != TILE_X - 1)// 우하단 :  마지막 열이 아니라면
//		{
//			//우하단 타일의 오른쪽이나 위가 이동 가능하다면
//			if (_tile[Ci + 1][Cj + 1].walkable && _tile
//				[Ci + 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)
//			{
//				if (!_tile[Ci + 1][Cj + 1].listOn)
//				{
//					_tile[Ci + 1][Cj + 1].listOn = true;
//					_tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
//					_tile[Ci + 1][Cj + 1].G = Cg + 14;
//					_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
//					_openList.push_back(&_tile[Ci + 1][Cj + 1]);
//				}
//				else
//				{
//					if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
//					{
//						_tile[Ci + 1][Cj + 1].G = Cg + 14;
//						_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
//					}
//				}
//			}
//		}
//	}
//}
//
//void aStar::calculateH()
//{
//	for (int i = 0; i < _openList.size(); i++)
//	{
//		//모두 맨하탄거리로 구한다
//		int vertical = (_endX - _openList[i]->j) * 10; //세로
//		int horizontal = (_endY - _openList[i]->i) * 10;
//
//		if (vertical < 0) vertical *= -1;		//방향이 반대면 음수부여(절대값)
//		if (horizontal < 0)horizontal *= -1;
//
//		_openList[i]->H = vertical + horizontal;//총 H값  : 가로 더하기 세로
//
//
//	}
//}
//
//void aStar::calculateF()
//{
//	for (int i = 0; i < _openList.size(); i++)
//	{
//		_openList[i]->F = _openList[i]->G + _openList[i]->H;
//	}
//}
//
//void aStar::addCloseList()
//{
//	if (_openList.size() == 0)//검색을 해찌만 오픈리스트의 사이즈가 0이면 더이상 찾지마셈 - 끝났음(더이상 탐색할 노드가 없음)
//	{
//		_aStarState = ASTAR_STATE_NOWAY; //경로 엄쓰
//		return;			//작업노노
//	}
//
//	int index = 0;					//오픈 리스트중 가장 F가 작은 타일의 인덱스
//	int lowest = BIGNUM;			//오픈 리스트중 가장 작은 F값
//
//	for (int i = 0; i < _openList.size(); i++)
//	{
//		if (_openList[i]->F < lowest)//오픈 리스트의 F가 가장작은거 보다 더 작으면
//
//		{
//			lowest = _openList[i]->F;			//lowest를 F로 바꿈
//			index = i;
//		}
//	}
//	_openList[index]->color = RGB(180, 180, 255);//
//
//	_closeList.push_back(_openList[index]);		//클로즈 리스트 추가
//	_openList.erase(_openList.begin() + index);//클로즈 리스트에 추가된 타일은 오픈 리스트에서 제외하자
//
//	_lastIndex++;
//}
//
//void aStar::checkArrive()
//{
//	//클로즈리스트의 i j가 도착지점과 같다면
//	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)
//	{
//		_aStarState = ASTAR_STATE_FOUND;		//나이스하게 찾음
//		_closeList[_lastIndex]->color = RGB(255, 0, 0); //도착지점 색상
//		showWay(_closeList[_lastIndex]);//경로를 보여주셈
//	}
//}
//void aStar::showWay(aStarTile * tile)
//{
//	if (!(tile->i == _endY && tile->j == _endX))//도착지점 아니면
//		tile->color = RGB(255, 0, 255);//
//	tile = tile->parent;//타일의 부모를 참조해서 showway함수에 다시 넣자
//
//	if (tile->parent == NULL) {//타일의 부모가 시작지점이면 그만 끝내자 제발
//		return;
//	}
//
//	else
//		showWay(tile);//다시 부르자
//
//
//
//}
