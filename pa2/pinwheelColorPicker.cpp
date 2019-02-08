#include "pinwheelColorPicker.h"
#define _USE_MATH_DEFINES
#include <math.h>

pinwheelColorPicker::pinwheelColorPicker(HSLAPixel pinwheelColor1, HSLAPixel pinwheelColor2, 
										 int centerX, int centerY)
{
	color1 = pinwheelColor1;
	color2 = pinwheelColor2;
	cX = centerX;
	cY = centerY;
}

HSLAPixel pinwheelColorPicker::operator()(int x, int y)
{
	int newX = x - cX;
	int newY = y - cY;
	//cX++;
	//cY++;
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
	
	/*if((newX >=0 && newY >= 0) || (newX <= 0 && newY <= 0))
	{
		newPixel.h = (int) distance % 36 * 10;
		newPixel.s = 1.0;
		newPixel.l = 0.5;
		newPixel.a = 1.0;
		return newPixel;
	}
	else 
	{
		newPixel.h = 360 - ((int) distance % 36 * 10);
		newPixel.s = 1.0;
		newPixel.l = 0.5;
		newPixel.a = 1.0;
		return newPixel;	
	}*/
	
	
	/*if(newX == 0){
		newPixel.h = ;
		newPixel.s = 1.0;
		newPixel.l = 0.5;
		newPixel.a = 1.0;
		return newPixel;
	}
	
	int result = atan(newY / newX) * 180 / M_PI;
	
	if((result <= 45 && result >= 0) || (result >= 90 && result <= 135))
	{
		newPixel.h = color1.h;
		newPixel.s = 1.0;
		newPixel.l = 0.5;
		newPixel.a = 1.0;
	}
	else
	{
		newPixel.h = color2.h;
		newPixel.s = 1.0;
		newPixel.l = 0.5;
		newPixel.a = 1.0;
	}*/
	//return newPixel;
}