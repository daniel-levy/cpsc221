#include "block.h"

//PA1 functions

/**
 * Returns the width of the current block
 *
 */
int Block::width() const{
	return this->data[0].size();
}
	
	
/**
 * Returns the height of the current block
 *
 */
int Block::height() const{
	return this->data.size(); 
}


/**
 * From im, grabs the vertical strip of pixels whose upper left corner is 
 * at position (column,0) and whose width is width.
 *
 */
void Block::build(PNG &im, int column, int width){
	
	int imHeight = im.height();	
	this->data.resize(imHeight);	
	
	for(int i = 0; i < imHeight; i++){
		this->data[i].resize(width);
	}
	
	for(int i = 0; i < imHeight; i++){
		for(int j = column; j < (column + width); j++){
			HSLAPixel *pixel = im.getPixel(j,i);			
			this->data[i][(j-column)] = *pixel;
		}
	}
}

	 
/**
 * Draws the current block at position (column,0) in im.
 *
 */
void Block::render(PNG & im, int column) const{
	for(int i = 0; i < this->height(); i++){
		for(int j = column; j < (column + this->width()); j++){
			HSLAPixel * pixel = im.getPixel(j,i);
			*pixel= this->data[i][j-column];
		}
	}
}
 
 
 /**
 * This function changes the saturation of every pixel in the block to 0, 
 * which removes the color, leaving grey.
 *
 */
void Block::greyscale(){
	for(int i = 0; i < this->height(); i++){
		for(int j = 0; j < this->width(); j++){
			HSLAPixel pixel = this->data[i][j];
			pixel.s = 0;
			this->data[i][j] = pixel;
		}
	}
}