#include "stdafx.h"
#include "mainGame.h"

void mainGame::initItems()
{
	Item it = Item();

#pragma region 장비류
		//기본무기 - 무기없음
		{
			it.id = -1;
			it.name = "무기없음";
			it.reachx = 140;
			it.reachz = 140;
			it.phydmgmin = 5;
			it.phydmgmax = 10;
			it.magdmgmin = 5;
			it.magdmgmax = 10;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//아이템없음
		{
			it.id = -1;
			it.name = "없음";
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//창성의구원자 - 소검
		{
			it.id = 139;
			it.name = "창성의 구원자 - 소검";
			itemNames.push_back(it.name);
			sprintf(it.imgName, "sswd4000");
			it.type = item_weapon;
			it.detail = wp_sswd;
			it.phydmgmin = 1500;
			it.phydmgmax = 2000;
			it.magdmgmin = 2500;
			it.magdmgmax = 3000;
			it.reachx = 180;
			it.reachz = 150;
			it.branch = 1;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//일반검
		{
			it.id = 146;
			it.name = "일반검";
			itemNames.push_back(it.name);
			sprintf(it.imgName, "sswd4400");
			it.type = item_weapon;
			it.detail = wp_sswd;
			it.phydmgmin = 100;
			it.phydmgmax = 300;
			it.magdmgmin = 50;
			it.magdmgmax = 150;
			it.reachx = 180;
			it.reachz = 150;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//메탈라인 아머 상의
		{
			it.id = 66;
			it.name = "메탈라인 아머 상의";
			it.type = item_coat;
			it.detail = arm_plate;
			it.gainStr = 155;
			it.gainInt = 155;
			it.gainHealth = 158;
			it.gainSpirit = 110;
			it.phydef = 7286;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//메탈라인 아머 하의
		{
			it.id = 63;
			it.name = "메탈라인 아머 하의";
			it.type = item_pants;
			it.detail = arm_plate;
			it.gainStr = 155;
			it.gainInt = 155;
			it.gainHealth = 158;
			it.gainSpirit = 110;
			it.phydef = 3698;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//메탈라인 아머 어깨
		{
			it.id = 60;
			it.name = "메탈라인 아머 어깨";
			it.type = item_shoulder;
			it.detail = arm_plate;
			it.gainStr = 145;
			it.gainInt = 145;
			it.gainHealth = 150;
			it.gainSpirit = 110;
			it.phydef = 4914;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//메탈라인 아머 벨트
		{
			it.id = 59;
			it.name = "메탈라인 아머 벨트";
			it.type = item_belt;
			it.detail = arm_plate;
			it.gainStr = 136;
			it.gainInt = 136;
			it.gainHealth = 140;
			it.gainSpirit = 110;
			it.phydef = 2532;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//메탈라인 아머 신발
		{
			it.id = 61;
			it.name = "메탈라인 아머 신발";
			it.type = item_shoes;
			it.detail = arm_plate;
			it.gainStr = 136;
			it.gainInt = 136;
			it.gainHealth = 140;
			it.gainSpirit = 110;
			it.phydef = 3698;
			it.reqlvl = 5;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
#pragma endregion

#pragma region 소모품
		//블루베리
		{
			it.id = 4;
			it.name = "블루베리";
			it.type = item_consume;
			it.gainHP = 100;
			it.price = 50;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//라미화 잎
		{
			it.id = 7;
			it.name = "라미화 잎";
			it.type = item_consume;
			it.gainMP = 50;
			it.price = 50;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//타코야끼
		{
			it.id = 17;
			it.name = "타코야끼";
			it.type = item_consume;
			it.gainHP = 500;
			it.price = 150;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//샴페인
		{
			it.id = 18;
			it.name = "샴페인";
			it.type = item_consume;
			it.gainMP = 400;
			it.price = 150;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//하트쿠키
		{
			it.id = 24;
			it.name = "하트쿠키";
			it.type = item_consume;
			it.detail = 1;				//퍼센트 단위
			it.gainHP = 50;
			it.price = 500;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//마나에이드
		{
			it.id = 26;
			it.name = "마나에이드";
			it.type = item_consume;
			it.detail = 1;				//퍼센트 단위
			it.gainMP = 50;
			it.price = 500;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
#pragma endregion
}