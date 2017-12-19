#pragma once
#include "singletonBase.h"
#include <vector>

struct INIData
{
	const char*	subject;	//항목			ex)조조
	const char*	title;		//제목			ex)무력
	const char* body;		//값(value)		ex)30
};

class iniDataManager :public singletonBase<iniDataManager>
{
private:
	typedef vector<INIData> iniData;
	typedef vector<INIData>::iterator iniIter;

	typedef vector<iniData> iniDatas;
	typedef vector<iniData>::iterator inisIter;
	iniDatas vIniDatas;

public:

	HRESULT init();
	void release();

	
	//자료추가
	void addData(const char* subject, const char* title, const char* body);
	//세이브
	void iniSave(char* fileName);
	//로드
	char* loadDataString(const char* fileName, const char* subject, const char* title);
	int loadDataInteger(const char* fileName, const char* subject, const char* title);


	iniDataManager();
	~iniDataManager();
};

