/**
 * @file gridColorPicker.h
 * Definition of a grid color picker.
 *
 */
#ifndef PINWHEELCOLORPICKER_H
#define PINWHEELCOLORPICKER_H

#include "colorPicker.h"
#include <math.h>

class pinwheelColorPicker : public colorPicker
{
  public:

    pinwheelColorPicker(HSLAPixel pinwheelColor1, HSLAPixel pinwheelColor2, 
						int centerX, int centerY);
	
    virtual HSLAPixel operator()(int x, int y);

  private:
	HSLAPixel color1, color2;
	int cX, cY;
};

#endif
