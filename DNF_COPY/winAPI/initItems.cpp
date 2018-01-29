#include "stdafx.h"
#include "mainGame.h"

void mainGame::initItems()
{
	Item it = Item();

#pragma region ����
		//�⺻���� - �������
		{
			it.id = -1;
			it.name = "�������";
			it.reachx = 140;
			it.reachz = 140;
			it.phydmgmin = 5;
			it.phydmgmax = 10;
			it.magdmgmin = 5;
			it.magdmgmax = 10;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//�����۾���
		{
			it.id = -1;
			it.name = "����";
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//â���Ǳ����� - �Ұ�
		{
			it.id = 139;
			it.name = "â���� ������ - �Ұ�";
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
		//�Ϲݰ�
		{
			it.id = 146;
			it.name = "�Ϲݰ�";
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
		//��Ż���� �Ƹ� ����
		{
			it.id = 66;
			it.name = "��Ż���� �Ƹ� ����";
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
		//��Ż���� �Ƹ� ����
		{
			it.id = 63;
			it.name = "��Ż���� �Ƹ� ����";
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
		//��Ż���� �Ƹ� ���
		{
			it.id = 60;
			it.name = "��Ż���� �Ƹ� ���";
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
		//��Ż���� �Ƹ� ��Ʈ
		{
			it.id = 59;
			it.name = "��Ż���� �Ƹ� ��Ʈ";
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
		//��Ż���� �Ƹ� �Ź�
		{
			it.id = 61;
			it.name = "��Ż���� �Ƹ� �Ź�";
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

#pragma region �Ҹ�ǰ
		//��纣��
		{
			it.id = 4;
			it.name = "��纣��";
			it.type = item_consume;
			it.gainHP = 100;
			it.price = 50;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//���ȭ ��
		{
			it.id = 7;
			it.name = "���ȭ ��";
			it.type = item_consume;
			it.gainMP = 50;
			it.price = 50;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//Ÿ�ھ߳�
		{
			it.id = 17;
			it.name = "Ÿ�ھ߳�";
			it.type = item_consume;
			it.gainHP = 500;
			it.price = 150;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//������
		{
			it.id = 18;
			it.name = "������";
			it.type = item_consume;
			it.gainMP = 400;
			it.price = 150;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//��Ʈ��Ű
		{
			it.id = 24;
			it.name = "��Ʈ��Ű";
			it.type = item_consume;
			it.detail = 1;				//�ۼ�Ʈ ����
			it.gainHP = 50;
			it.price = 500;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
		//�������̵�
		{
			it.id = 26;
			it.name = "�������̵�";
			it.type = item_consume;
			it.detail = 1;				//�ۼ�Ʈ ����
			it.gainMP = 50;
			it.price = 500;
			itemList.insert(make_pair(it.name, it));
			it = Item();
		}
#pragma endregion
}