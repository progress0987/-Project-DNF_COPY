#include "stdafx.h"
#include "mainGame.h"


RECT rtemp;

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
//초기화
HRESULT mainGame::init(void) 
{
	gameNode::init(true);
#pragma region d3d로딩
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {			//디바이스를 생성하기 위한 D3D 객체 생성
		return E_FAIL;
	}

	D3DDISPLAYMODE d3ddm;
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	g_pD3D->CreateDevice(					//출력될 디바이스를 생성하는부분
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pd3dDevice
	);

	D3DXCreateSprite(g_pd3dDevice, &g_pd3dSprite);
	if (FAILED(g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pd3dSurface))) {
		return E_FAIL;
	}
	cam.x = 0;
	cam.y = 0;

	initItems();
	LoadSounds();
	LoadImages();
#pragma endregion

	pl = new player;
	seriaRoom = new Seria;
	village = new Village;
	mirkwood = new Mirkwood;
	loriendeep = new lorienDeep;


	seriaRoom->init();
	seriaRoom->setPlayer(pl);

	village->init();
	village->setPlayer(pl);

	conNode node;
	node.nextNode = village;
	node.x = 712;
	node.z = 378 * 2;
	dungeonGate gateinfo;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.isShow = false;
	gateinfo.movable = true;
	gateinfo.moveRect = {395,540,545,550};
	seriaRoom->setConNode(gateinfo, 2);
	gateinfo.isShow = false;
	gateinfo.movable = false;
	seriaRoom->setConNode(gateinfo, 0);
	seriaRoom->setConNode(gateinfo, 1);
	seriaRoom->setConNode(gateinfo, 3);

	node.nextNode = seriaRoom;
	node.x = seriaRoom->getWidth() / 2;
	node.z = (seriaRoom->getHeight() - 50) * 2;
	gateinfo.con = node;
	gateinfo.isBoss = false;
	gateinfo.isShow = false;
	gateinfo.movable = true;

	gateinfo.moveRect = {683,310,733,320};

	village->setConNode(gateinfo, 0);
	gateinfo.isShow = false;
	gateinfo.movable = false;
	village->setConNode(gateinfo, 1);
	village->setConNode(gateinfo, 2);
	village->setConNode(gateinfo, 3);


	mirkwood->setPlayer(pl);
	mirkwood->init();

	loriendeep->setPlayer(pl);
	loriendeep->init();

	pl->setCurScene(mirkwood);/////////////////////////////////////////////////현재맵설정
	pl->init();


	showDungeonSelect = showDungeonMoveScene = false;
	dunRect.push_back(RectMake(100, 100, 168, 73));
	dunRect.push_back(RectMake(300, 150, 168, 73));
	dunRect.push_back(RectMake(200, 300, 168, 73));

	dunName.push_back("던전_선택_로리엔");
	dunName.push_back("던전_선택_로리엔안쪽");
	dunName.push_back("던전_선택_빌마르크");

	Maps.push_back(mirkwood);
	Maps.push_back(loriendeep);


	dunselected = -1;
	onOpening = false;///////////////////////////////////////////////////오프닝플레이
	openingPhase = 0;
	openingTick = 0;

	return S_OK;
}
//해제
 void mainGame::release(void)
 {//사용한 이미지도 릴리즈해줘야함
	 

	 pl->release();

	 g_pd3dSurface->Release();
	 g_pd3dSprite->Release();
	 g_pd3dDevice->Release();
	 g_pD3D->Release();
	 
	 gameNode::release();
 }
 //연산~
 void mainGame::update(void)
 {
	 if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		 clicked = true;
	 }
	 if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		 lstay = true;
	 }
	 if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		 lstay = false;
		 clicked = false;
	 }
	 if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
		 rclicked = true;
	 }
	 if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON)) {
		 rclicked = false;
	 }
	 if (!showDungeonSelect && !showDungeonMoveScene&&!onOpening) {
		 pl->update();
		 pl->getCurMap()->update();
	 }
	 if (pl->getCurMap()->isChangable&& pl->getX()<27) {
		 showDungeonSelect = true;
	 }
	 if (pl->reset) {
		 pl->setCurScene(village, 100, (WINSIZEY - 100) * 2);
		 pl->reset = false;
		 pl->resetPlayer();
	 }
	 if (showDungeonMoveScene) {
		 dunmovetick++;
		 if (dunmovetick > 800) {
			 showDungeonMoveScene = false;
			 playBGM("BGM_던전_일반");
		 }
	 }
	 if (showDungeonSelect) {
		 for (int i = 0; i < dunRect.size(); i++) {
			 if (PtInRect(&dunRect[i], ptMouse)&&clicked) {
				 clicked = false;
				 if (i == dunselected) {
					 if (i == 0) {//로리엔
						 Maps[i]->resetDungeon();
						 pl->setCurScene(Maps[i], 150, (WINSIZEY - 50) * 2);
						 pl->setDirection(true);
						 dunselected = -1;
						 showDungeonSelect = false;
						 showDungeonMoveScene = true;
						 dunmovetick = 0;
					 }else if (i == 1) {//로리엔 깊은곳
						 Maps[i]->resetDungeon();
						 pl->setCurScene(Maps[i], 150, (WINSIZEY - 50) * 2);
						 pl->setDirection(true);
						 dunselected = -1;
						 showDungeonSelect = false;
						 showDungeonMoveScene = true;
						 dunmovetick = 0;
					 }
				 }
				 else {
					 dunselected = i;
				 }
			 }
		 }
	 }
	 if (onOpening) {
		 openingTick++;
		 switch (openingPhase) {
		 case 0://떨어지는것
			 if (openingTick > 900) {
				 openingPhase = 1;
			 }
			 break;
		 case 1://등급보여주는것
			 if (openingTick > 2000) {
				 openingPhase = 2;
			 }
			 break;
		 case 2://로딩창
			 if (openingTick > 3000) {
				 onOpening = false;
				 openingTick = openingPhase = -1;
			 }
			 break;
		 }
	 }


	 gameNode::update();

 }
 //여기가 그려주는 곳 - paint 후에 paintDC가 렌더됨 - 순서 바꿀시 주의할것
 void mainGame::render() 
 {
	 SetCursor(NULL);
	 ShowCursor(false);
	 if (SUCCEEDED(g_pd3dDevice->BeginScene())) {
		 //3D그리기 시작
		 if (SUCCEEDED(g_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND))) {
			 g_pd3dDevice->Clear( 0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0, 0, 0),1.0f,0);
			 if (onOpening) {
				 showOpening();
			 }
			 else if (showDungeonSelect) {
				 showdungeonselect();
			 }
			 else if (showDungeonMoveScene) {
				 showdunmoveScene();
			 }
			 else {
				 paint();
			 }
			 if (clicked) {
				 IMAGEMANAGER->findImage("마우스_클릭")->render(ptMouse.x, ptMouse.y);
			 }
			 else {
				 IMAGEMANAGER->findImage("마우스_기본")->render(ptMouse.x, ptMouse.y);
			 }
			 g_pd3dSprite->End();
		 }
		 if (!showDungeonSelect&&!showDungeonMoveScene&&!onOpening) {
			 g_pd3dSurface->GetDC(&hdc);
			 paintDC();
			 g_pd3dSurface->ReleaseDC(hdc);
		 }
		 g_pd3dDevice->EndScene();
	 }
	 g_pd3dDevice->Present(NULL, NULL, NULL, NULL);



 }

 //모든 이미지들 로드
 void mainGame::LoadImages()
 {
	 //이미지 처리
	 char tmp[100];
	 char tmp2[255];

	 
	 #pragma region 플레이어
	 ///플레이어
	 for (int i = 0; i < 210; i++) {

		 sprintf(tmp2, "sprites/character_premade/%d.png", i);
		 sprintf(tmp, "캐릭터_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/empty/emptyB/%d_p7.png", i);
		 sprintf(tmp, "빈손뒤_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/empty/emptyF/%d_p7.png", i);
		 sprintf(tmp, "빈손앞_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 플레이어 프레임은 210개

	 #pragma region 아이템 - 무기
	 ///아이템
	 //장착시 모습(무기)
	 for (vector<string>::iterator i = itemNames.begin(); i != itemNames.end(); i++) {
		 map<string, Item>::iterator f = itemList.find((*i));
		 if (f != itemList.end()&& f->second.id!=-1) {
			 for (int a = 0; a < 210; a++) {
				 switch (f->second.type) {
				 case itemType::item_weapon:
					 if (f->second.branch > 0) {
						 sprintf(tmp2, "sprites/item/equipment/weapon/%sb.img/%d_p%d.png", f->second.imgName, a,f->second.branch);
					 }
					 else {
						 sprintf(tmp2, "sprites/item/equipment/weapon/%sb.img/%d.png", f->second.imgName, a);
					 }
					 sprintf(tmp, "%s_뒤_%d", (*i).c_str(), a);
					 IMAGEMANAGER->addImage(tmp, tmp2);

					 if (f->second.branch > 0) {
						 sprintf(tmp2, "sprites/item/equipment/weapon/%sc.img/%d_p%d.png", f->second.imgName, a, f->second.branch);
					 }
					 else {
						 sprintf(tmp2, "sprites/item/equipment/weapon/%sc.img/%d.png", f->second.imgName, a);
					 }
					 sprintf(tmp, "%s_앞_%d", (*i).c_str(), a);
					 IMAGEMANAGER->addImage(tmp, tmp2);
					 break;
				 case itemType::item_coat:
					 break;

				 }
			 }
		 }
	 }
	 
#pragma endregion 무기 앞,뒤 이미지는 아이템리스트에 들어가있는 정보로 로드됨. 내부 for문 참조

	 #pragma region 아이템 - 갑옷(판금)
	 for (int i = 0; i < 70; i++) {
		 if (i < 63) {
			 sprintf(tmp2, "sprites/item/icons/plate_belt.img/%d.png", i);
			 sprintf(tmp, "판금_벨트_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 if (i < 64) {
			 sprintf(tmp2, "sprites/item/icons/plate_neck.img/%d.png", i);
			 sprintf(tmp, "판금_어깨_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 if (i < 65) {
			 sprintf(tmp2, "sprites/item/icons/plate_shoes.img/%d.png", i);
			 sprintf(tmp, "판금_신발_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 if (i < 67) {
			 sprintf(tmp2, "sprites/item/icons/plate_pants.img/%d.png", i);
			 sprintf(tmp, "판금_바지_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 sprintf(tmp2, "sprites/item/icons/plate_coat.img/%d.png", i);
		 sprintf(tmp, "판금_상의_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 판금의 모든 인벤토리 아이템 이미지 저장
	 
	 #pragma region 아이템 - 무기
	 for (int i = 0; i < 169; i++) {
		 if (i < 160) {
			 sprintf(tmp2, "sprites/item/icons/sswd.img/%d.png", i);
			 sprintf(tmp, "소검_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 sprintf(tmp2, "sprites/item/icons/katana.img/%d.png", i);
		 sprintf(tmp, "도_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 소검, 도 만 추가
	 
	 #pragma region 아이템 - 악세서리
	 for (int i = 0; i < 197; i++) {
		 sprintf(tmp2, "sprites/item/icons/bracelet.img/%d.png", i);
		 sprintf(tmp, "팔찌_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 for (int i = 0; i < 249; i++) {
		 sprintf(tmp2, "sprites/item/icons/ring.img/%d.png", i);
		 sprintf(tmp, "반지_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 for (int i = 0; i < 204; i++) {
		 sprintf(tmp2, "sprites/item/icons/necklace.img/%d.png", i);
		 sprintf(tmp, "목걸이_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 팔찌, 반지, 목걸이
	 
	 #pragma region 소모품
	 for (int i = 0; i < 30; i++) {
		 sprintf(tmp2, "sprites/item/icons/consumption.img/%d.png", i);
		 sprintf(tmp, "소모_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 0~30까지만 추가

	 #pragma region 필드위 이미지
		 sprintf(tmp2, "sprites/item/onField/fieldimage.img/20.png");
		 sprintf(tmp, "아이템_필드_소모품");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/fieldimage.img/9.png");
		 sprintf(tmp, "아이템_필드_소검");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/field_equip.img/15.png");
		 sprintf(tmp, "아이템_필드_판금_상의");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/field_equip.img/16.png");
		 sprintf(tmp, "아이템_필드_판금_하의");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/field_equip.img/17.png");
		 sprintf(tmp, "아이템_필드_판금_어깨");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/field_equip.img/18.png");
		 sprintf(tmp, "아이템_필드_판금_벨트");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/field_equip.img/19.png");
		 sprintf(tmp, "아이템_필드_판금_신발");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/fieldimage.img/26.png");
		 sprintf(tmp, "아이템_필드_골드_1");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/fieldimage.img/27.png");
		 sprintf(tmp, "아이템_필드_골드_2");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/item/onField/fieldimage.img/25.png");
		 sprintf(tmp, "아이템_필드_골드_3");
		 IMAGEMANAGER->addImage(tmp, tmp2);


#pragma endregion 소모품, 판금, 무기, 돈

	 #pragma region UI
	 IMAGEMANAGER->addImage("UI_아이템선택", "sprites/UI/attachicon.img/1.png");
	 IMAGEMANAGER->addImage("UI_하단_기본창", "sprites/UI/hud.img/0.png");
	 IMAGEMANAGER->addImage("UI_하단_기본창_확장", "sprites/UI/hud.img/133.png");
	 IMAGEMANAGER->addImage("UI_하단_기본창_조각", "sprites/UI/hud.img/134.png");
	 IMAGEMANAGER->addImage("UI_하단_경험치", "sprites/UI/hud.img/4.png");
	 IMAGEMANAGER->addImage("UI_HP", "sprites/UI/hud.img/1.png");
	 IMAGEMANAGER->addImage("UI_MP", "sprites/UI/hud.img/2.png");


	 //IMAGEMANAGER->addImage("UI_구입_기본", "sprites/UI/hud.img/2.png");
	 //IMAGEMANAGER->addImage("UI_구입_오버", "sprites/UI/hud.img/2.png");
	 //IMAGEMANAGER->addImage("UI_구입_클릭", "sprites/UI/hud.img/2.png");
	 //IMAGEMANAGER->addImage("UI_확인_", "sprites/UI/hud.img/2.png");


	 IMAGEMANAGER->addImage("UI_상점_슬롯", "sprites/UI/shop_slot.img/0.png");
	 //IMAGEMANAGER->addImage("UI_상점_슬롯", "sprites/UI/shop_slot.img/0.png");



	 IMAGEMANAGER->addImage("UI_닫기_기본", "sprites/UI/popup.img/110.png");
	 IMAGEMANAGER->addImage("UI_닫기_오버", "sprites/UI/popup.img/111.png");
	 IMAGEMANAGER->addImage("UI_닫기_클릭", "sprites/UI/popup.img/112.png");


	 IMAGEMANAGER->addImage("UI_인벤토리_기본창", "sprites/UI/inventory.img/0.png");
	 IMAGEMANAGER->addImage("UI_인벤토리_활성탭", "sprites/UI/windowcommon.img/31.png");
	 IMAGEMANAGER->addImage("UI_인벤토리_비활성탭", "sprites/UI/windowcommon.img/29.png");
	 IMAGEMANAGER->addImage("UI_인벤토리_장비베이스", "sprites/UI/inventory.img/21.png");
	 //IMAGEMANAGER->addImage("UI_인벤토리_아이템_라인베이스", "sprites/UI/inventory.img/39.png");
	 IMAGEMANAGER->addImage("UI_인벤토리_아이템_개별", "sprites/UI/inventory.img/49.png");
	 //IMAGEMANAGER->addImage("UI_인벤토리_기본창", "sprites/UI/inventory.img/0.png");
	 for (int i = 0; i < 9; i++) {
		 sprintf(tmp2, "sprites/UI/windowcommon.img/%d.png", i);
		 sprintf(tmp, "창_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 IMAGEMANAGER->addImage("UI_스텟_기본", "sprites/UI/profile.img/15.png");
	 IMAGEMANAGER->addImage("UI_인벤토리_하단", "sprites/UI/inventory.img/13.png");

	 for (int i = 0; i < 10; i++) {
		 sprintf(tmp2, "sprites/effects/game/combo_big.img/%d.png", i+11);
		 sprintf(tmp, "대미지_일반_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/effects/game/combo_big.img/%d.png", i + 22);
		 sprintf(tmp, "대미지_크리티컬_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/effects/game/combo_big.img/%d.png", i + 88);
		 sprintf(tmp, "플레이어_대미지_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 IMAGEMANAGER->addImage("크리티컬_표시", "sprites/effects/game/combo_big.img/84.png");

	 for (int i = 0; i < 12; i++) {
		 sprintf(tmp2, "sprites/effects/item/heal.img/%d.png", i);
		 sprintf(tmp, "체력회복_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/effects/item/mpup.img/%d.png", i);
		 sprintf(tmp, "마나회복_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 for (int i = 1; i < 7; i++) {
			 sprintf(tmp2, "sprites/UI/keyshortcut.img/%d.png", i+45);
			 sprintf(tmp, "키보드_숏컷_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 //키 숏컷 출력 - 나중에 for문으로 한번에 처리할것
	 {
			 sprintf(tmp2, "sprites/UI/keyshortcut.img/55.png");
			 sprintf(tmp, "키보드_숏컷_A");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/73.png");
			 sprintf(tmp, "키보드_숏컷_S");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/58.png");
			 sprintf(tmp, "키보드_숏컷_D");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/60.png");
			 sprintf(tmp, "키보드_숏컷_F");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/61.png");
			 sprintf(tmp, "키보드_숏컷_G");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/62.png");
			 sprintf(tmp, "키보드_숏컷_H");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/71.png");
			 sprintf(tmp, "키보드_숏컷_Q");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/77.png");
			 sprintf(tmp, "키보드_숏컷_W");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/59.png");
			 sprintf(tmp, "키보드_숏컷_E");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/72.png");
			 sprintf(tmp, "키보드_숏컷_R");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/UI/keyshortcut.img/74.png");
			 sprintf(tmp, "키보드_숏컷_T");
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
#pragma endregion

	 #pragma region 몬스터
	 //고블린
	 for (int i = 0; i < 17; i++) {
		 sprintf(tmp2, "sprites/monster/goblin/blue/%d.png", i);
		 sprintf(tmp, "고블린_파랑_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/darkgreen/%d.png", i);
		 sprintf(tmp, "고블린_십장_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/green/%d.png", i);
		 sprintf(tmp, "고블린_초록_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/throw/%d.png", i);
		 sprintf(tmp, "고블린_투석_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/red/%d.png", i);
		 sprintf(tmp, "고블린_빨강_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/belt/belt_norm/%d.png", i);
		 sprintf(tmp, "고블린_장비_벨트_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/face/face_blue/%d.png", i);
		 sprintf(tmp, "고블린_얼굴_파랑_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/face/face_red/%d.png", i);
		 sprintf(tmp, "고블린_얼굴_빨강_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/pants/pants_norm/%d.png", i);
		 sprintf(tmp, "고블린_장비_바지_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/wrist/wrist_norm/%d.png", i);
		 sprintf(tmp, "고블린_장비_팔찌_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/goblin/equipment/weapon/weapon_2/%d.png", i);
		 sprintf(tmp, "고블린_무기_십장_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 for (int i = 0; i < 4; i++) {
		 sprintf(tmp2, "sprites/monster/goblin/equipment/weapon/throwstone.img/%d.png", i);
		 sprintf(tmp, "고블린_무기_투석_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 
	 //타우
	 for (int i = 0; i < 31; i++) {
		 sprintf(tmp2, "sprites/monster/tau/sprite_monster_tau/body07.img/%d.png", i);
		 sprintf(tmp, "메카타우_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/tau/sprite_monster_tau/metacowlight.img/%d.png", i);
		 sprintf(tmp, "메카타우_빛_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/tau/sprite_monster_tau_equipment/metacowaxe.img/%d.png", i);
		 sprintf(tmp, "메카타우_무기_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/tau/sprite_monster_tau_equipment/metacowaxeglow.img/%d.png", i);
		 sprintf(tmp, "메카타우_무기_빛_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/tau/sprite_monster_tau/tauarmy.img/%d.png", i);
		 sprintf(tmp, "타우아미_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/monster/tau/sprite_monster_tau/tauassaulter.img/%d.png", i);
		 sprintf(tmp, "타우어설터_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 고블린, 타우

	 #pragma region 맵선택
	 IMAGEMANAGER->addImage("던전_선택_표시", "sprites/cutscene/onselect/selectdungeon02.img/0.png");
	 IMAGEMANAGER->addImage("던전_선택_배경", "sprites/cutscene/onselect/granfloris.img/0.png");
	 IMAGEMANAGER->addImage("던전_선택_로리엔", "sprites/cutscene/onselect/elvengard.img/0.png");
	 IMAGEMANAGER->addImage("던전_선택_로리엔안쪽", "sprites/cutscene/onselect/elvengard.img/1.png");
	 IMAGEMANAGER->addImage("던전_선택_빌마르크", "sprites/cutscene/onselect/elvengard.img/2.png");
	 IMAGEMANAGER->addImage("던전_선택_이동", "sprites/cutscene/onmove/granfloris.img/0.png");


#pragma endregion 지도선택하는곳

	 #pragma region 맵 타일
	 //맵 이동 게이트
	 {
		 IMAGEMANAGER->addImage("던전_문_사이드",		"sprites/maps/dungeons/gates/gate_side.img/0.png");
		 IMAGEMANAGER->addImage("던전_문_사이드_창살",	"sprites/maps/dungeons/gates/gate_side.img/1.png");
		 IMAGEMANAGER->addImage("던전_문_사이드_빛",	"sprites/maps/dungeons/gates/gate_side_light.img/0.png");

		 IMAGEMANAGER->addImage("던전_문_위",		"sprites/maps/dungeons/gates/gate_up.img/0.png");
		 IMAGEMANAGER->addImage("던전_문_위_창살",	"sprites/maps/dungeons/gates/gate_up.img/1.png");
		 IMAGEMANAGER->addImage("던전_문_위_빛",	"sprites/maps/dungeons/gates/gate_up_light.img/0.png");
		
		 IMAGEMANAGER->addImage("던전_문_아래",		"sprites/maps/dungeons/gates/gate_down.img/0.png");
		 IMAGEMANAGER->addImage("던전_문_아래_창살","sprites/maps/dungeons/gates/gate_down.img/1.png");
		 IMAGEMANAGER->addImage("던전_문_아래_빛",	"sprites/maps/dungeons/gates/gate_down_light.img/0.png");
		 
		 IMAGEMANAGER->addImage("던전_보스문_사이드",		"sprites/maps/dungeons/gates/bossgate_side.img/0.png");
		 IMAGEMANAGER->addImage("던전_보스문_사이드_창살",	"sprites/maps/dungeons/gates/bossgate_side.img/1.png");
		 IMAGEMANAGER->addImage("던전_보스문_사이드_빛",	"sprites/maps/dungeons/gates/bossgate_side_light.img/0.png");
		 
		 
		 IMAGEMANAGER->addImage("던전_보스문_위",		"sprites/maps/dungeons/gates/bossgate_up.img/0.png");
		 IMAGEMANAGER->addImage("던전_보스문_위_창살",	"sprites/maps/dungeons/gates/bossgate_up.img/1.png");
		 IMAGEMANAGER->addImage("던전_보스문_위_빛",	"sprites/maps/dungeons/gates/bossgate_up_light.img/0.png");
		
		 IMAGEMANAGER->addImage("던전_보스문_아래",		"sprites/maps/dungeons/gates/bossgate_down.img/0.png");
		 IMAGEMANAGER->addImage("던전_보스문_아래_창살","sprites/maps/dungeons/gates/bossgate_down.img/1.png");
		 IMAGEMANAGER->addImage("던전_보스문_아래_빛",	"sprites/maps/dungeons/gates/bossgate_down_light.img/0.png");
	 }

	 //머크우드 타일
	 {
		 IMAGEMANAGER->addImage("던전_머크우드_배경_뒤", "sprites/maps/dungeons/mirkwood/back_far.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_배경_중간", "sprites/maps/dungeons/mirkwood/back_middle.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_배경_나무길", "sprites/maps/dungeons/mirkwood/tree_backway.img/0.png");

		 IMAGEMANAGER->addImage("던전_머크우드_바닥_0", "sprites/maps/dungeons/mirkwood/tile.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_1", "sprites/maps/dungeons/mirkwood/tile.img/1.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_2", "sprites/maps/dungeons/mirkwood/tile.img/2.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_3", "sprites/maps/dungeons/mirkwood/tile.img/3.png");
		 IMAGEMANAGER->addImage("던전_머크우드_바닥_덧붙임", "sprites/maps/dungeons/mirkwood/tile_ex.img/0.png");

		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_0", "sprites/maps/dungeons/mirkwood/stone.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_1", "sprites/maps/dungeons/mirkwood/stone.img/1.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_2", "sprites/maps/dungeons/mirkwood/stone.img/2.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_3", "sprites/maps/dungeons/mirkwood/stone.img/3.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_4", "sprites/maps/dungeons/mirkwood/stone.img/4.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_돌_5", "sprites/maps/dungeons/mirkwood/stone.img/5.png");

		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_0", "sprites/maps/dungeons/mirkwood/tree.img/0.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_1", "sprites/maps/dungeons/mirkwood/tree.img/1.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_2", "sprites/maps/dungeons/mirkwood/tree.img/2.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_3", "sprites/maps/dungeons/mirkwood/tree.img/3.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_4", "sprites/maps/dungeons/mirkwood/tree.img/4.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_5", "sprites/maps/dungeons/mirkwood/tree.img/5.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_6", "sprites/maps/dungeons/mirkwood/tree.img/6.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_7", "sprites/maps/dungeons/mirkwood/tree.img/7.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_8", "sprites/maps/dungeons/mirkwood/tree.img/8.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_9", "sprites/maps/dungeons/mirkwood/tree.img/9.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_10", "sprites/maps/dungeons/mirkwood/tree.img/10.png");
		 IMAGEMANAGER->addImage("던전_머크우드_지형_나무_11", "sprites/maps/dungeons/mirkwood/tree.img/11.png");
	 }
#pragma endregion 머크우드

	 #pragma region 상태이상 이펙트
	 //혈흔

	 for (int i = 0; i < 7; i++) {
		 sprintf(tmp2, "sprites/effects/game/hit/bloodlarge.img/%d.png", i);
		 sprintf(tmp, "혈흔_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //빙결
	 {
		 sprintf(tmp2, "sprites/status/freeze/4.png");
		 sprintf(tmp, "빙결_0");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/5.png");
		 sprintf(tmp, "빙결_1");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/6.png");
		 sprintf(tmp, "빙결_2");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/7.png");
		 sprintf(tmp, "빙결_3");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/18.png");
		 sprintf(tmp, "빙결_해제_0");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/19.png");
		 sprintf(tmp, "빙결_해제_1");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/20.png");
		 sprintf(tmp, "빙결_해제_2");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/21.png");
		 sprintf(tmp, "빙결_해제_3");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/22.png");
		 sprintf(tmp, "빙결_해제_4");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/status/freeze/23.png");
		 sprintf(tmp, "빙결_해제_5");
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 빙결크기는 몬스터 크기에따라 달라짐

	 #pragma region 스킬 슬롯 이미지
	 for (int i = 0; i < 138; i++) {
		 sprintf(tmp2, "sprites/skill/icons/%d.png", i);
		 sprintf(tmp, "스킬_아이콘_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 있는이미지만 넣어둬서 이외의 숫자넣을경우 터짐

	 #pragma region 스킬
	 //어퍼슬래시
	 for (int i = 0; i < 9; i++) {
		 sprintf(tmp2, "sprites/skill/upperslash/%d.png", i);
		 sprintf(tmp, "어퍼슬래시_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //파동검
	 for (int i = 0; i < 5; i++) {
		 sprintf(tmp2, "sprites/skill/wave/hadouken_hadou.img/%d.png", i);
		 sprintf(tmp, "파동검_공격_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/wave/hadouken_ken.img/%d.png", i);
		 sprintf(tmp, "파동검_효과_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //파동검 빙인
	 {
		 for (int i = 0; i < 6; i++) {
			 sprintf(tmp2, "sprites/skill/icewave/icewave1.img/%d.png", i);
			 sprintf(tmp, "파동검_빙인_시작효과_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 11; i++) {
			 sprintf(tmp2, "sprites/skill/icewave/icewave2.img/%d.png", i);
			 sprintf(tmp, "파동검_빙인_얼음기둥_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 64; i++) {

			 sprintf(tmp2, "sprites/skill/icewave/icewaveparticle.img/%d.png", i);
			 sprintf(tmp, "파동검_빙인_얼음조각_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 3; i++) {
			 sprintf(tmp2, "sprites/skill/icewave/icewaveparticlesmoke.img/%d.png", i);
			 sprintf(tmp, "파동검_빙인_얼음구름_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 }
	 
	 //파동검 폭염
	 {
		 for (int i = 0; i < 10; i++) {
			 sprintf(tmp2, "sprites/skill/firewave/flame_dodge.img/%d.png", i);
			 sprintf(tmp, "파동검_폭염_화염_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/firewave/flame_normal.img/%d.png", i);
			 sprintf(tmp, "파동검_폭염_연기_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }

		 sprintf(tmp2, "sprites/skill/firewave/flame_ground.img/0.png");
		 sprintf(tmp, "파동검_폭염_화염_바닥_화염");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/firewave/flame_ground.img/1.png");
		 sprintf(tmp, "파동검_폭염_화염_바닥_연기");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/firewave/flame_line.img/0.png");
		 sprintf(tmp, "파동검_폭염_화염_바닥_폭발");
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 for (int i = 0; i < 10; i++) {
			 sprintf(tmp2, "sprites/skill/firewave/sword_effect.img/%d.png", i);
			 sprintf(tmp, "파동검_폭염_칼_화염_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2,true,RGB(0,0,0));
			 sprintf(tmp2, "sprites/skill/firewave/sword_dodge.img/%d.png", i);
			 sprintf(tmp, "파동검_폭염_칼_잔영_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2,true,RGB(0,0,0));
			 sprintf(tmp2, "sprites/skill/firewave/sword_normal.img/%d.png", i);
			 sprintf(tmp, "파동검_폭염_칼_연기_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2,true,RGB(0,0,0));
		 }
	 }

	 //진공참
	 {
			 sprintf(tmp2,"sprites/skill/vaccumslash/grandwave.img/0.png");
			 sprintf(tmp, "진공참_뒤");
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwave.img/1.png");
			 sprintf(tmp, "진공참_앞");
			 IMAGEMANAGER->addImage(tmp, tmp2);

			 sprintf(tmp2, "sprites/skill/vaccumslash/surajin.img/0.png");
			 sprintf(tmp, "수라진공참_뒤");
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/surajin.img/1.png");
			 sprintf(tmp, "수라진공참_앞");
			 IMAGEMANAGER->addImage(tmp, tmp2);

		 for (int i = 0; i < 4; i++) {
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwaveblade.img/%d.png", i);
			 sprintf(tmp, "진공참_모션_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwavefullcharge.img/%d.png", i);
			 sprintf(tmp, "진공참_풀차지_뒤_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwavefullcharge.img/%d.png", i+5);
			 sprintf(tmp, "진공참_풀차지_앞_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 13; i++) {
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwaveoncharge.img/%d.png", i+13);
			 sprintf(tmp, "진공참_차지중_뒤_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/vaccumslash/grandwaveoncharge.img/%d.png", i);
			 sprintf(tmp, "진공참_차지중_앞_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 }

	 //파동해제
	 {
		 for (int i = 0; i < 5; i++) {
			 sprintf(tmp2, "sprites/skill/releasewave/releasewave1.img/%d.png", i);
			 sprintf(tmp, "파동해제_해골_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/releasewave/releasewave2.img/%d.png", i);
			 sprintf(tmp, "파동해제_효과_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }

		 sprintf(tmp2, "sprites/skill/releasewave/releasewave1.img/5.png");
		 sprintf(tmp, "파동해제_해골_5");
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //부동명왕진
	 {
		 for (int i = 0; i < 6; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/1-dodge.img/%d.png", i);
			 sprintf(tmp, "부동_폭발_1_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/2-dodge.img/%d.png", i);
			 sprintf(tmp, "부동_폭발_2_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/3-dodge.img/%d.png", i);
			 sprintf(tmp, "부동_폭발_3_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/effect.img/%d.png", i);
			 sprintf(tmp, "부동_구체_효과_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/target-effect.img/%d.png", i);
			 sprintf(tmp, "부동_구속_효과_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/target-effect-dodge.img/%d.png", i);
			 sprintf(tmp, "부동_구속_효과_배경_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 5; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/action.img/%d.png", i);
			 sprintf(tmp, "부동_시동_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 for (int i = 0; i < 3; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/bead_disappear_dodge.img/%d.png", i);
			 sprintf(tmp, "부동_소멸이펙트_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
		 sprintf(tmp2, "sprites/skill/wavespin/bead-dodge.img/1.png");
		 sprintf(tmp, "부동_구체");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/wavespin/bead-dodge.img/2.png");
		 sprintf(tmp, "부동_구체_오라");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/skill/wavespin/mg-circle.img/0.png");
		 sprintf(tmp, "부동_마법진");
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 for (int i = 0; i < 9; i++) {
			 sprintf(tmp2, "sprites/skill/wavespin/mg-circle-back.img/%d.png", i);
			 sprintf(tmp, "부동_마법진_이펙트_뒤_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
			 sprintf(tmp2, "sprites/skill/wavespin/mg-circle-front.img/%d.png", i);
			 sprintf(tmp, "부동_마법진_이펙트_앞_%d", i);
			 IMAGEMANAGER->addImage(tmp, tmp2);
		 }
	 }

	 //살의의 파동
#pragma endregion 어퍼슬래시, 파동검, 빙인, 폭염, 진공참, 파동해제, 부동명왕진

	 #pragma region NPC 이미지
	 for (int i = 0; i < 12; i++) {
		 sprintf(tmp2, "sprites/NPC/origin_seria.img/%d.png", i);
		 sprintf(tmp, "NPC_세리아_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);

		 sprintf(tmp2, "sprites/NPC/linus.img/%d.png", i);
		 sprintf(tmp, "NPC_라이너스_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
	 for (int i = 0; i < 8; i++) {
		 sprintf(tmp2, "sprites/NPC/kanna.img/%d.png", i);
		 sprintf(tmp, "NPC_칸나_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }
#pragma endregion 세리아,칸나,라이너스


	 ///기타 이미지

	 //마우스 포인터
	 IMAGEMANAGER->addImage("마우스_기본", "sprites/UI/cursor.img/0.png");
	 IMAGEMANAGER->addImage("마우스_클릭", "sprites/UI/cursor.img/1.png");

	 //몬스터 체력
	 IMAGEMANAGER->addImage("체력바_배경", "sprites/UI/overheadgauge.img/0.png");
	 IMAGEMANAGER->addImage("체력바_빨강", "sprites/UI/overheadgauge.img/1.png");
	 //오프닝
	 {
		 IMAGEMANAGER->addImage("로딩_배경", "sprites/Opening/sprite_interface2_nowloading/nowloading.img/1.png");
		 IMAGEMANAGER->addImage("로딩_회전", "sprites/Opening/sprite_interface2_nowloading/nowloading.img/4.png");
		 
		 IMAGEMANAGER->addImage("오프닝_배경", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/0.png");
		 IMAGEMANAGER->addImage("오프닝_로고_강조", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/2.png");
		 IMAGEMANAGER->addImage("오프닝_로고", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/3.png");
		 IMAGEMANAGER->addImage("오프닝_로고_먼지", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/4.png");
		 IMAGEMANAGER->addImage("오프닝_붓_1", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/5.png");
		 IMAGEMANAGER->addImage("오프닝_붓_2", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/6.png");
		 IMAGEMANAGER->addImage("오프닝_붓_3", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/7.png");
		 IMAGEMANAGER->addImage("오프닝_붓_4", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/8.png");
		 IMAGEMANAGER->addImage("오프닝_로고_빛남_1", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/9.png");
		 IMAGEMANAGER->addImage("오프닝_로고_빛남_2", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/10.png");
		 IMAGEMANAGER->addImage("오프닝_로고_빛남_3", "sprites/Opening/sprite_interface2_nowloading_intro/intro.img/11.png");
		 IMAGEMANAGER->addImage("오프닝_등급", "sprites/Opening/sprite_interface2_nowloading_review_grade/reviewgrade.img/3.png");

	 }

	 //맵 종료
	 {
		 IMAGEMANAGER->addImage("마지막출력_배경", "sprites/UI/eplp.img/16.png");
		 IMAGEMANAGER->addImage("마지막출력", "sprites/UI/eplp.img/0.png");
		 IMAGEMANAGER->addImage("재도전_일반", "sprites/UI/eplp.img/1.png");
		 IMAGEMANAGER->addImage("재도전_오버", "sprites/UI/eplp.img/2.png");
		 IMAGEMANAGER->addImage("재도전_오버_배경", "sprites/UI/eplp.img/13.png");
		 IMAGEMANAGER->addImage("재도전_클릭", "sprites/UI/eplp.img/3.png");
		 IMAGEMANAGER->addImage("재도전_비활", "sprites/UI/eplp.img/4.png");

		 IMAGEMANAGER->addImage("다른던전_일반", "sprites/UI/eplp.img/5.png");
		 IMAGEMANAGER->addImage("다른던전_오버", "sprites/UI/eplp.img/6.png");
		 IMAGEMANAGER->addImage("다른던전_오버_배경", "sprites/UI/eplp.img/14.png");
		 IMAGEMANAGER->addImage("다른던전_클릭", "sprites/UI/eplp.img/7.png");
		 IMAGEMANAGER->addImage("다른던전_비활", "sprites/UI/eplp.img/8.png");

		 IMAGEMANAGER->addImage("마을로_일반", "sprites/UI/eplp.img/9.png");
		 IMAGEMANAGER->addImage("마을로_오버", "sprites/UI/eplp.img/10.png");
		 IMAGEMANAGER->addImage("마을로_오버_배경", "sprites/UI/eplp.img/15.png");
		 IMAGEMANAGER->addImage("마을로_클릭", "sprites/UI/eplp.img/11.png");
		 IMAGEMANAGER->addImage("마을로_비활", "sprites/UI/eplp.img/12.png");
	 }
	 //코인 카운트다운
	 for (int i = 0; i < 10; i++) {
		 sprintf(tmp2, "sprites/UI/countdown.img/%d.png", i+2);
		 sprintf(tmp, "카운트다운_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
		 sprintf(tmp2, "sprites/UI/countdown.img/%d.png", i+25);
		 sprintf(tmp, "코인카운트_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //코인잔여출력창
	 IMAGEMANAGER->addImage("코인잔여", "sprites/UI/countdown.img/0.png");

	 //레벨업이펙트
	 for (int i = 0; i < 15; i++) {
		 sprintf(tmp2, "sprites/effects/game/blast1.img/%d.png", i);
		 sprintf(tmp, "레벨업_%d", i);
		 IMAGEMANAGER->addImage(tmp, tmp2);
	 }

	 //레벨업이미지
	 IMAGEMANAGER->addImage("레벨업", "sprites/effects/game/levelup.img/0.png");

	 IMAGEMANAGER->addImage("X표시", "sprites/invalid.png");
	 IMAGEMANAGER->addImage("그림자", "sprites/shadow.png");
	 IMAGEMANAGER->addImage("페이드", "sprites/fade.img");
 }

 //모든 사운드들 로드
 void mainGame::LoadSounds()
 {
	 SOUNDMANAGER->addSound("캐릭_평타_1", "Sounds/char/sm_atk_01.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_평타_2", "Sounds/char/sm_atk_02.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_평타_3", "Sounds/char/sm_atk_03.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_점프공격", "Sounds/char/sm_jumpatk_01.ogg", false, false);
	 
	 SOUNDMANAGER->addSound("캐릭_타격", "Sounds/char/sm_dmg_01.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_사망", "Sounds/char/sm_die.ogg", false, false);

	 SOUNDMANAGER->addSound("캐릭_스킬_쿨타임", "Sounds/char/sm_cooltime.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_부동_시작", "Sounds/char/sm_boodong_start.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_부동_폭발", "Sounds/char/sm_boodong_explosion.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_파동검폭염", "Sounds/char/sm_firewave.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_파동검빙인", "Sounds/char/sm_icewave.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_충전", "Sounds/char/sm_gue_charge.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_진공참", "Sounds/char/sm_jingong.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_수라진공참", "Sounds/char/sm_sura_jingong.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_어퍼", "Sounds/char/sm_upslash.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬_웨이브", "Sounds/char/sm_wave.ogg", false, false);

	 SOUNDMANAGER->addSound("캐릭_스킬사운드_부동_구생성", "Sounds/skill/boodong_ball.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬사운드_부동_마법진_루프", "Sounds/skill/boodong_circle_loop.ogg", false, true);
	 SOUNDMANAGER->addSound("캐릭_스킬사운드_부동_구폭발", "Sounds/skill/boodong_explosion.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬사운드_어퍼", "Sounds/skill/upper_slash_01.ogg", false, false);
	 SOUNDMANAGER->addSound("캐릭_스킬사운드_웨이브", "Sounds/skill/hadouken.ogg", false, false);

	 SOUNDMANAGER->addSound("효과_화염폭발", "Sounds/effect/fire_explosion.ogg", false, false);
	 SOUNDMANAGER->addSound("효과_체력회복", "Sounds/effect/hp_recovered.ogg", false, false);
	 SOUNDMANAGER->addSound("효과_마나회복", "Sounds/effect/mp_recovered.ogg", false, false);
	 SOUNDMANAGER->addSound("효과_결과출력", "Sounds/effect/result.ogg", false, false);

	 SOUNDMANAGER->addSound("UI_레벨업", "Sounds/UI/levup.ogg", false, false);
	 SOUNDMANAGER->addSound("UI_아이템획득", "Sounds/UI/get_item.ogg", false, false);
	 SOUNDMANAGER->addSound("UI_이어하기", "Sounds/UI/coin_in.ogg", false, false);

	 SOUNDMANAGER->addSound("몬스터_고블린_사망", "Sounds/monster/goblin/gbn_die_01.ogg", false, false);
	 SOUNDMANAGER->addSound("몬스터_고블린_피격", "Sounds/monster/goblin/gbn_dmg_03.ogg", false, false);
	 SOUNDMANAGER->addSound("몬스터_고블린_투척", "Sounds/monster/goblin/gbn_thw.ogg", false, false);

	 //////////////////////////////////////BGM


	 SOUNDMANAGER->addSound("BGM_마을", "Sounds/bgm/hendonmyre.ogg", true, true);
	 bgmNames.push_back("BGM_마을");
	 SOUNDMANAGER->addSound("BGM_던전_일반", "Sounds/bgm/mirkwood.ogg", true, true);
	 bgmNames.push_back("BGM_던전_일반");
	 SOUNDMANAGER->addSound("BGM_던전_보스", "Sounds/bgm/mirkwood_boss.ogg", true, true);
	 bgmNames.push_back("BGM_던전_보스");
	 SOUNDMANAGER->addSound("BGM_세리아", "Sounds/bgm/seria_gate.ogg", true, true);
	 bgmNames.push_back("BGM_세리아");

 }

 void mainGame::showdungeonselect()
 {
	 IMAGEMANAGER->findImage("던전_선택_배경")->render();
	 for (int i = 0; i < dunRect.size(); i++) {
		 if (i == dunselected) {
			 IMAGEMANAGER->findImage("던전_선택_표시")->render(dunRect[i].left - 3, dunRect[i].top - 2);
		 }
		 IMAGEMANAGER->findImage(dunName[i])->render(dunRect[i].left, dunRect[i].top);
	 }

 }

 void mainGame::showdunmoveScene()
 {
	 if (dunmovetick < 128) {
	 IMAGEMANAGER->findImage("던전_선택_이동")->blurredrender(0,0,dunmovetick*2);
		 //IMAGEMANAGER->findImage("페이드")->coloredrender(0, 0, 255 - dunmovetick*2);
	 }
	 else if (dunmovetick > 672) {
	 IMAGEMANAGER->findImage("던전_선택_이동")->blurredrender(0, 0, (800-dunmovetick) * 2);
		 //IMAGEMANAGER->findImage("페이드")->coloredrender(0, 0, (dunmovetick - 672) * 2);
	 }
	 else {
		 IMAGEMANAGER->findImage("던전_선택_이동")->render();
	 }
 }

 void mainGame::showOpening()
 {
	 switch (openingPhase) {
	 case 0://떨어지는것
		 IMAGEMANAGER->findImage("오프닝_배경")->render(0,0);
		 if (300<openingTick&&openingTick < 350) {
			 IMAGEMANAGER->findImage("오프닝_로고_강조")->DFpointrender(13, 23,0,0,(300.f/(float)openingTick)*1.5f);
		 }
		 else if (350 <= openingTick && openingTick < 500) {
			 IMAGEMANAGER->findImage("오프닝_로고_먼지")->DFpointrender(210, 114, 0, 0, openingTick / 350.f, 255 * ((float)(520 - openingTick) / 170.f));
			 IMAGEMANAGER->findImage("오프닝_로고")->render(237, 189);
		 }
		 else if (500 <= openingTick&&openingTick<510) {
			 IMAGEMANAGER->findImage("오프닝_로고_먼지")->DFpointrender(210, 114, 0, 0, openingTick / 350.f, 255 * ((float)(520 - openingTick) / 170.f));
			 IMAGEMANAGER->findImage("오프닝_로고")->render(237, 189);
			 IMAGEMANAGER->findImage("오프닝_로고_빛남_1")->render(237, 189);
		 }
		 else if (510 <= openingTick && openingTick<520) {
			 IMAGEMANAGER->findImage("오프닝_로고_먼지")->DFpointrender(210, 114, 0, 0, openingTick / 350.f, 255 * ((float)(520 - openingTick) / 170.f));
			 IMAGEMANAGER->findImage("오프닝_로고")->render(237, 189);
			 IMAGEMANAGER->findImage("오프닝_로고_빛남_2")->render(237, 189);
		 }
		 else if (520 <= openingTick && openingTick<530) {
			 IMAGEMANAGER->findImage("오프닝_로고")->render(237, 189);
			 IMAGEMANAGER->findImage("오프닝_로고_빛남_3")->render(237, 189);
		 }
		 else if (530 <= openingTick) {
			 IMAGEMANAGER->findImage("오프닝_로고")->render(237, 189);
		 }
		 break;
	 case 1://등급보여주는것
		 IMAGEMANAGER->findImage("오프닝_배경")->render(0, 0);
		 if (900 < openingTick&&openingTick < 1000) {
			 IMAGEMANAGER->findImage("오프닝_로고")->DFpointrender(237, 189,0,0,1.f,255.f*((1000.f - (float)openingTick)/100.f));
			 //900~1000 -> 1 ~ 0
			 //1000 - openingtick / 100?
		 }
		 if (1000 <= openingTick && openingTick < 1030) {
			 IMAGEMANAGER->findImage("오프닝_붓_1")->DFpointrender(153, 208,0,0);
		 }
		 if (1030 <= openingTick && openingTick < 1060) {
			 IMAGEMANAGER->findImage("오프닝_붓_2")->DFpointrender(153, 208, 0, 0);
		 }
		 if (1060 <= openingTick && openingTick < 1090) {
			 IMAGEMANAGER->findImage("오프닝_붓_3")->DFpointrender(153, 208, 0, 0);
		 }
		 if (1090 <= openingTick && openingTick < 1120) {
			 IMAGEMANAGER->findImage("오프닝_붓_4")->DFpointrender(153, 208, 0, 0);
		 }
		 if (1060 < openingTick&&openingTick<1076) {
			 IMAGEMANAGER->findImage("오프닝_등급")->DFpointrender(0, 0, 0, 0,1.f,(255.f * ((1076.f - (float)openingTick)*16.f -1)));
		 }
		 if (1120 <= openingTick&&openingTick<=1800) {
			 IMAGEMANAGER->findImage("오프닝_붓_4")->DFpointrender(153, 208, 0, 0);
			 IMAGEMANAGER->findImage("오프닝_등급")->render();
		 }
		 if (1800 < openingTick&&openingTick < 2000) {
			 IMAGEMANAGER->findImage("오프닝_붓_4")->DFpointrender(153, 208, 0, 0,1.f,255.f*((2000.f - (float)openingTick))/200.f);
			 IMAGEMANAGER->findImage("오프닝_등급")->DFpointrender(0,0,0,0,1.f,255.f*((2000.f - (float)openingTick))/200.f);

		 }
		 break;
	 case 2://로딩창
		 IMAGEMANAGER->findImage("로딩_배경")->render(0,0);

		 IMAGEMANAGER->findImage("로딩_회전")->DFpointrotatedrender(378+23, 461+23, PI*((float)openingTick - 2000.f) / 100.f,23,23);
			 //IMAGEMANAGER->findImage("로딩_회전")->rotatedrender(378,461,)
		 break;
	 }
 }

 //이미지들 처리
 void mainGame::paint()
 {
	 pl->getCurMap()->render();
	 pl->getUI()->render();
 }

 //DC단에서 할 일 처리
 void mainGame::paintDC()
 {
	 pl->getCurMap()->renderdc();
	 pl->renderdc();
	 TIMEMANAGER->render(hdc);
 }

