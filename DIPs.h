/* DIPs.h */

#ifndef DIPS_H
#define DIPS_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Constants.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include <time.h>

/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image);

/* Add a border to the image */
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int border_width);

/* flip image vertically */
IMAGE *VFlip(IMAGE *image);

/* color filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int targer_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
IMAGE *Edge(IMAGE *image);

/* shuffle the image */
IMAGE *Shuffle(IMAGE *image);

#endif
