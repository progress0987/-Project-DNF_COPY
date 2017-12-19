#include "stdafx.h"
#include "txtData.h"


HRESULT txtData::init(void)
{
	return S_OK;
}

void txtData::release(void)
{
}

void txtData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];

	//ZeroMemory(str, sizeof(str));

	//for(int i = 0; i < vArray.size(); i++) {
	//	strncat_s(str, 128, vArray[i].c_str,126);

	//	if (1 < vArray.size())
	//		strcat(str, ",");
	//}
	return str;
}

vector<string> txtData::txtLoad(const char * loadFilename)
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile(loadFilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);


	return charArraySeperation(str);
}

vector<string> txtData::charArraySeperation(char charArray[])
{
	vector<string>vArray;

	char*temp;
	char* seperator = ",";
	char* token;

	token = strtok(charArray, seperator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, seperator))) {
		vArray.push_back(token);
	}

	return vArray;
}

txtData::txtData()
{
}


txtData::~txtData()
{
}
