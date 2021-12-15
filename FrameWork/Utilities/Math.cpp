#include "stdafx.h"
#include "Math.h"
//180�� = 1 * PI
//1�� = PI / 180;
//x�� = x * PI / 180;

//180 / PI = 1 ����
//x * 180 / PI = x ����
//1 ���� = 57
float const Math::PI = 3.14159284f;

float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}

float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}
//s -> 0.0f ~ 1.0f
float Math::FloatLerp(float from, float to, float s)
{
	float delta = (to - from) * s;

	return from + delta;
}

float Math::Random(float from, float to)
{
	//ex) from = -1, to = 1
	//temp -> 0 ~ 1 * 2 -> 0 ~ 2
	// -1 ~ 1
	float temp = (float)rand() / (float)RAND_MAX;
	temp = (to - from) * temp;
	return from + temp;
}

float Math::Clamp(float value, float from, float to)
{
	if (value < from)
		return from;
	if (value > to)
		return to;
	return value;
}
