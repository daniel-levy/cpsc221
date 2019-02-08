/**
 * @file gridColorPicker.h
 * Definition of a grid color picker.
 *
 */
#ifndef PINWHEELCOLORPICKER_H
#define PINWHEELCOLORPICKER_H

#include "colorPicker.h"
#include <math.h>

class customColorPicker : public colorPicker
{
  public:

    customColorPicker(int centerX, int centerY);
	
    virtual HSLAPixel operator()(int x, int y);

  private:
	int cX, cY;
};

#endif
