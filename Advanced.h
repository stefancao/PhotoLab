/* Advanced.h */

#ifndef ADVANCED_H
#define ADVANCED_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Constants.h"
#include "Image.h"

#define MAX_COLOR 16

/*Posterize  Image*/
IMAGE *Posterize(IMAGE *image, unsigned int pbits);

/* Add noise to image */
IMAGE *FillLight(IMAGE *image, int number, int lightWidth);

/* Overlay with another image */
IMAGE *Overlay(char fname[SLEN], IMAGE *image, int x_offset, int y_offset);

/* Perform Cut Past operations on the image */
IMAGE *CutPaste(IMAGE *image, unsigned int startX, unsigned int startY, unsigned int x_width, unsigned int y_width, unsigned int pasteNumber);

/* Resize */
IMAGE *Resize(unsigned int percentage, IMAGE *image);

/* Rotate 90 degrees clockwise */
IMAGE *Rotate(IMAGE *image);

/* Mandelbrot */
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);

/* BONUS : Add outer border */
IMAGE *AddOuterBorder(IMAGE *image, char color[SLEN], int border_width);

#endif



