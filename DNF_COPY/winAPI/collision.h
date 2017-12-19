#pragma once

namespace Util {
	typedef struct Point {
		float x;
		float y;
		Point() :x(0.0f), y(0.0f) {}

		void move(float dx, float dy) {
			x += dx;
			y += dy;
		}
	}MYPOINT, *LPMYPOINT;

	typedef struct Circle {
		float x, y, r;

		Circle() :x(0.0f), y(0.0f), r(0.0f) {}
		Circle(float _x, float _y, float _r) :x(_x), y(_y), r(_r) {}

		void move(float dx, float dy) {
			x += dx;
			y += dy;
		}
		void set(float centerX, float centerY, float radius) {
			x = centerX;
			y = centerY;
			r = radius;
		}
		void setCenterPos(float X, float Y) {
			x = X;
			y = Y;
		}
		void render(HDC hdc) {
			int x1 = FLOAT_TO_INT(x);
			int y1 = FLOAT_TO_INT(y);
			int r1 = FLOAT_TO_INT(r);

			Ellipse(hdc, x1 - r1, y1 - r1, x1 + r1, y1 + r1);
		}
	}MYCIRCLE, *LPMYCIRCLE;

	typedef struct MYRECT {
		float left;
		float top;
		float right;
		float bottom;

		MYRECT() :left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
		MYRECT(float l, float t, float r, float b) :left(l), top(r), right(r), bottom(b){}

		void move(float dx, float dy) {
			left += dx;
			top += dy;
			right += dx;
			bottom += dy;
		}

		void set(float l, float t, float r, float b) {
			left = l;
			top = t;
			right = r;
			bottom = b;
		}
		void setLeftTopPos(float l, float t) {
			float width = getWidth();
			float height = getHeight();

			left = l;
			top = t;
			right = l + width;
			bottom = top + height;
		}
		void setCenterPos(float X, float Y) {
			float hW = getWidth() / .5f;
			float hH = getHeight() / .5f;
			left = X - hW;
			top = Y - hH;
			right = X + hW;
			bottom = Y + hH;
		}
		float getWidth() {
			return right - left;
		}
		float getHeight() {
			return bottom - top;
		}
		void render(HDC hdc) {
			Rectangle(hdc, FLOAT_TO_INT(left), FLOAT_TO_INT(top), FLOAT_TO_INT(right), FLOAT_TO_INT(bottom));
		}
	}MYRECT, *LPMYRECT;


	//rect - point 面倒眉农
	bool checkPointInRect(const RECT& rc, const POINT& pt);
	bool checkPointInRect(const RECT& rc, int x, int y);
	bool checkPointInRect(const MYRECT& rc, float x, float y);
	bool checkPointInRect(const MYRECT& rc, const MYPOINT& pt);

	//circle - point 面倒眉农
	bool checkPointCircle(float cX, float cY, float cR, const MYPOINT& pt);
	bool checkPointCircle(float cX, float cY, float cR, float x, float y);
	bool checkPointCircle(const MYCIRCLE& cir, float x, float y);
	bool checkPointCircle(const MYCIRCLE& cir, const MYPOINT& pt);;

	//rect - rect 面倒眉农
	bool isCollision(const MYRECT& r1, const MYRECT& r2);
	bool isCollision(const RECT& r1, const RECT& r2);

	//circle - circle 面倒眉农
	bool isCollision(const MYCIRCLE& c1, const MYCIRCLE& c2);

	//rect - circle 面倒眉农
	bool isCollision(const MYRECT& r, const MYCIRCLE& c);
	bool isCollision(const RECT& r, const MYCIRCLE& c);

	//何刁腮 第狼 贸府
	bool isCollisionReaction(const RECT& rcHold, RECT& rcMove);
	bool isCollisionReaction(const MYRECT& mrhold, MYRECT& mrmove);
	bool isCollisionReaction(const MYCIRCLE& chold,MYCIRCLE& cmove);


}
