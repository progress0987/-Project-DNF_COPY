#include "stdafx.h"
#include "iniDataManager.h"


HRESULT iniDataManager::init()
{
	return S_OK;
}

void iniDataManager::release()
{
}

void iniDataManager::addData(const char * subject, const char * title, const char * body)
{
	INIData data;
	data.subject = subject;
	data.title = title;
	data.body = body;
	iniData vIniData;
	vIniData.push_back(data);
	this->vIniDatas.push_back(vIniData);
}

void iniDataManager::iniSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < vIniDatas.size(); i++) {
		iniData vData = vIniDatas[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body,str);//¼öÁ¤
		vData.clear();
	}
	vIniDatas.clear();

}

char * iniDataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[65] = { NULL };

	GetPrivateProfileString(subject, title, "", data, 65, str);

	return data;
}

int iniDataManager::loadDataInteger(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);
	return GetPrivateProfileInt(subject,title,0,str);
}

iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{
}
