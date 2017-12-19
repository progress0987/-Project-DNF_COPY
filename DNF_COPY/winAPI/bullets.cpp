#include "stdafx.h"
//#include "bullets.h"
//
//missile::missile()
//{
//}
//
//
//missile::~missile()
//{
//}
////여기서 미사일 초기화 -> 알아서 이미지로 초기화하기
//HRESULT missile::init(int bulletMax, float range, D2DImage* img)
//{
//	//총알의 사거리
//	this->range = range;
//	//총알최대갯수만큼 생성
//	for (int i = 0; i < bulletMax; i++) {
//		//총알 초기화
//		Bullet bul;
//		ZeroMemory(&bul, sizeof(Bullet));
//		bul.bulletImg = new D2DImage;
//		bul.bulletImg = img;
//		//총알속도(바꿔야함
//		bul.speed = 5.0f;
//		bul.fired = false;
//		BulletList.push_back(bul);
//	}
//
//	return S_OK;
//}
//
//void missile::release()
//{
//}
//
//void missile::update()
//{
//	move();
//}
//
//void missile::render()
//{
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end(); BulletListIter++) {
//		if (BulletListIter->fired) {
//			BulletListIter->bulletImg->render(hdc, BulletListIter->rc.left, BulletListIter->rc.top, 0, 0, BulletListIter->bulletImg->getWidth(), BulletListIter->bulletImg->getHeight());
//		}
//	}
//}
//
//void missile::fire(float x, float y)
//{
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end(); BulletListIter++) {
//		if (!BulletListIter->fired) {
//			BulletListIter->fired = true;
//			BulletListIter->x = BulletListIter->fireX = x;
//			BulletListIter->y = BulletListIter->fireY = y;
//			BulletListIter->rc = RectMakeCenter(BulletListIter->x, BulletListIter->y, BulletListIter->bulletImg->getWidth(), BulletListIter->bulletImg->getHeight());
//			break;
//		}
//	}
//}
//
//void missile::move()
//{
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end(); BulletListIter++) {
//		if (BulletListIter->fired) {
//			//방향설정해줄것
//			BulletListIter->y -= BulletListIter->speed;
//			BulletListIter->rc = RectMakeCenter(BulletListIter->x, BulletListIter->y, BulletListIter->bulletImg->getWidth(), BulletListIter->bulletImg->getHeight());
//		}
//		if (range < getDistance(BulletListIter->x, BulletListIter->y, BulletListIter->fireX, BulletListIter->fireY)) {
//			BulletListIter->fired = false;
//		}
//	}
//}
//
//instanceMissile::instanceMissile()
//{
//}
//
//instanceMissile::~instanceMissile()
//{
//}
//
//HRESULT instanceMissile::init(int bulletMax, float range)
//{
//	this->bulletMax = bulletMax;
//	this->range = range;
//	return S_OK;
//}
//
//void instanceMissile::release()
//{
//}
//
//void instanceMissile::update()
//{
//	move();
//}
//
//void instanceMissile::render()
//{
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end(); BulletListIter++) {
//		if (BulletListIter->fired) {
//			//수정할것
//			BulletListIter->bulletImg->frameRender(hdc, BulletListIter->rc.left, BulletListIter->rc.top, BulletListIter->bulletImg->getFrameX(), 0);
//			//아마도 미사일 애니메이션 프레임을 정하는듯
//			BulletListIter->count++;
//			//프레임애니메이션
//			if (BulletListIter->count % 5 == 0) {
//				BulletListIter->bulletImg->setFrameX(BulletListIter->bulletImg->getFrameX() + 1);
//				//프레임애니메이션 원복
//				if (BulletListIter->bulletImg->getFrameX() > BulletListIter->bulletImg->getMaxFrameX()) {
//					BulletListIter->bulletImg->setFrameX(0);
//				}
//				//왜 초기화하는지 모르겠음
//				BulletListIter->count = 0;
//			}
//		}
//	}
//}
//
//void instanceMissile::removeMissile(int arrnum)
//{
//	//이미지를 먼저 날려야 안터짐
//	BulletList[arrnum].bulletImg->release();
//	BulletList.erase(BulletList.begin() + arrnum);
//}
//
//void instanceMissile::fire(float x, float y, D2DImage * img)
//{
//	Bullet bul;
//	ZeroMemory(&bul, sizeof(Bullet));
//	bul.bulletImg = img;
//	//총알 속도,좌표등등설정
//	bul.x = bul.fireX = x;
//	bul.y = bul.fireY = y;
//	bul.rc = RectMakeCenter(bul.x, bul.y, bul.bulletImg->getFrameWidth(), bul.bulletImg->getFrameHeight());
//	BulletList.push_back(bul);
//}
//
//void instanceMissile::move()
//{
//	//방향에따라 움직이는거 설정해줘야함
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end();) {
//		//이동하는것 설정다시해야함(방향에따라)
//		BulletListIter->y = BulletListIter->speed;
//		BulletListIter->rc = RectMakeCenter(BulletListIter->x, BulletListIter->y, BulletListIter->bulletImg->getFrameWidth(), BulletListIter->bulletImg->getFrameHeight());
//		if (range < getDistance(BulletListIter->x, BulletListIter->y, BulletListIter->fireX, BulletListIter->fireY)) {
//			SAFE_DELETE(BulletListIter->bulletImg);
//			BulletListIter = BulletList.erase(BulletListIter);
//		}
//		else BulletListIter++;
//	}
//}
//
//classBullet::classBullet()
//{
//}
//
//classBullet::~classBullet()
//{
//}
//
//
//
//HRESULT classBullet::init(const char * imgName, int bulMax, float range)
//{
//	this->imgName = imgName;
//	this->bulletMax = bulMax;
//	this->range = range;
//	return S_OK;
//}
//
//void classBullet::release()
//{
//}
//
//void classBullet::update()
//{
//	move();
//}
//
//void classBullet::render()
//{
//	draw();
//}
//
//void classBullet::fire(float x, float y, float angle, float speed)
//{
//	//최대갯수보다 벡터가 커지면 생성불가
//	if (bulletMax < BulletList.size())return;
//	Bullet bul;
//	ZeroMemory(&bul, sizeof(Bullet));
//	bul.bulletImg = IMAGEMANAGER->findImage(imgName);
//	bul.speed = speed;
//	bul.radius = bul.bulletImg->getWidth() / 2;
//	bul.x = bul.fireX = x;
//	bul.y = bul.fireY = y;
//	bul.angle = angle;
//	bul.rc = RectMakeCenter(bul.x, bul.y, bul.bulletImg->getWidth(), bul.bulletImg->getHeight());
//	BulletList.push_back(bul);
//}
//
//void classBullet::move()
//{
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end(); ) {
//		BulletListIter->x += cosf(BulletListIter->angle)*BulletListIter->speed;
//		BulletListIter->y += (-sinf(BulletListIter->angle))*BulletListIter->speed;
//		BulletListIter->rc = RectMakeCenter(BulletListIter->x, BulletListIter->y, BulletListIter->bulletImg->getWidth(), BulletListIter->bulletImg->getHeight());
//
//		if (range < getDistance(BulletListIter->fireX, BulletListIter->fireY, BulletListIter->x, BulletListIter->y)) {
//			BulletListIter = BulletList.erase(BulletListIter);
//		}
//		else
//			BulletListIter++;
//	}
//}
//
//void classBullet::draw()
//{
//	for (BulletListIter = BulletList.begin(); BulletListIter != BulletList.end(); BulletListIter++) {
//		BulletListIter->bulletImg->render(hdc, BulletListIter->rc.left, BulletListIter->rc.top);
//	}
//}
//
//HRESULT missilePF::init(const char * imgName, int bulMax, float range)
//{
//	this->imgName = imgName;
//	this->bulletMax = bulMax;
//	this->range = range;
//
//	return S_OK;
//}
//
//void missilePF::release()
//{
//	Bullets.clear();
//}
//
//void missilePF::update()
//{
//	move();
//}
//
//void missilePF::render()
//{
//	draw();
//}
//
//void missilePF::fire(float x, float y, float angle, float speed)
//{
//	if (bulletMax < Bullets.size())return;
//	Bullet bul;
//	ZeroMemory(&bul, sizeof(Bullet));
//	bul.bulletImg = IMAGEMANAGER->findImage(imgName);
//	bul.angle = angle;
//	bul.speed = speed;
//	bul.radius = bul.bulletImg->getFrameWidth()/2;
//	bul.x = bul.fireX = x;
//	bul.y = bul.fireY = y;
//	bul.rc = RectMakeCenter(bul.x, bul.y, bul.bulletImg->getWidth(), bul.bulletImg->getHeight());
//	Bullets.push_back(bul);
//}
//
//void missilePF::move()
//{
//	float elapsedTime = TIMEMANAGER->getElapsedTime();
//	for (BulletIter = Bullets.begin(); BulletIter != Bullets.end();) {
//		BulletIter->x += cosf(BulletIter->angle)*BulletIter->speed*elapsedTime;
//		BulletIter->y += -sinf(BulletIter->angle)*BulletIter->speed*elapsedTime;
//
//		BulletIter->rc = RectMakeCenter(BulletIter->x, BulletIter->y, BulletIter->bulletImg->getFrameWidth(), BulletIter->bulletImg->getFrameHeight());
//
//		if (range < getDistance(BulletIter->fireX, BulletIter->fireY, BulletIter->x, BulletIter->y)) {
//			BulletIter = Bullets.erase(BulletIter);
//		}
//		else BulletIter++;
//	}
//}
//
//void missilePF::draw()
//{
//	int frame;
//	float angle;
//	for (BulletIter = Bullets.begin(); BulletIter != Bullets.end();) {
//		angle = BulletIter->angle + (PI / 16);
//		if (angle >= PI2) angle -= PI2;
//
//		frame = (angle / (PI / 8));
//
//		BulletIter->bulletImg->frameRender(hdc, BulletIter->rc.left, BulletIter->rc.top, frame, 0);
//	}
//}
//
//void missilePF::removeBullet(int arrNum)
//{
//	Bullets.erase(Bullets.begin() + arrNum);
//}
