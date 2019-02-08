/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"
#include "animation.h"
#include <utility>
#include <cmath>
#include <vector>

//DFS
animation filler::fillSolidDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    solidColorPicker a(fillColor);
	animation anim;
    anim = filler::fill<Stack>(img, x, y, a, tolerance, frameFreq);
	return anim;
}

animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    gridColorPicker a(gridColor, gridSpacing);
	animation anim;
    anim = filler::fill<Stack>(img, x, y, a, tolerance, frameFreq);
	return anim;
}

animation filler::fillGradientDFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    gradientColorPicker a(fadeColor1, fadeColor2, radius, x, y);
	animation anim;
    anim = filler::fill<Stack>(img, x, y, a, tolerance, frameFreq);
	return anim;
}

/*animation filler::fillRainDFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    animation anim;
    anim = filler::fill<Stack>(img, x, y, a, tolerance, frameFreq);
	return anim;
}*/

/*animation filler::fillCustomDFS(PNG& img, int x, int y, 
									double tolerance, int frameFreq)
{
	customColorPicker a(x, y);
	animation anim;
    anim = filler::fill<Stack>(img, x, y, a, tolerance, frameFreq);
	return anim;
}*/

//BFS
animation filler::fillSolidBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                 double tolerance, int frameFreq)
{
    solidColorPicker a(fillColor);
    animation anim;
    anim = filler::fill<Queue>(img, x, y, a, tolerance, frameFreq);
	return anim;
}

animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel gridColor,
                                int gridSpacing, double tolerance, int frameFreq)
{
    gridColorPicker a(gridColor, gridSpacing);
    animation anim;
    anim = filler::fill<Queue>(img, x, y, a, tolerance, frameFreq);
	return anim;
}

animation filler::fillGradientBFS(PNG& img, int x, int y,
                                    HSLAPixel fadeColor1, HSLAPixel fadeColor2,
                                    int radius, double tolerance, int frameFreq)
{
    gradientColorPicker a(fadeColor1, fadeColor2, radius, x, y);
    animation anim;
    anim = filler::fill<Queue>(img, x, y, a, tolerance, frameFreq);
	return anim;
}
/*animation filler::fillRainBFS(PNG& img, int x, int y,
                                    long double freq, double tolerance, int frameFreq)
{
    rainbowColorPicker a(freq);
    animation anim;
    anim = filler::fill<Queue>(img, x, y, a, tolerance, frameFreq);
	return anim;
}*/

/*animation filler::fillCustomBFS(PNG& img, int x, int y, 
									double tolerance, int frameFreq)
{

	customColorPicker a(x, y);
	animation anim;
    anim = filler::fill<Queue>(img, x, y, a, tolerance, frameFreq);
	return anim;
}*/

//FILL
template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{

	int freqCount = 0;
	int imageHeight = img.height();
	int imageWidth = img.width();
	
	HSLAPixel *origin = new HSLAPixel();
	HSLAPixel *originalPixel = img.getPixel(x, y);
	animation *finalAnimation = new animation();

	filler::setPixel(originalPixel, origin);

	OrderingStructure<pair<int,int>> orderingStructure;
	vector<vector<bool>> isPixelProcessed(imageWidth,vector<bool>(imageHeight));

	for(unsigned int i = 0; i < img.width(); i++){
		for(unsigned int j = 0; j < img.height(); j++){
			isPixelProcessed[i][j] = false;
		}
	}
	orderingStructure.add(make_pair(x,y));
	isPixelProcessed[x][y] = true;

	HSLAPixel newPixel = fillColor.operator()(x,y);
	HSLAPixel *pixel = img.getPixel(x,y);
	
	filler::setPixel(&newPixel, pixel);
	
	freqCount = 1;
	
	if(freqCount % frameFreq == 0){
		finalAnimation->addFrame(img);
	}

	while(orderingStructure.isEmpty() == false){
		pair<int,int> currentPair = orderingStructure.remove();
		int newX;
		int newY;

		if(currentPair.first + 1 < imageWidth){
			if(isPixelProcessed[currentPair.first + 1][currentPair.second] == false){
				filler::fillHelper(isPixelProcessed, currentPair.first + 1, currentPair.second, pixel, origin,
							img, fillColor, tolerance, freqCount, orderingStructure);
				
				if(freqCount % frameFreq == 0){
					finalAnimation->addFrame(img);
				}
			}
		}
		
		if(currentPair.second + 1 < imageHeight){
			if(isPixelProcessed[currentPair.first][currentPair.second + 1] == false){
				filler::fillHelper(isPixelProcessed, currentPair.first, currentPair.second + 1, pixel, origin,
							img, fillColor, tolerance, freqCount, orderingStructure);
				
				if(freqCount % frameFreq == 0){
					finalAnimation->addFrame(img);
				}
			}
		}
		
		if(currentPair.first - 1 >= 0 ){
			if(isPixelProcessed[currentPair.first - 1][currentPair.second] == false){
				filler::fillHelper(isPixelProcessed, currentPair.first - 1, currentPair.second, pixel, origin,
							img, fillColor, tolerance, freqCount, orderingStructure);
				
				if(freqCount % frameFreq == 0){
					finalAnimation->addFrame(img);
				}
			}
		}
		
		if(currentPair.second - 1 >= 0){
			if(isPixelProcessed[currentPair.first][currentPair.second - 1] == false){
				filler::fillHelper(isPixelProcessed, currentPair.first, currentPair.second - 1, pixel, origin,
							img, fillColor, tolerance, freqCount, orderingStructure);
				
				if(freqCount % frameFreq == 0){
					finalAnimation->addFrame(img);
				}
			}
		}
	}

	finalAnimation->addFrame(img);
	return *finalAnimation;
	
} 

void filler::fillHelper(vector<vector<bool>> &isPixelProcessed, int first, int second, HSLAPixel *pixel, HSLAPixel *origin,
						PNG& img, colorPicker& fillColor, double tolerance, int &freqCount, OrderingStructure<pair<int,int>> &orderingStructure)
{							
	pixel = img.getPixel(first, second);

	if(origin->dist(*pixel) <= tolerance){
		isPixelProcessed[first][second] = true;
		HSLAPixel newPixel = fillColor.operator()(first, second);
		
		filler::setPixel(&newPixel, pixel);
		orderingStructure.add(make_pair(first, second));
		freqCount++;
	}
}

void filler::setPixel(HSLAPixel *from, HSLAPixel *to){
	to->h = from->h;
	to->s = from->s;
	to->l = from->l;
	to->a = from->a;
}
