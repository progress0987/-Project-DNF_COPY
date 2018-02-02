#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	empty = itemList.find("없음")->second;
	emptyWeapon = itemList.find("무기없음")->second;
	Time = onHeal = onHealFrame = bloodframe = 0;
	frame = 176;
	onSuperarmor = onLevelup = levelupTick = levelupEffect = false;
	x = curMap->getWidth() / 2;
	y = 0;
	z = (curMap->getHeight() - 50)*2;
	curStance = stance_idle;
	onDebug = onJump = onSkill = printblood = false;
	ui = new UI;
	ui->init();
	gold = 1000000;
	movebegin = 0;
	setOnCombat(!curMap->isPeaceful());
	Coin = 3;
	deadTick = 9;
	reset = false;

	Weapon = emptyWeapon;
	Armor = Shoulder = Pants = Belt = Boots = Necklece = Ring = Bracelet = empty;

	QSkill = WSkill = ASkill = SSkill = DSkill = FSkill = GSkill = nullptr;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			equipments.push_back(empty);
			consume.push_back(empty);
		}
	}

	rootItem(itemList.find("일반검")->second);
	//rootItem(itemList.find("창성의 구원자 - 소검")->second);
	//rootItem(itemList.find("메탈라인 아머 상의")->second);
	//rootItem(itemList.find("메탈라인 아머 하의")->second);
	//rootItem(itemList.find("메탈라인 아머 어깨")->second);
	//rootItem(itemList.find("메탈라인 아머 벨트")->second);
	//rootItem(itemList.find("메탈라인 아머 신발")->second);

	for (int i = 0; i < 10; i++) {
		rootItem(itemList.find("블루베리")->second);
		rootItem(itemList.find("라미화 잎")->second);
		rootItem(itemList.find("타코야끼")->second);
		rootItem(itemList.find("샴페인")->second);
		rootItem(itemList.find("하트쿠키")->second);
		rootItem(itemList.find("마나에이드")->second);
	}

	q1 = q2 = q3 = q4 = q5 = q6 = empty;
	Weapon = emptyWeapon;
	curSkill = nullptr;
	Stat.level = 1;
	Stat.str = 5;
	Stat.intel = 5;
	Stat.health = 5;
	Stat.spirit = 5;
	Stat.reqEXP = 100;
	Stat.curEXP = 0;
	Stat.a_str = Stat.a_intel = Stat.a_health = Stat.a_spirit = 0;
	Stat.maxHP = Stat.curHP = (Stat.health + Stat.a_health) * 10 + (Stat.str + Stat.a_str) * 5		+500;
	Stat.maxMP = Stat.curMP = (Stat.spirit + Stat.a_spirit) * 10 + (Stat.intel + Stat.a_intel) * 5	+500;
	Stat.phyAtt = (Stat.str + Stat.a_str) * 5;
	Stat.magAtt = (Stat.intel + Stat.a_intel) * 10;

	Stat.phyDef = (Stat.health + Stat.a_health) * 2 + (Stat.str + Stat.a_str);
	Stat.a_phyDef = Armor.phydef + Shoulder.phydef + Belt.phydef + Pants.phydef + Boots.phydef;
	Stat.magDef = (Stat.spirit + Stat.a_spirit) * 10 + (Stat.intel + Stat.a_intel);
	Stat.a_magDef = Armor.magdef + Shoulder.magdef + Belt.magdef + Pants.magdef + Boots.magdef;

	Stat.a_phyAtt = Weapon.phydmgmin;
	Stat.a_magAtt = Weapon.magdmgmin;

	setSkills();
	for (int i = equipments.size(); i < 32; i++) {
		equipments.push_back(empty);
	}

	test = false;
	return S_OK;
}

void player::release(void)
{
	ui->release();
}

void player::update(void)
{
	tick++;
	Time++;
	//살아있을때
	if (Stat.curHP > 0) {
		if (gold < 0)gold = 0;//혹시모를 에러검출용

		if (reset) {
			Stat.curHP = Stat.maxHP;
			deadTick = 9;
			reset = false;
		}
		effectedOnTime atk;
		/////////////////////////////////////////////////////////////////////////////////////////////////////체력/마력 적을때 회복, 회복효과
		{
			if (Stat.curMP < Stat.maxMP) {
				if (tick % 20 == 0) {
					Stat.curMP += 2;
				}
			}
			if (Stat.curHP < Stat.maxHP) {
				if (tick % 20 == 0) {
					Stat.curHP += 3;
				}
			}
			if (Stat.curHP > Stat.maxHP) Stat.curHP = Stat.maxHP;
			if (Stat.curMP > Stat.maxMP) Stat.curMP = Stat.maxMP;

			if (onHeal > 0) {
				if (tick % 5 == 0) {
					onHealFrame++;
					if (onHealFrame > 11) {
						onHealFrame = 0;
						onHeal = 0;
					}
				}
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////상태에 따른 프레임 처리 (공격렉트도 포함)
		switch (curStance) {
		case stance_idle:
			if (tick % 30 == 0) {
				frame++;
				if (frame > 179) {
					frame = 176;
				}
			}
			break;
		case stance_walk:
			if (tick % 15 == 0) {
				frame++;
				if (frame > 187) {
					frame = stance_walk;
				}
			}
			break;
		case stance_run:
			if (tick % 15 == 0) {
				frame++;
				if (frame > 112) {
					frame = stance_run;
				}
			}
			break;
		case stance_ready:
			if (tick % 15 == 0) {
				frame++;
				if (frame > 95) {
					frame = stance_ready;
				}
			}
			break;
		case stance_hit:
			if (tick % 30 == 0) {
				frame++;
				if (frame > 98) {
					curStance = stance_ready;
					frame = stance_ready;
					onHit = true;
				}
			}
			break;
		case stance_sit:
			if (tick % 40 == 0) {
				frame = curMap->isPeaceful() ? stance_idle : stance_ready;
				curStance = curMap->isPeaceful() ? stance_idle : stance_ready;
			}
			break;
		case stance_jump_up:
			if (tick % 30 == 0) {
				frame++;
				if (frame > 127) {
					frame = 127;
				}
			}
			break;
		case stance_jump_down:
			if (tick % 30 == 0) {
				frame++;
				if (frame > 132) {
					frame = 132;
				}
			}
			break;
		case stance_norm_1:
			if (tick % 5 == 0) {
				frame++;

				if (frame == 3 && onAttack) {
					atk.isCrit = rand() % 100 > 80 ? true : false;
					atk.mindmg = (pl->getStatus().str + pl->getStatus().a_str) + pl->getWeapon().phydmgmin;
					atk.maxdmg = (pl->getStatus().str + pl->getStatus().a_str) * 2 + pl->getWeapon().phydmgmax;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = false;
					atk.isAbnormal = false;
					atk.area.miny = -50; atk.area.maxy = 0;
					atk.area.minz = z - Weapon.reachz; atk.area.maxz = z + Weapon.reachz;
					atk.area.maxx = curDir ? x + Weapon.reachx : x + 50;
					atk.area.minx = curDir ? x - 50 : x - Weapon.reachx;
					atk.pushX = curDir ? 3.f : -3.f;
					atk.pushY = 0.f;
					atk.staytime = 10;
					atk.time = Time;
					atk.time = GetTickCount();
					attackQueue.push_back(atk);
					SOUNDMANAGER->play("캐릭_평타_1");
				}
				if (frame > 8) {
					if (nextStance < 0) {
						curStance = stance_ready;
						frame = stance_ready;
					}
					else {
						curStance = nextStance;
						frame = nextStance;
						nextStance = stance_NULL;
					}
				}
			}
			break;
		case stance_norm_2:
			if (tick % 5 == 0) {
				frame++;
				if (frame == 12 && onAttack) {
					atk.isCrit = rand() % 100 > 80 ? true : false;
					atk.mindmg = (Stat.str + Stat.a_str) + Weapon.phydmgmin;
					atk.maxdmg = (Stat.str + Stat.a_str) * 2 + Weapon.phydmgmax;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = false;
					atk.isAbnormal = false;
					atk.area.miny = -50; atk.area.maxy = 0;
					atk.area.minz = z - Weapon.reachz; atk.area.maxz = z + Weapon.reachz;
					atk.area.maxx = curDir ? x + Weapon.reachx : x + 50;
					atk.area.minx = curDir ? x - 50 : x - Weapon.reachx;
					atk.pushX = curDir ? 3.f : -3.f;
					atk.pushY = 0.f;
					atk.staytime = 10;
					atk.time = Time;
					atk.time = GetTickCount();
					attackQueue.push_back(atk);
					SOUNDMANAGER->play("캐릭_평타_2");
				}
				if (frame > 20) {
					if (nextStance < 0) {
						curStance = stance_ready;
						frame = stance_ready;
					}
					else {
						curStance = nextStance;
						frame = nextStance;
						nextStance = stance_NULL;
					}
				}
			}
			break;
		case stance_norm_3:
			if (tick % 5 == 0) {
				frame++;
				if (frame == 35 && onAttack) {
					atk.isCrit = rand() % 100 > 80 ? true : false;
					atk.mindmg = (Stat.str + Stat.a_str) + Weapon.phydmgmin;
					atk.maxdmg = (Stat.str + Stat.a_str) * 2 + Weapon.phydmgmax;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = false;
					atk.isAbnormal = false;
					atk.area.miny = -100; atk.area.maxy = 0;
					atk.area.minz = z - Weapon.reachz / 2; atk.area.maxz = z + Weapon.reachz / 2;
					atk.area.maxx = curDir ? x + Weapon.reachx : x - 10;
					atk.area.minx = curDir ? x + 10 : x - Weapon.reachx;
					atk.pushX = curDir ? 1.f : -1.f;
					atk.pushY = -5.f;												//추후 스킬레벨에따라 띄우기능력변경
					atk.staytime = 10;
					atk.time = Time;
					atk.time = GetTickCount();
					attackQueue.push_back(atk);
					SOUNDMANAGER->play("캐릭_평타_3");
				}
				if (frame > 41) {
					//if (nextStance < 0) {
					curStance = stance_ready;
					frame = stance_ready;
					nextStance = stance_NULL;
					//}
					//else {
					//	curStance = nextStance;
					//	frame = nextStance;
					//}
				}
			}
			break;
		case stance_upper:
			if (tick % 5 == 0) {
				frame++;
				if (frame > 50) {
					//if (nextStance < 0) {
					curStance = stance_ready;
					frame = stance_ready;
					nextStance = stance_NULL;
					onSkill = false;
					//}
					//else {
					//	curStance = nextStance;
					//	frame = nextStance;
					//}
				}
			}
			break;
		case stance_areal_att:
			if (tick % 10 == 0) {
				frame++;

				if (frame == 134 && onAttack) {
					atk.isCrit = rand() % 100 > 80 ? true : false;
					atk.mindmg = (Stat.str + Stat.a_str) + Weapon.phydmgmin;
					atk.maxdmg = (Stat.str + Stat.a_str) * 2 + Weapon.phydmgmax;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = false;
					atk.isAbnormal = false;
					atk.area.miny = y - 100; atk.area.maxy = y + 30;
					atk.area.minz = z - Weapon.reachz / 2; atk.area.maxz = z + Weapon.reachz / 2;
					atk.area.maxx = curDir ? x + Weapon.reachx : x - 10;
					atk.area.minx = curDir ? x + 10 : x - Weapon.reachx;
					atk.pushX = curDir ? 1.f : -1.f;
					atk.pushY = 0;
					atk.staytime = 10;
					atk.time = Time;
					atk.time = GetTickCount();
					attackQueue.push_back(atk);											//추후 스킬레벨에따라 띄우기능력변경
					SOUNDMANAGER->play("캐릭_점프공격");

				}
				if (frame > 137) {
					if (jumpPow > 0) {
						curStance = stance_jump_down;
					}
					else {
						curStance = stance_jump_up;
					}
					nextStance = stance_NULL;
					//frame = stance_jump_down -1;
				}
			}
			break;
		case stance_onSkill:
			//스킬로부터 프레임을 받아와야한다.

			if (!curSkill->oncast) { curStance = stance_ready; frame = stance_ready; curSkill = nullptr; }
			else { frame = curSkill->getCurAction(); }
			break;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////골드 위에 서 있으면 자동획득
		if (curMap->aboveItem(x, z) == 2) {
			DropItemStruct t = curMap->rootItem(x, z);
			gold += t.goldamount;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////대미지 입는지 아니면 시간이 이미 지난 공격 렉트인지 확인
		if (Stat.curHP > 0 && onHit) {
			for (list<effectedOnTime>::iterator i = hitQueue.begin(); i != hitQueue.end(); i++) {
				if (i->area.minx < x&&x < i->area.maxx&&
					i->area.miny < y&&y <= i->area.maxy&&
					i->area.minz < z&&z < i->area.maxz) {
					hitcount = 500;
					int hitdmg = RND->getFromIntTo(i->mindmg, i->maxdmg) - (Stat.phyDef + Stat.a_phyDef);
					if (hitdmg <= 0) hitdmg = 1;
					Stat.curHP -= hitdmg;
					HitQueue hit;
					hit.dmg = hitdmg;
					hit.isCrit = i->isCrit;
					hit.time = GetTickCount();
					hit.x = x;
					hit.y = y + translate(z) - 120;//머리위쪽으로 출력하기위함
					dmgShow.push_back(hit);
					onHit = false;
					printblood = true;
					SOUNDMANAGER->play("캐릭_타격");


					if (!onSuperarmor) {
						curStance = stance_hit;
						frame = stance_hit;
					}
					if (Stat.curHP <= 0) {///////////////////////////////////////////////////////////////////사망 프로세스!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						frame = 103;
						SOUNDMANAGER->play("캐릭_사망");
					}
				}
			}
		}
		for (list<effectedOnTime>::iterator i = hitQueue.begin(); i != hitQueue.end();) {
			if (i->time + i->staytime < GetTickCount()) i = hitQueue.erase(i);
			else i++;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////무적시간처리
		if (hitcount > 0 && onHit == false) {
			hitcount -= 2;
			if (hitcount <= 0) {
				onHit = true;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////슈퍼아머 처리(나중에 슈퍼아머중에 맞아도 스킬 안풀리게)
		if (skill_wavespin->finished&&skill_releasewave->finished && onSuperarmor) {
			onSuperarmor = false;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력부분
		{
			if ((KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isOnceKeyDown(VK_DOWN)) && (curStance == stance_idle || curStance == stance_ready)) {
				if (GetTickCount() - movebegin < 400 && curMap->isRunnable()) {
					curStance = stance_run;
					movestatus = 2;
					frame = 105;
				}
				if (curStance == stance_idle || curStance == stance_ready) {
					curStance = stance_walk;
					movestatus = 1;
					movebegin = GetTickCount();
					frame = 180;
				}
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
				if (curStance == stance_walk || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att || curStance == stance_idle) && movestatus == 1)) {
					if (curStance == stance_idle) curStance = stance_walk;
					x += 2;
				}
				else if (curStance == stance_run || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att) && movestatus == 2)) {
					x += 3;
				}
				else if (curStance == stance_norm_1 || curStance == stance_norm_2 || curStance == stance_upper) {
					x += 1;
				}
				if (curStance == stance_walk || curStance == stance_idle || curStance == stance_run || curStance == stance_ready)
					curDir = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
				if (curStance == stance_walk || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att || curStance == stance_idle) && movestatus == 1)) {
					if (curStance == stance_idle)  curStance = stance_walk;
					x -= 2;
				}
				else if (curStance == stance_run || ((curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att) && movestatus == 2)) {
					x -= 3;
				}
				else if (curStance == stance_norm_1 || curStance == stance_norm_2 || curStance == stance_upper) {
					x -= 1;
				}
				if (curStance == stance_walk || curStance == stance_idle || curStance == stance_run || curStance == stance_ready)
					curDir = false;
			}
			if (KEYMANAGER->isStayKeyDown(VK_UP)) {
				if (curStance == stance_walk || curStance == stance_run || curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att)
					z -= 3;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
				if (curStance == stance_walk || curStance == stance_run || curStance == stance_jump_up || curStance == stance_jump_down || curStance == stance_areal_att)
					z += 3;
			}
			if ((!KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_UP) && !KEYMANAGER->isStayKeyDown(VK_DOWN)) && (curStance == stance_walk || curStance == stance_run)) {
				if (!curMap->isPeaceful()) {
					curStance = stance_ready;
					frame = 90;
				}
				else {
					curStance = stance_idle;
					frame = 176;
				}
				movestatus = 0;
			}


			if (KEYMANAGER->isOnceKeyDown('X')) {
				if (y==0&&curMap->aboveItem(x, z)) {
					frame = stance_sit;
					curStance = stance_sit;
					DropItemStruct it = curMap->rootItem(x, z);
					rootItem(it.item);
					SOUNDMANAGER->play("UI_아이템획득");
				}
				else if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'X';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('Z')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'Z';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('A')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'A';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('S')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'S';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('D')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'D';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('F')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'F';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('G')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'G';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('Q')) {
				if (curMap->isAttackable()) {
					inputStruct t;
					t.key = 'Q';
					t.time = GetTickCount();
					inputQueue.push_back(t);
				}
			}
			if (KEYMANAGER->isOnceKeyDown('C')) {
				if (curMap->isRunnable()) {
					if (curStance == stance_walk || curStance == stance_run || curStance == stance_idle || curStance == stance_ready) {
						curStance = stance_jump_up;
						frame = 125;
						onJump = true;
						jumpPow = -4.5f;
					}
				}
			}

			if (KEYMANAGER->isOnceKeyDown('I')) {
				ui->setCurActiveTab();
				ui->showinv();

			}
			if (KEYMANAGER->isOnceKeyDown('P')) {
				ui->showstat();
			}
			if (KEYMANAGER->isOnceKeyDown('1')) {
				useItem(-1, 1, -1);
			}
			if (KEYMANAGER->isOnceKeyDown('2')) {
				useItem(-1, 2, -1);
			}
			if (KEYMANAGER->isOnceKeyDown('3')) {
				useItem(-1, 3, -1);
			}
			if (KEYMANAGER->isOnceKeyDown('4')) {
				useItem(-1, 4, -1);
			}
			if (KEYMANAGER->isOnceKeyDown('5')) {
				useItem(-1, 5, -1);
			}
			if (KEYMANAGER->isOnceKeyDown('6')) {
				useItem(-1, 6, -1);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
				//onDebug = !onDebug;
				//levelupEffect = true;
				//onLevelup = true;

				rootItem(itemList.find("창성의 구원자 - 소검")->second);
				rootItem(itemList.find("메탈라인 아머 상의")->second);
				rootItem(itemList.find("메탈라인 아머 하의")->second);
				rootItem(itemList.find("메탈라인 아머 어깨")->second);
				rootItem(itemList.find("메탈라인 아머 벨트")->second);
				rootItem(itemList.find("메탈라인 아머 신발")->second);
			}
			//if (KEYMANAGER->isOnceKeyDown('V')) {
			//	test = !test;
			//}
			//if (test) {
			//	if (GetTickCount() % 100 == 0) {
			//		inputStruct t;
			//		t.key = 'Z';
			//		t.time = GetTickCount();
			//		inputQueue.push_back(t);
			//	}
			//}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////키보드 입력 처리부분(공격 및 모션처리)
		if (inputQueue.size() > 0) {
			if (inputQueue.front().time + KEYDELAY > GetTickCount()) {
				if (inputQueue.front().key == 'X') {
					if ((curStance == stance_idle || curStance == stance_ready || curStance == stance_walk) && curMap->isAttackable()) {
						onAttack = true;
						curStance = stance_norm_1;
						frame = stance_norm_1;
						nextStance = stance_NULL;
						inputQueue.pop_front();
					}
					else if (curStance == stance_norm_1) {
						nextStance = stance_norm_2;
						inputQueue.pop_front();
					}
					else if (curStance == stance_norm_2) {
						nextStance = stance_norm_3;
						inputQueue.pop_front();
					}
					else if (curStance == stance_jump_up || curStance == stance_jump_down) {
						curStance = stance_areal_att;
						frame = stance_areal_att;
						inputQueue.pop_front();
					}
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'Z'&&curStance != stance_onSkill && !onJump && !skill_upper->onCooldown) {
					if (Stat.curMP >= skill_upper->reqMana) {
						curStance = stance_onSkill;
						curSkill = skill_upper;
						skill_upper->cast(x, y, z);
						Stat.curMP -= skill_upper->reqMana;
					}else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'A'&&curStance != stance_onSkill && !onJump && !ASkill->onCooldown) {
					if (Stat.curMP >= ASkill->reqMana) {
						curStance = stance_onSkill;
						curSkill = ASkill;
						ASkill->cast(x, y, z);
						Stat.curMP -= ASkill->reqMana;
					}
					else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'S'&&curStance != stance_onSkill && !onJump && !SSkill->onCooldown) {
					if (Stat.curMP >= SSkill->reqMana) {
						curStance = stance_onSkill;
						curSkill = SSkill;
						SSkill->cast(x, y, z);
						Stat.curMP -= SSkill->reqMana;
					}
					else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'D'&&curStance != stance_onSkill && !onJump && !DSkill->onCooldown) {
					if (Stat.curMP >= DSkill->reqMana) {
						curStance = stance_onSkill;
						curSkill = DSkill;
						DSkill->cast(x, y, z);
						Stat.curMP -= DSkill->reqMana;
					}
					else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'F'&&curStance != stance_onSkill && !onJump && !FSkill->onCooldown) {
					if (Stat.curMP >= FSkill->reqMana) {
						curStance = stance_onSkill;
						curSkill = FSkill;
						FSkill->cast(x, y, z);
						Stat.curMP -= FSkill->reqMana;
					}
					else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'G'&&curStance != stance_onSkill && !onJump && !GSkill->onCooldown) {
					if (Stat.curMP >= GSkill->reqMana) {
						curStance = stance_onSkill;
						curSkill = GSkill;
						GSkill->cast(x, y, z);
						Stat.curMP -= GSkill->reqMana;
						onSuperarmor = true;
					}
					else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
				if (inputQueue.size() > 0 && inputQueue.front().key == 'Q'&&curStance != stance_onSkill && !onJump && !QSkill->onCooldown) {
					if (Stat.curMP >= QSkill->reqMana) {
						curStance = stance_onSkill;
						curSkill = QSkill;
						QSkill->cast(x, y, z);
						Stat.curMP -= QSkill->reqMana;
						onSuperarmor = true;
					}
					else SOUNDMANAGER->play("캐릭_스킬_쿨타임");
					inputQueue.pop_front();
				}
			}
			else {
				inputQueue.pop_front();
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////점프처리부분
		{
			if (onJump) {
				jumpPow += 0.07f;
				y += jumpPow;
			}
			if (curStance == stance_jump_up) {
				if (jumpPow > 0) {
					frame = 127;
					curStance = stance_jump_down;
				}
			}
			if (curStance == stance_jump_down) {
				if (y > 0) {
					y = 0;
					onJump = false;
					if (curMap->isPeaceful()) {
						curStance = stance_idle;
						frame = 176;
						if (movestatus == 1) {
							curStance = stance_walk;
							frame = 180;
						}
						else if (movestatus == 2) {
							curStance = stance_run;
							frame = 105;
						}
					}
					else {
						curStance = stance_ready;
						frame = 90;
						if (movestatus == 1) {
							curStance = stance_walk;
							frame = 180;
						}
						else if (movestatus == 2) {
							curStance = stance_run;
							frame = 105;
						}
					}
				}
			}
			if (curStance == stance_areal_att) {
				if (y > 0) {
					y = 0;
					onJump = false;
					if (curMap->isPeaceful()) {
						curStance = stance_idle;
						frame = 176;
						if (movestatus == 1) {
							curStance = stance_walk;
							frame = 180;
						}
						else if (movestatus == 2) {
							curStance = stance_run;
							frame = 105;
						}
					}
					else {
						curStance = stance_ready;
						frame = 90;
						if (movestatus == 1) {
							curStance = stance_walk;
							frame = 180;
						}
						else if (movestatus == 2) {
							curStance = stance_run;
							frame = 105;
						}
					}
				}
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////플레이어 레벨업 출력
		if (levelupEffect) {
			if (tick % 10 == 0) {
				levelupTick++;
				if (levelupTick == 1) {
					effectedOnTime atk;
					atk.isCrit = false;
					atk.mindmg = 0;
					atk.maxdmg = 0;
					atk.isOnetime = true;
					atk.isProjectile = false;
					atk.isHold = false;
					atk.area.miny = -300; atk.area.maxy = 0;
					atk.area.minz = z - 800; atk.area.maxz = z + 800;
					atk.area.maxx = x + 400;
					atk.area.minx = x;
					atk.pushX = 5.f;
					atk.pushY = -6.f;												//추후 스킬레벨에따라 띄우기능력변경
					atk.staytime = 10;
					atk.time = GetTickCount();
					attackQueue.push_back(atk);
					atk.area.maxx = x;
					atk.area.minx = x - 400;
					atk.pushX = -5.f;
					atk.time = GetTickCount();
					attackQueue.push_back(atk);
				}
				if (levelupTick > 14) {
					levelupEffect = false;
					onLevelup = false;
					levelupTick = 0;
				}
			}
		}

		//	conNode* Node;
		//	Node = nullptr;
		//	if(curMap->getMove(Node,x,z)){		//이동
		//#pragma region rect의 타입 ==0, 이동 설정부분
		//	setCurScene(Node->nextNode,Node->x,Node->z);//이동부분 중요!
		//#pragma endregion nextmap 과 nextpos로 다음에 이동했을때의 좌표를 결정. 이거 아마 메인게임에서 해야할거임 maingame에 init부분 확인,
		//	}

		/////////////////////////////////////////////////////////////////////////////////////////////////////UI 업데이트
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////사망시
	else {
		if (reset) {
			Stat.curHP = Stat.maxHP;
			deadTick = 9;
			reset = false;
		}
		if (Coin > 0) {
			if (KEYMANAGER->isOnceKeyDown('X')) {
				Coin--;
				Stat.curHP = Stat.maxHP;
				deadTick = 9;
				levelupEffect = true;
				reset = false;
				SOUNDMANAGER->play("UI_이어하기");
			}
		}
		if (tick % 200 == 0) {
			deadTick--;
			if (deadTick < 0) {
				deadTick = 0;
				reset = true;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////대미지 이미지 처리
	for (list<HitQueue>::iterator i = dmgShow.begin(); i != dmgShow.end();) {
		DWORD now = GetTickCount();
		if (now < i->time + 300) {////////////////////////// 맞아서 300ms까지는 위로올라감
			i->y -= (1.f / 2.f);
		}
		else if (i->time + 300 < now&&now < i->time + 600) {
			i->y -= (1.f / 500.f);
		}
		else if (i->time + 600 < now&&now < i->time + 900) {
			i->y -= (1.f / 2.f);
		}
		else if (i->time + 900 < now) {
			i = dmgShow.erase(i);
			continue;
		}
		i++;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////각 스킬들 업데이트
	updateSkills();
	/////////////////////////////////////////////////////////////////////////////////////////////////////지속시간이 끝난 대미지렉트 제거
	for (list<effectedOnTime>::iterator i = attackQueue.begin(); i != attackQueue.end();) {
		if (i->time + i->staytime < GetTickCount())i = attackQueue.erase(i);
		else { i++; }
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////위치보정,충돌
	{
		//플레이어  지형충돌렉트 생성
		terColRect = RectMakeCenter(x, translate(z), 50, 30);
		RECT t;
		vector<MapTile> curMapTiles = curMap->getTiles();
		for (vector<MapTile>::iterator i = curMapTiles.begin(); i != curMapTiles.end(); i++) {
			if (IntersectRect(&t, &i->rc, &terColRect)) {
				if (i->type == -1) {
					int width = t.right - t.left;
					int height = t.bottom - t.top;
					if (width < height) {//x먼저
						if (t.right == i->rc.right&& terColRect.right > i->rc.right) {
							x = i->rc.right + 25;
						}
						else if (t.left == i->rc.left && terColRect.left < i->rc.left) {
							x = i->rc.left - 25;
						}
					}
					else { // z먼저
						if (t.top == i->rc.top && terColRect.top < i->rc.top) {
							z = (i->rc.top - 15) * 2;
						}
						if (t.bottom == i->rc.bottom && terColRect.bottom > i->rc.bottom) {
							z = (i->rc.bottom + 15) * 2;
						}
					}
				}
			}
		}
		if (x + 25 > curMap->getWidth()) x = curMap->getWidth() - 25;
		if (x - 25 < 0) x = 25;
		if (translate(z) + 15 > curMap->getHeight()) z = (curMap->getHeight() - 15) * 2;
		if (translate(z) - 15 < 0) z = (15) * 2;
		terColRect = RectMakeCenter(x, translate(z), 50, 30);
		if (y > 0) {
			y = 0;
			jumpPow = 0;
			onJump = false;
		}
		if (printblood) {
			bloodframe++;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////카메라 처리 부분
	{
		cam.x = x - WINSIZEX / 2;
		cam.y = translate(z) - WINSIZEY / 2;
		if (cam.x + WINSIZEX > curMap->getWidth()) cam.x = curMap->getWidth() - WINSIZEX;
		if (cam.x < 0)cam.x = 0;
		if (cam.y + WINSIZEY > curMap->getHeight()) cam.y = curMap->getHeight() - WINSIZEY;
		if (cam.y < 0) cam.y = 0;
	}
	ui->update();
	/////////////////////////////////////////////////////////////////////////////////////////////////////테스트중
	bool test2;
	if (SOUNDMANAGER->isPlaySound("효과_결과출력")) { 
		test = true;
	}
	if (!SOUNDMANAGER->isPlaySound("효과_결과출력")) {
		test = false;
	}
	if (!test) {
		test2 = false;
	}
}

void player::render(void)
{
	char tmp[50];
	if (levelupEffect) {
		sprintf(tmp, "레벨업_%d", levelupTick);
		IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x+20, translate(z) - cam.y, 401, 524);
	}
	if (onLevelup) {
		IMAGEMANAGER->findImage("레벨업")->DFpointrender(x - cam.x, translate(z) - cam.y - 120 - levelupTick * 5, 138, 30,1.f,255 - 8*levelupTick);
	}
	printSkillb();
	IMAGEMANAGER->findImage("그림자")->DFpointrender(x - cam.x, translate(z) - cam.y, 300, 50, 0.3f, 0xAA);
	sprintf(tmp, "%s_뒤_%d",Weapon.name.c_str(), frame);
	if (Weapon.id == -1) {
		sprintf(tmp, "빈손뒤_%d", frame);
	}
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);

	sprintf(tmp, "캐릭터_%d", frame);
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);
	
	sprintf(tmp, "%s_앞_%d",Weapon.name.c_str(), frame);
	if (Weapon.id == -1) {
		sprintf(tmp, "빈손앞_%d", frame);
	}
	IMAGEMANAGER->findImage(tmp)->DFcharpointrender(x - cam.x, (y + translate(z)) - cam.y, curDir);

	if (onHeal > 0) {
		switch (onHeal) {
		case 1:
			sprintf(tmp, "체력회복_%d", onHealFrame);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y - 100,240,160);
			break;
		case 2:
			sprintf(tmp, "마나회복_%d", onHealFrame);
			IMAGEMANAGER->findImage(tmp)->DFpointrender(x - cam.x, (y + translate(z)) - cam.y - 100,240,160);
			break;
		case 3:
			break;
		}
	}
	if (printblood) {
		char tmp[50];
		if (bloodframe / 4 > 6) {
			bloodframe = 0;
			printblood = false;
		}
		sprintf(tmp, "혈흔_%d", bloodframe / 4);
		IMAGEMANAGER->findImage(tmp)->render(x - 50 - cam.x, (y + translate(z) - 80) - cam.y);
	}
	for (list<HitQueue>::iterator i = dmgShow.begin(); i != dmgShow.end(); i++) {
		printNumber(*i);
	}
	printSkillf();
	if (Stat.curHP <= 0) {
		sprintf(tmp, "카운트다운_%d",deadTick);
		int coinw = IMAGEMANAGER->findImage("코인잔여")->getWidth();
		int coinh = IMAGEMANAGER->findImage("코인잔여")->getHeight();
		IMAGEMANAGER->findImage(tmp)->DFpointrender(WINSIZEX/2, WINSIZEY/2-50,IMAGEMANAGER->findImage(tmp)->getWidth(),88);
		IMAGEMANAGER->findImage("코인잔여")->render(WINSIZEX / 2 - coinw / 2, WINSIZEY / 2 - coinh / 2);
		sprintf(tmp, "코인카운트_%d", Coin % 100 / 10);
		IMAGEMANAGER->findImage(tmp)->render(WINSIZEX / 2 - coinw / 2 + 125, WINSIZEY / 2 - coinh / 2 + 50);
		sprintf(tmp, "코인카운트_%d", Coin % 10);
		IMAGEMANAGER->findImage(tmp)->render(WINSIZEX / 2 - coinw / 2 + 140, WINSIZEY / 2 - coinh / 2 + 50);
	}
}

void player::renderdc(void)
{
	//Rectangle(hdc, terColRect.left -cam.x, terColRect.top -cam.y, terColRect.right -cam.x, terColRect.bottom-cam.y);
	char t[100];
	sprintf(t, "x : %f y : %f z : %f z/2 : %f", x, y, z,z/2);
	TextOut(hdc, 50, 100, t, strlen(t));

	//POINT tmp;
	//tmp.x = ptMouse.x + cam.x;
	//tmp.y = ptMouse.y + cam.y;
	sprintf(t, "x : %d y : %d", ptMouse.x+(int)cam.x, ptMouse.y+(int)cam.y);
	TextOut(hdc, 50, 150, t, strlen(t));
	//sprintf(t, "queuesize : %d", inputQueue.size());
	//TextOut(hdc, 50, 200, t, strlen(t));

	//대미지 렉트 그려주기
	//for (list<effectedOnTime>::iterator i = attackQueue.begin(); i != attackQueue.end(); i++) {
	//	Rectangle(hdc, i->area.minx - cam.x, translate(i->area.minz)+y - cam.y, i->area.maxx -cam.x, translate(i->area.maxz)+y - cam.y);
	//}
	ui->renderdc();

}

void player::gainEXP(int amount)
{
	Stat.curEXP += amount;
	if (Stat.curEXP >= Stat.reqEXP) {
		Stat.level++;
		Stat.str    += 10;
		Stat.intel  += 10;
		Stat.health += 10;
		Stat.spirit += 10;
		Stat.curEXP = Stat.curEXP%Stat.reqEXP;
		Stat.reqEXP *= 1.5;

		Stat.a_str = Weapon.gainStr + Armor.gainStr + Shoulder.gainStr + Belt.gainStr + Pants.gainStr + Boots.gainStr;
		Stat.a_intel = Weapon.gainInt + Armor.gainInt + Shoulder.gainInt + Belt.gainInt + Pants.gainInt + Boots.gainInt;
		Stat.a_health = Weapon.gainHealth + Armor.gainHealth + Shoulder.gainHealth + Belt.gainHealth + Pants.gainHealth + Boots.gainHealth;
		Stat.a_spirit = Weapon.gainSpirit + Armor.gainSpirit + Shoulder.gainSpirit + Belt.gainSpirit + Pants.gainSpirit + Boots.gainSpirit;


		Stat.maxHP = Stat.curHP = (Stat.health + Stat.a_health) * 10 + (Stat.str + Stat.a_str) * 5 + 500;
		Stat.maxMP = Stat.curMP = (Stat.spirit + Stat.a_spirit) * 10 + (Stat.intel + Stat.a_intel) * 5 + 500;
		Stat.phyAtt = (Stat.str + Stat.a_str) * 5;
		Stat.magAtt = (Stat.intel + Stat.a_intel) * 10;

		Stat.phyDef = (Stat.health + Stat.a_health) * 2 + (Stat.str + Stat.a_str);
		Stat.a_phyDef = Armor.phydef + Shoulder.phydef + Belt.phydef + Pants.phydef + Boots.phydef;
		Stat.magDef = (Stat.spirit + Stat.a_spirit) * 10 + (Stat.intel + Stat.a_intel);
		Stat.a_magDef = Armor.magdef + Shoulder.magdef + Belt.magdef + Pants.magdef + Boots.magdef;

		Stat.a_phyAtt = Weapon.phydmgmin;
		Stat.a_magAtt = Weapon.magdmgmin;
		levelupEffect = true;
		onLevelup = true;
		SOUNDMANAGER->play("UI_레벨업");
	}
}

void player::resetPlayer()
{
	setOnCombat(false);
	Stat.curHP = Stat.maxHP;
	deadTick = 9;
	reset = false;
}

void player::setCurScene(MapBase * map, FLOAT x, FLOAT z)
{
	if (map->getCurMap() != NULL) {
		curMap = map->getCurMap();
	}
	else {
		curMap = map;
	}
	this->x = x;
	this->y = 0;
	this->z = z;
}

void player::setOnCombat(bool oncombat)
{
	if (oncombat) {
		curStance = stance_ready;
		frame = 90;
	}
	else {
		curStance = stance_idle;
		frame = 176;
	}
}

void player::setSkills()
{
	skill_upper = new upper;
	skill_upper->init();
	skills.push_back(skill_upper);

	skill_wave = new wave;
	skill_wave->init();
	skills.push_back(skill_wave);
	ASkill = skill_wave;

	skill_icewave = new icewave;
	skill_icewave->init();
	skills.push_back(skill_icewave);
	SSkill = skill_icewave;

	skill_firewave = new firewave;
	skill_firewave->init();
	skills.push_back(skill_firewave);
	DSkill = skill_firewave;

	skill_vacslash = new vacslash;
	skill_vacslash->init();
	skills.push_back(skill_vacslash);
	FSkill = skill_vacslash;

	skill_releasewave = new releasewave;
	skill_releasewave->init();
	skills.push_back(skill_releasewave);
	QSkill = skill_releasewave;
	
	skill_wavespin = new wavespin;
	skill_wavespin->init();
	skills.push_back(skill_wavespin);
	GSkill = skill_wavespin;
}

void player::updateSkills()
{
	for (vector<Skill*>::iterator i = skills.begin(); i != skills.end(); i++)
	{
		(*i)->update();
	}
}

void player::printSkillb()
{
	for (vector<Skill*>::iterator i = skills.begin(); i != skills.end(); i++)
	{
		(*i)->renderb();
	}
}

void player::printSkillf()
{
	for (vector<Skill*>::iterator i = skills.begin(); i != skills.end(); i++)
	{
		(*i)->renderf();
	}
}

void player::hitDmg(int amount)
{
	Stat.curHP -= amount;
}

void player::useItem(int tab, int x, int y)
{
	int index = y * 8 + x;
	int amount;
	switch (tab) {
	case -1:						//퀵슬롯에서 사용
		switch (x) {				//몇번째 슬롯인지
		case 1:
			if (q1.id > 0) {
				switch (q1.detail) {
				case 1:											//퍼센트단위로 체력회복시키는거
					amount = (Stat.maxHP * ((float)q1.gainHP / 100.f));
					Stat.curHP += amount;
					amount = (Stat.maxMP * ((float)q1.gainMP / 100.f));
					Stat.curMP += amount;
					break;
				default:										//수치로 체력회복
					Stat.curHP += q1.gainHP;
					Stat.curMP += q1.gainMP;
					break;
				}
				onHeal = q1.gainHP > 0 ? (q1.gainMP > 0 ? 3 : 1) : (q1.gainMP > 0 ? 2 : 0);
				q1.stack--;
				if (q1.stack <= 0) {
					q1 = empty;
				}
			}
			break;
		case 2:
			if (q2.id > 0) {
				switch (q2.detail) {
				case 1:											//퍼센트단위로 체력회복시키는거
					amount = (Stat.maxHP * ((float)q2.gainHP / 100.f));
					Stat.curHP += amount;
					amount = (Stat.maxMP * ((float)q2.gainMP / 100.f));
					Stat.curMP += amount;
					break;
				default:										//수치로 체력회복
					Stat.curHP += q2.gainHP;
					Stat.curMP += q2.gainMP;
					break;
				}
				onHeal = q2.gainHP > 0 ? (q2.gainMP > 0 ? 3 : 1) : (q2.gainMP > 0 ? 2 : 0);
				q2.stack--;
				if (q2.stack <= 0) {
					q2 = empty;
				}
			}
			break;
		case 3:
			if (q3.id > 0) {
				switch (q3.detail) {
				case 1:											//퍼센트단위로 체력회복시키는거
					amount = (Stat.maxHP * ((float)q3.gainHP / 100.f));
					Stat.curHP += amount;
					amount = (Stat.maxMP * ((float)q3.gainMP / 100.f));
					Stat.curMP += amount;
					break;
				default:										//수치로 체력회복
					Stat.curHP += q3.gainHP;
					Stat.curMP += q3.gainMP;
					break;
				}
				onHeal = q3.gainHP > 0 ? (q3.gainMP > 0 ? 3 : 1) : (q3.gainMP > 0 ? 2 : 0);
				q3.stack--;
				if (q3.stack <= 0) {
					q3 = empty;
				}
			}
			break;
		case 4:
			if (q4.id > 0) {
				switch (q4.detail) {
				case 1:											//퍼센트단위로 체력회복시키는거
					amount = (Stat.maxHP * ((float)q4.gainHP / 100.f));
					Stat.curHP += amount;
					amount = (Stat.maxMP * ((float)q4.gainMP / 100.f));
					Stat.curMP += amount;
					break;
				default:										//수치로 체력회복
					Stat.curHP += q4.gainHP;
					Stat.curMP += q4.gainMP;
					break;
				}
				onHeal = q4.gainHP > 0 ? (q4.gainMP > 0 ? 3 : 1) : (q4.gainMP > 0 ? 2 : 0);
				q4.stack--;
				if (q4.stack <= 0) {
					q4 = empty;
				}
			}
			break;
		case 5:
			if (q5.id > 0) {
				switch (q5.detail) {
				case 1:											//퍼센트단위로 체력회복시키는거
					amount = (Stat.maxHP * ((float)q5.gainHP / 100.f));
					Stat.curHP += amount;
					amount = (Stat.maxMP * ((float)q5.gainMP / 100.f));
					Stat.curMP += amount;
					break;
				default:										//수치로 체력회복
					Stat.curHP += q5.gainHP;
					Stat.curMP += q5.gainMP;
					break;
				}
				onHeal = q5.gainHP > 0 ? (q5.gainMP > 0 ? 3 : 1) : (q5.gainMP > 0 ? 2 : 0);
				q5.stack--;
				if (q5.stack <= 0) {
					q5 = empty;
				}
			}
			break;
		case 6:
			if (q6.id > 0) {
				switch (q6.detail) {
				case 1:											//퍼센트단위로 체력회복시키는거
					amount = (Stat.maxHP * ((float)q6.gainHP / 100.f));
					Stat.curHP += amount;
					amount = (Stat.maxMP * ((float)q6.gainMP / 100.f));
					Stat.curMP += amount;
					break;
				default:										//수치로 체력회복
					Stat.curHP += q6.gainHP;
					Stat.curMP += q6.gainMP;
					break;
				}
				onHeal = q6.gainHP > 0 ? (q6.gainMP > 0 ? 3 : 1) : (q6.gainMP > 0 ? 2 : 0);
				q6.stack--;
				if (q6.stack <= 0) {
					q6 = empty;
				}
			}
			break;
		}
		break;
	case 0:
		switch (equipments[index].type) {
		case item_weapon:
			if (Weapon.name == "무기없음") {
				equipments[y * 8 + x].equipped = true;
				Weapon = equipments[y * 8 + x];
				equipments[y * 8 + x] = empty;
			}
			else {
				Weapon.equipped = false;
				Item t = Weapon;
				equipments[y * 8 + x].equipped = true;
				Weapon = equipments[y * 8 + x];
				equipments[y * 8 + x] = t;
			}
			break;
		case item_coat:
			if (Armor.name == "없음") {
				equipments[y * 8 + x].equipped = true;
				Armor = equipments[y * 8 + x];
				equipments[y * 8 + x] = empty;
			}
			else {
				Armor.equipped = false;
				Item t = Armor;
				equipments[y * 8 + x].equipped = true;
				Armor = equipments[y * 8 + x];
				equipments[y * 8 + x] = t;
			}
			break;
		case item_shoulder:
			if (Shoulder.name == "없음") {
				equipments[y * 8 + x].equipped = true;
				Shoulder = equipments[y * 8 + x];
				equipments[y * 8 + x] = empty;
			}
			else {
				Shoulder.equipped = false;
				Item t = Shoulder;
				equipments[y * 8 + x].equipped = true;
				Shoulder = equipments[y * 8 + x];
				equipments[y * 8 + x] = t;
			}
			break;
		case item_belt:
			if (Belt.name == "없음") {
				equipments[y * 8 + x].equipped = true;
				Belt = equipments[y * 8 + x];
				equipments[y * 8 + x] = empty;
			}
			else {
				Belt.equipped = false;
				Item t = Belt;
				equipments[y * 8 + x].equipped = true;
				Belt = equipments[y * 8 + x];
				equipments[y * 8 + x] = t;
			}
			break;
		case item_pants:
			if (Pants.name == "없음") {
				equipments[y * 8 + x].equipped = true;
				Pants = equipments[y * 8 + x];
				equipments[y * 8 + x] = empty;
			}
			else {
				Pants.equipped = false;
				Item t = Pants;
				equipments[y * 8 + x].equipped = true;
				Pants = equipments[y * 8 + x];
				equipments[y * 8 + x] = t;
			}
			break;
		case item_shoes:
			if (Boots.name == "없음") {
				equipments[y * 8 + x].equipped = true;
				Boots = equipments[y * 8 + x];
				equipments[y * 8 + x] = empty;
			}
			else {
				Boots.equipped = false;
				Item t = Boots;
				equipments[y * 8 + x].equipped = true;
				Boots = equipments[y * 8 + x];
				equipments[y * 8 + x] = t;
			}
			break;
		}
		break;
	case 1:
		switch (consume[index].detail) {
		case 1:											//퍼센트단위로 체력회복시키는거
			amount = (Stat.maxHP * ((float)consume[index].gainHP / 100.f));
			Stat.curHP += amount;
			if(consume[index].gainHP>0)SOUNDMANAGER->play("체력회복");
			amount = (Stat.maxMP * ((float)consume[index].gainMP / 100.f));
			Stat.curMP += amount;
			if(consume[index].gainMP>0)SOUNDMANAGER->play("마나회복");
			onHeal = consume[index].gainHP > 0 ? (consume[index].gainMP > 0 ? 3 : 1) : (consume[index].gainMP > 0 ? 2 : 0);
			consume[index].stack--;
			if (consume[index].stack <= 0) {
				consume[index] = empty;
			}
			break;
		default:										//수치로 체력회복
			Stat.curHP +=consume[index].gainHP;
			if(consume[index].gainHP>0)SOUNDMANAGER->play("체력회복");
			Stat.curMP +=consume[index].gainMP;
			if(consume[index].gainMP>0)SOUNDMANAGER->play("마나회복");
			onHeal = consume[index].gainHP > 0 ? (consume[index].gainMP > 0 ? 3 : 1) : (consume[index].gainMP > 0 ? 2 : 0);
			consume[index].stack--;
			if (consume[index].stack <= 0) {
				consume[index] = empty;
			}
			break;
		}
		break;
	default:
		break;
	}


	Stat.a_str		= Weapon. gainStr	+ Armor. gainStr	+ Shoulder.gainStr		+ Belt.gainStr		+ Pants. gainStr	+ Boots.gainStr	;
	Stat.a_intel	= Weapon. gainInt	+ Armor. gainInt	+ Shoulder.gainInt		+ Belt.gainInt		+ Pants. gainInt	+ Boots.gainInt	;
	Stat.a_health	= Weapon. gainHealth+ Armor. gainHealth	+ Shoulder.gainHealth	+ Belt.gainHealth	+ Pants. gainHealth	+ Boots.gainHealth;
	Stat.a_spirit	= Weapon. gainSpirit+ Armor. gainSpirit	+ Shoulder.gainSpirit	+ Belt.gainSpirit	+ Pants. gainSpirit	+ Boots.gainSpirit;

	Stat.maxHP = (Stat.health + Stat.a_health) * 10 + (Stat.str + Stat.a_str) * 5		+500;
	Stat.maxMP = (Stat.spirit + Stat.a_spirit) * 10 + (Stat.intel + Stat.a_intel) * 5	+500;
	if (curMap->isPeaceful()) {
		Stat.curHP = Stat.maxHP;
		Stat.curMP = Stat.maxMP;
	}
	Stat.phyAtt = (Stat.str + Stat.a_str) * 5;
	Stat.magAtt = (Stat.intel + Stat.a_intel) * 10;

	Stat.phyDef = (Stat.health + Stat.a_health) * 2 + (Stat.str + Stat.a_str);
	Stat.a_phyDef = Armor.phydef + Shoulder.phydef + Belt.phydef + Pants.phydef + Boots.phydef;
	Stat.magDef = (Stat.spirit + Stat.a_spirit) * 10 + (Stat.intel + Stat.a_intel);
	Stat.a_magDef = Armor.magdef + Shoulder.magdef + Belt.magdef + Pants.magdef + Boots.magdef;

	Stat.a_phyAtt = Weapon.phydmgmin;
	Stat.a_magAtt = Weapon.magdmgmin;
}

void player::useIteminQS(int qs)
{
}

void player::rootItem(Item it)
{
	int last=-1;
	switch (it.type) {
	case item_consume:
		for (int i = 0; i < 32; i++) {
			if (consume[i].name == it.name) {
				consume[i].stack++;
				last = -1;
				break;
			}else if (consume[i].name == "없음"&&last<0) {
				last = i;
			}
		}
		if (last != -1) {
			consume[last] = it;
		}
		break;
	case item_weapon:
	case item_coat:
	case item_shoulder:
	case item_belt:
	case item_pants:
	case item_shoes:
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = it; break;
			}
		}
		break;
	}
}

void player::sellItem(int tab, int index)
{
	switch (tab) {
	case 0:
		gold += equipments[index].price;
		equipments[index] = empty;
		break;
	case 1:
		gold += consume[index].price * consume[index].stack;
		consume[index] = empty;
		break;
	case 2:
		break;
	}
}

void player::unequip(int pos)
{
	//0 상 1 하 2 어깨 3 벨트 4 신발 5무기
	switch (pos) {
	case 0:
		Armor.equipped = false;
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = Armor; break;
			}
		}
		Armor = empty;
		break;
	case 1:
		Pants.equipped = false;
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = Pants; break;
			}
		}
		Pants = empty;
		break;
	case 2:
		Shoulder.equipped = false;
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = Shoulder; break;
			}
		}
		Shoulder = empty;
		break;
	case 3:
		Belt.equipped = false;
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = Belt; break;
			}
		}
		Belt = empty;
		break;
	case 4:
		Boots.equipped = false;
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = Boots; break;
			}
		}
		Boots = empty;
		break;
	case 5:
		Weapon.equipped = false;
		for (int i = 0; i < 32; i++) {
			if (equipments[i].name == "없음") {
				equipments[i] = Weapon; break;
			}
		}
		Weapon = emptyWeapon;
	}
	useItem(-1, 0, 0);
}

Item player::setquickslot(int index, Item it)
{
	Item r = empty;
	switch (index) {
	case 1:
		if (q1.id > 0)r = q1;
		q1 = it;
		break;
	case 2:
		if (q2.id > 0)r = q2;
		q2 = it;
		break;
	case 3:
		if (q3.id > 0)r = q3;
		q3 = it;
		break;
	case 4:
		if (q4.id > 0)r = q4;
		q4 = it;
		break;
	case 5:
		if (q5.id > 0)r = q5;
		q5 = it;
		break;
	case 6:
		if (q6.id > 0)r = q6;
		q6 = it;
		break;
	}
	return r;
}



Item player::getItem(int curTab, int x, int y)
{
	Item t = empty;
	switch (curTab) {
	case 0:
		break;
	case 1:
		if (consume[x + y * 8].id > 0) {

		}
		break;
	}
	return t;
}

player::player()
{
	x = y = z = 0.0f;
}


player::~player()
{
}

