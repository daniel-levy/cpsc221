#include "customColorPicker.h"
#define _USE_MATH_DEFINES
#include <math.h>

customColorPicker::customColorPicker(int centerX, int centerY)
{
	cX = centerX;
	cY = centerY;
}

HSLAPixel customColorPicker::operator()(int x, int y)
{
	int newX = x - cX;
	int newY = y - cY;
	
	double distance = sqrt(pow(newX, 2) + pow(newY, 2));
	HSLAPixel newPixel;
	
	if((int)distance % 3 == 0)
	{
		newPixel.h = (int) distance % 36 * 10;
		newPixel.s = 1.0;
		newPixel.l = 0.0;
		newPixel.a = 1.0;
	}
	else
	{
		newPixel.h = (int) distance % 36 * 10;
		newPixel.s = 1.0;
		newPixel.l = 0.5;
		newPixel.a = 1.0;
	}
	
	return newPixel;
}