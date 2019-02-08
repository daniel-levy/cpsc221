/**
 * @file gridColorPicker.h
 * Definition of a grid color picker.
 *
 */
#ifndef BUBBLECOLORPICKER_H
#define BUBBLECOLORPICKER_H

#include "colorPicker.h"

class bubblecolorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new colorPicker.
     *
     * @param fillColor Color for the border between cells of the grid.
     * @param gridSpacing Spacing between cells of the grid.
     */
    bubbleColorPicker(HSLAPixel bubbleColor, int radius, int distance);

    /**
     * Picks the color for pixel (x, y). If the x or y coordinate is a
     * multiple of the spacing, it will be filled with the fillColor.
     * otherwise, it will be filled with white.
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
	HSLAPixel bubbleColor;
	int radius, distance;
};

#endif
