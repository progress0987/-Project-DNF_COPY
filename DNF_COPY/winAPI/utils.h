#pragma once

//버전 낮은 사람들을 위한 cMath 라이브러리 추가
#include <cmath>

#define DEG_TO_RAD 0.017435f //디그리 1도(라디안값)
#define PI 3.141592654f
#define PI2 (PI*2.f)

#define PI_2		(PI/2.f)
#define PI_4		float(PI/4.0f)
#define PI_8		float(PI/8.0f)
#define PI_16		float(PI/16.0f)
#define PI_32		float(PI/32.0f)

#define FLOAT_TO_INT(f1) static_cast<int>(f1)
#define FLOAT_EPSILON 0.001f // 실수에서 가장 작은 단위

namespace Util {
	//거리
	float getDistance(float startX,float startY, float endX, float endY);
	//각도
	float getAngle(float x1, float y1, float x2, float y2);
}


