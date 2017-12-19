#include "stdafx.h"
#include "SaveLoadTest.h"


void SaveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) load();

}

void SaveLoadTest::save()
{
	/*
	파일 입출력
	C - FILE*
	c++ - ifstream,ofstream
	WIN - createFile
	*/
	//////////////////////테스트부분 - 삭제///////////////////////

	HANDLE file;
	char str[128] = "테스트용";
	DWORD write;

	file = CreateFile("Test1.txt", GENERIC_WRITE, 0, NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	WriteFile(file, str, strlen(str), &write, NULL);
	CloseHandle(file);


	/////////////////////////////////////////////////////////////
}

void SaveLoadTest::load()
{
	///////////////////////////테스트용/////////////////////////////
	HANDLE file;
	char str[128];
	DWORD read;
	file = CreateFile("Test1.txt", GENERIC_READ, 0, NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	ReadFile(file, str, strlen(str), &read, NULL);
	CloseHandle(file);
	//메시지박스
	MessageBox(_hWnd, str, "로딩완료", MB_OK);
	//////////////////////////////////////////////////////////////////
}

SaveLoadTest::SaveLoadTest()
{
}


SaveLoadTest::~SaveLoadTest()
{
}
