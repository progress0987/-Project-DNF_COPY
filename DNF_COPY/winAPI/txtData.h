#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class txtData :public singletonBase<txtData>
{
public:
	HRESULT init(void);
	void release(void);

	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string>vArray);

	vector<string>txtLoad(const char* loadFilename);
	vector<string>charArraySeperation(char charArray[]);
	txtData();
	~txtData();
};

