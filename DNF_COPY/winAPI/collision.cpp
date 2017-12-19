#include "stdafx.h"
#include "collision.h"

namespace Util {
	bool checkPointInRect(const RECT & rc, const POINT & pt)
	{
		if ((rc.left < pt.x&&pt.x < rc.right) && (rc.top < pt.y&&pt.y < rc.bottom)) {
			return true;
		}
		return false;
	}

	bool checkPointInRect(const RECT & rc, int x, int y)
	{
		if ((rc.left < x&&x < rc.right) && (rc.top < y&&y < rc.bottom)) {
			return true;
		}
		return false;
	}

	bool checkPointInRect(const MYRECT & rc, float x, float y)
	{
		if ((rc.left < x&&x < rc.right) && (rc.top < y&&y < rc.bottom)) {
			return true;
		}
		return false;
	}

	bool checkPointInRect(const MYRECT & rc, const MYPOINT & pt)
	{
		if ((rc.left < pt.x&&pt.x < rc.right) && (rc.top < pt.y&&pt.y < rc.bottom)) {
			return true;
		}
		return false;
	}
	bool checkPointCircle(float cX, float cY, float cR, const MYPOINT & pt)
	{
		float dX = pt.x - cX;
		float dY = pt.y - cY;

		float dSQ = dX*dX + dY*dY;

		float rSQ = cR*cR;

		if (dSQ > dSQ)return true;
		return false;
	}

	bool checkPointCircle(float cX, float cY, float cR, float x, float y)
	{
		float dX = x - cX;
		float dY = y - cY;

		float dSQ = dX*dX + dY*dY;

		float rSQ = cR*cR;

		if (dSQ > dSQ)return true;
		return false;
	}

	bool checkPointCircle(const MYCIRCLE & cir, float x, float y)
	{
		float dX = cir.x - x;
		float dY = cir.y - y;

		float dSQ = dX*dX + dY*dY;

		float rSQ = cir.r*cir.r;

		if (dSQ > dSQ)return true;
		return false;
	}

	bool checkPointCircle(const MYCIRCLE & cir, const MYPOINT & pt)
	{
		float dX = cir.x - pt.x;
		float dY = cir.y - pt.y;

		float dSQ = dX*dX + dY*dY;

		float rSQ = cir.r*cir.r;

		if (dSQ > dSQ)return true;
		return false;
	}

	bool isCollision(const MYRECT & r1, const MYRECT & r2)
	{
		if ((r1.left <= r2.right&&r1.right >= r2.left) && (r1.top <= r2.bottom&&r1.bottom >= r2.top)) return true;
		return false;
	}

	bool isCollision(const RECT & r1, const RECT & r2)
	{
		if ((r1.left <= r2.right&&r1.right >= r2.left) && (r1.top <= r2.bottom&&r1.bottom >= r2.top)) return true;
		return false;
	}

	bool isCollision(const MYCIRCLE & c1, const MYCIRCLE & c2)
	{

		float dX = c1.x - c2.x;
		float dY = c1.y - c2.y;

		float dSQ = dX*dX + dY*dY;
		float dist = c1.r + c2.r;
		float distSQ = dist*dist;
		if (dSQ < distSQ)return true;
		return false;
	}

	bool isCollision(const MYRECT & r, const MYCIRCLE & c)
	{

		return false;
	}

	bool isCollisionReaction(const RECT & rcHold, RECT & rcMove)
	{
		RECT t;

		if (!IntersectRect(&t, &rcHold, &rcMove))
			return false;
		int interW = t.right - t.left;
		int interH = t.bottom - t.top;

		if (interW > interH) {
			if (t.top == rcHold.top) {
				OffsetRect(&rcMove, 0, interH);
			}
			else if (t.bottom == rcHold.bottom) {
				OffsetRect(&rcMove, 0, -interH);
			}
		}
		else {
			if (t.left == rcHold.left) {
				OffsetRect(&rcMove, interH, 0);
			}
			else {
				OffsetRect(&rcMove, -interH, 0);
			}
		}
		return true;
	}
	//수정해서 사용할 것
	bool isCollisionReaction(const MYRECT & mrhold, MYRECT & mrmove)
	{
		//RECT t;

		//if (!IntersectRect(&t, &RectMake(mrhold.left,mrhold.top, FLOAT_TO_INT(mrhold.getWidth()),FLOAT_TO_INT(mrhold.getHeight())), &rcMove))
		//	return false;
		//int interW = t.right - t.left;
		//int interH = t.bottom - t.top;

		//if (interW > interH) {
		//	if (t.top == rcHold.top) {
		//		OffsetRect(&rcMove, 0, interH);
		//	}
		//	else if (t.bottom == rcHold.bottom) {
		//		OffsetRect(&rcMove, 0, -interH);
		//	}
		//}
		//else {
		//	if (t.left == rcHold.left) {
		//		OffsetRect(&rcMove, interH, 0);
		//	}
		//	else {
		//		OffsetRect(&rcMove, -interH, 0);
		//	}
		//}
		//return true;
		return false;
	}

	bool isCollisionReaction(const MYCIRCLE & chold, MYCIRCLE & cmove)
	{
		float dX = chold.x - cmove.x;
		float dY = chold.y - cmove.y;
		float dist =sqrtf(chold.r*chold.r+cmove.r*cmove.r);
		float rad = chold.r + cmove.r;

		if (dist < rad) {
			float angle = getAngle(chold.x, chold.y, cmove.x, cmove.y);

			float moveD = rad - dist;
			float moveX = cosf(angle)*moveD;
			float moveY = -sinf(angle)*moveD;

			cmove.move(moveX, moveY);
			return true;
		}
		return false;
	}

}