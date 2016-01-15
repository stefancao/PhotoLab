/* Advanced.c */

#include "Advanced.h"


/* Posterization */
IMAGE *Posterize(IMAGE *image, unsigned int pbits)
{
	assert(image);

	unsigned char maskzero[8] = {0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
        unsigned char maskone[8]  = {0x0     , 0x1     , 0x3     , 0x7     , 0xf      , 0x1f     , 0x3f     , 0x7f     };
        int x, y;

        for(x = 0; x < (image->Width); x++)
        {
                for(y = 0; y < (image->Height); y++)
                {
			SetPixelR(image, x, y, (GetPixelR(image, x, y) & maskzero[pbits - 1]));
			SetPixelR(image, x, y, (GetPixelR(image, x, y) | maskone[pbits - 1]));

			SetPixelG(image, x, y, (GetPixelG(image, x, y) & maskzero[pbits - 1]));
			SetPixelG(image, x, y, (GetPixelG(image, x, y) | maskone[pbits - 1]));

			SetPixelB(image, x, y, (GetPixelB(image, x, y) & maskzero[pbits - 1]));
			SetPixelB(image, x, y, (GetPixelB(image, x, y) | maskone[pbits - 1]));

                }
        }
	assert(image);
	return image;
}


/* add noise to image */
IMAGE *FillLight(IMAGE *image, int number, int lightWidth)
{
	assert(image);	

	int x, y, i, h;
    	int colorChoice;	
    
  	srand(0);

    	for (i = 0; i < number; i++)
    	{
        	x = (rand()%((image->Width)-lightWidth)) + lightWidth/2;
        	y = (rand()%((image->Height)-lightWidth))+ lightWidth/2;
        
		colorChoice = (rand()%3)+1;

		int red_flag, blue_flag, green_flag;
		red_flag = blue_flag = green_flag = 0;
		if(colorChoice == 1)
			red_flag = 1;
		else if(colorChoice == 2)
			green_flag = 1;
		else 
			blue_flag = 1;
	
		for(h = -lightWidth/2; h < lightWidth/2; h++)
		{
			SetPixelR(image, x+h, y, 255*red_flag);
			SetPixelR(image, x, y+h, 255*red_flag);
			SetPixelR(image, x+h, y+h, 255*red_flag);	
			SetPixelR(image, x-h, y+h, 255*red_flag); 
			
			SetPixelG(image, x+h, y, 255*green_flag);
                        SetPixelG(image, x, y+h, 255*green_flag);
                        SetPixelG(image, x+h, y+h, 255*green_flag);
                        SetPixelG(image, x-h, y+h, 255*green_flag);		

			SetPixelB(image, x+h, y, 255*blue_flag);
                        SetPixelB(image, x, y+h, 255*blue_flag);
                        SetPixelB(image, x+h, y+h, 255*blue_flag);
                        SetPixelB(image, x-h, y+h, 255*blue_flag);		
		}
    	}
	assert(image);
	return image;
}


/* overlay with another image */
IMAGE *Overlay(char fname[SLEN], IMAGE *image, int x_offset, int y_offset)
{
	assert(image);	

	int x = 0, y = 0;
	
	IMAGE *overlay = NULL;

	/*read the second image */
	overlay = ReadImage(fname);
	assert(overlay);

	for (y = 0; y < (overlay->Height); y++)
		for (x = 0; x < (overlay->Width); x++)
		{
			if ((GetPixelR(overlay, x, y) < 250) && (GetPixelG(overlay, x, y) < 250) && (GetPixelB(overlay, x, y) < 250))
			{
				if((x+x_offset < (image->Width)) && (y + y_offset < (image->Height)))
				{
					SetPixelR(image, x+x_offset, y+y_offset, GetPixelR(overlay, x, y));
					SetPixelG(image, x+x_offset, y+y_offset, GetPixelG(overlay, x, y));
					SetPixelB(image, x+x_offset, y+y_offset, GetPixelB(overlay, x, y));
				}
			}
		}
	DeleteImage(overlay);
	assert(image);
	return image;
}


/* Perform Cut Paste operations on the image*/
IMAGE *CutPaste(IMAGE *image, unsigned int startX, unsigned int startY, unsigned int x_width, unsigned int y_width, unsigned int pasteNumber)
{
	assert(image);

	IMAGE *base = NULL;
	base = CreateImage(x_width, y_width);
	assert(base);	
	
	int x, y, n;
	for(x = startX; x < startX + x_width; x++)
	{
		for(y = startY; y < startY + y_width; y++)
		{
			SetPixelR(base, x-startX, y-startY, GetPixelR(image, x, y));
			SetPixelG(base, x-startX, y-startY, GetPixelG(image, x, y));
			SetPixelB(base, x-startX, y-startY, GetPixelB(image, x, y));
		}
	}

	for(n = 1;  n <= pasteNumber; n++)
	{
		unsigned int  pasteX, pasteY;
		#ifdef DEBUG
			switch(n)
			{
				case 1:
					pasteX = 341;	
					pasteY = 19;
					break;
				case 2:
					pasteX = 315;
					pasteY = 18;
					break;
				case 3:
					pasteX = 288;
					pasteY = 16;
					break;
				default:
					break;
			}
		#else
			printf("Please input start x and y coordinates for paste no %d:   ", n);
			scanf("%u %u", &pasteX, &pasteY);
		#endif /* DEBUG */
		
		for(x = 0; x < x_width; x++)
		{
			for(y = 0; y < y_width; y++)
			{
				SetPixelR(image, x+pasteX, y+pasteY, GetPixelR(base, x, y));
				SetPixelG(image, x+pasteX, y+pasteY, GetPixelG(base, x, y));
				SetPixelB(image, x+pasteX, y+pasteY, GetPixelB(base, x, y));

			}
		}
		
	}
	DeleteImage(base);
	assert(image);
	return image;	
}


/* Resize */
IMAGE *Resize(unsigned int percentage, IMAGE *image)
{
	assert(image);	

	int x, y, x1, y1, x2, y2;
	int i, j;
	int tmpR = 0;
	int tmpG = 0;
	int tmpB = 0;
	int avgR = 0;
	int avgG = 0;
	int avgB = 0;
	int count = 0;

	IMAGE *resize_image = NULL;
	resize_image = CreateImage((image->Width)*(percentage/100.00), (image->Height)*(percentage/100.00));
	assert(resize_image);

	if (percentage == 100)
	{
		for (y = 0; y < (image->Height); y++)
		{
			for (x = 0; x < (image->Width);	x++)
			{
				SetPixelR(resize_image, x, y, GetPixelR(image, x, y));
				SetPixelG(resize_image, x, y, GetPixelG(image, x, y));
				SetPixelB(resize_image, x, y, GetPixelB(image, x, y));
			}
		}
	}

	else if (percentage < 100)
	{
		for (y=0; y < (resize_image-> Height); y++)
		{
			for (x=0; x < (resize_image->Width); x++)
			{
				x1 = x/(percentage/100.00);
				y1 = y/(percentage/100.00);
				x2 = (x+1)/(percentage/100.00);
				y2 = (y+1)/(percentage/100.00);
				
				for (i = x1; i <= x2; i++)
				{
					if (x2 >= (image->Width))
					{
						break;
					}
					for (j = y1; j <= y2; j++)
					{
						if (y2 >= (image->Height))
						{
							break;
						}
						tmpR = tmpR + GetPixelR(image, i, j);
						tmpG = tmpG + GetPixelG(image, i, j);
						tmpB = tmpB + GetPixelB(image, i, j);
						count = count + 1;
					}
				}
				avgR = avgG = avgB = 0;
				if (count != 0)
				{
					avgR = tmpR/count;
					avgG = tmpG/count;
					avgB = tmpB/count;
				}

				SetPixelR(resize_image, x, y, avgR);
				SetPixelG(resize_image, x, y, avgG);
				SetPixelB(resize_image, x, y, avgB);
				
				count = 0;
				tmpR = tmpG = tmpB = 0;
			}
		}
	}

	else if (percentage > 100)
	{
		for (y=0; y < (image->Height); y++)
		{
			for (x=0; x < (image->Width); x++)
			{
				
				x1 = x*(percentage/100.00);
				y1 = y*(percentage/100.00);
				x2 = (x+1)*(percentage/100.00);
				y2 = (y+1)*(percentage/100.00);
			
				for (i = x1; i <= x2; i++)
				{
					if (x2 >= (resize_image->Width))
					{
						break;
					}
					for (j = y1; j <= y2; j++)
					{
						if (y2 >= (resize_image->Height))
						{
							break;
						}
						SetPixelR(resize_image, i, j, GetPixelR(image, x, y));	
						SetPixelG(resize_image, i, j, GetPixelG(image, x, y));
						SetPixelB(resize_image, i, j, GetPixelB(image, x, y));
					}
				}
			}
		}
	}
	DeleteImage(image);
	assert(resize_image);
	return resize_image;
	DeleteImage(resize_image);
}


/* Rotate 90 degrees clockwise */
IMAGE *Rotate(IMAGE *image)
{
	assert(image);	

	IMAGE *rotate_image = NULL;
	rotate_image = CreateImage(image->Height, image->Width);
	assert(rotate_image);	

	int x, y;
	int x2 = (rotate_image->Width);
	for (y = 0; y < (image->Height); y++)
	{
		x2--;
		int y2 = -1;
		for (x = 0; x < (image->Width); x++)
		{
			y2++;
			SetPixelR(rotate_image, x2, y2, GetPixelR(image, x, y));
			SetPixelG(rotate_image, x2, y2, GetPixelG(image, x, y));
			SetPixelB(rotate_image, x2, y2, GetPixelB(image, x, y));
		}
	}
	DeleteImage(image);
	assert(rotate_image);
	return rotate_image;
	DeleteImage(rotate_image);
}


/* Mandelbrot */
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration)
{
	IMAGE *mandel_brot = NULL;
	mandel_brot = CreateImage(W, H);
	assert(mandel_brot);	

	float x, y;
	float x0, y0;
	float  xtemp; 
	int iteration, color;
	int x1, y1;
	for (y1 = 0; y1 < (mandel_brot->Height); y1++)
	{
		for (x1 = 0; x1 < (mandel_brot->Width); x1++)
		{
			x0 = (((float)x1)/((float)(mandel_brot->Width)*3.5)) - 2.5;
			y0 = (((float)y1)/((float)(mandel_brot->Height)*2.0)) - 1.0;
			
			x = 0.0;
			y = 0.0;

			iteration = 0;

			while(x*x + y*y < 2*2 && iteration < max_iteration)
			{
				xtemp = x*x - y*y + x0;
				y = 2.0*x*y + y0;

				x = xtemp;
				iteration = iteration + 1;
			}
			color = iteration%16;

			const unsigned char palette[MAX_COLOR][3] = 
			{
				{0, 0, 0},		/* 0, black */
				{127, 0, 0},		/* 1, brown */
				{255, 0, 0},		/* 2, red */
				{255, 127, 0},		/* 3, orange */
				{255, 255, 0},		/* 4, yellow */
				{127, 255, 0}, 		/* 5, light green */
				{0, 255, 0},		/* 6, green */
				{0, 255, 127},		/* 7, blue green */
				{0, 255, 255}, 		/* 8, turquoise */
				{127, 255, 255},	/* 9, light blue */
				{255, 255, 255},	/* 10, white */
				{255, 127, 255},	/* 11, pink */
				{255, 0, 255},		/* 12, light pink */
				{127, 0, 255},		/* 13, purple */
				{0, 0, 255},		/* 14, blue */
				{0, 0, 127}		/* 15, dark blue */	
			};
				
			SetPixelR(mandel_brot, x1, y1, palette[color][1]);
			SetPixelG(mandel_brot, x1, y1, palette[color][2]);
			SetPixelB(mandel_brot, x1, y1, palette[color][3]);
		}
	}
	assert(mandel_brot);
	return mandel_brot;
	DeleteImage(mandel_brot);
}


/* BONUS : Add outer border */
IMAGE *AddOuterBorder(IMAGE *image, char color[SLEN], int border_width)
{
	assert(image);	

	IMAGE *border_image = NULL;
	border_image = CreateImage((image->Width)+(2*border_width), (image->Height)+(2*border_width));
	assert(border_image);	

	int x, y;
	int border_r = 0;
	int border_g = 0;
	int border_b = 0;

	if (!strcmp(color, "black"))
	{
		border_r = 0;
		border_g = 0;
 		border_b = 0;
	}
	else if (!strcmp(color, "white"))
	{
		border_r = 255;
		border_g = 255;
		border_b = 255;
	}
	else if (!strcmp(color, "red"))
	{
		border_r = 255;
		border_g = 0;
		border_b = 0;
	}
	else if (!strcmp(color, "green"))
	{
		border_r = 0;
		border_g = 255;
		border_b = 0;
	}
	else if (!strcmp(color, "blue"))
	{
		border_r = 0;
		border_g = 0;
		border_b = 255;
	}
	else if (!strcmp(color, "yellow"))
	{
		border_r = 255;
		border_g = 255;
		border_b = 0;
	}
	else if (!strcmp(color, "cyan"))
	{
		border_r = 0;
		border_g = 255;
		border_b = 255;
	}
	else if (!strcmp(color, "pink"))
	{
		border_r = 255;
		border_g = 192;
		border_b = 203;
	}
	else if (!strcmp(color, "orange"))
	{
		border_r = 255;
		border_g = 165;
		border_b = 0;
	}
	
	
	/* Add border */
	for (y = 0; y < (border_image->Height); y++)
	{		
		for (x = 0; x < (border_image->Width); x++)
		{
			if ((y < border_width) || (y >= (border_image->Height) - border_width) || (x < border_width) || (x >= (border_image->Width) - border_width))
			{
				SetPixelR(border_image, x, y, border_r);
				SetPixelG(border_image, x, y, border_g);
				SetPixelB(border_image, x, y, border_b);
			}
		}
	}
	/* Add the picture */
	for (y = 0; y < (image->Height); y++)
	{
		for (x = 0; x < (image-> Width); x++)
		{
			SetPixelR(border_image, x+border_width, y+border_width, GetPixelR(image, x, y));
			SetPixelG(border_image, x+border_width, y+border_width, GetPixelG(image, x, y));
			SetPixelB(border_image, x+border_width, y+border_width, GetPixelB(image, x, y));
		}
	}
	DeleteImage(image);
	assert(border_image);
	return border_image;
	DeleteImage(border_image);
}


/* EOF Advanced.c */
