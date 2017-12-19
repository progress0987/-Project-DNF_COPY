#include "stdafx.h"
#include "utils.h"

namespace Util {
	//거리
	float getDistance(float startX, float startY, float endX, float endY) {
		float x = (endX - startX) / 2;
		float y = (endY - startY) / 2;
		return sqrtf(x*x + y*y);
	}
	//각도
	float getAngle(float x1, float y1, float x2, float y2) {
		float x = x2 - x1;
		float y = y2 - y1;
		float dist = sqrtf(x*x + y*y);
		//탄젠트 각도
		float angle = atanf(y / x);

		//코사인쓸때사용
		/*if(y2 > y1) {
			angle = PI * 2 - angle;
		}*/
		return angle;
	}
}
