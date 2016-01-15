/* DIPs.c */

#include "DIPs.h"

/* Black and White */
IMAGE *BlackNWhite(IMAGE *image)
{
	assert(image);

	int x, y;
	unsigned int tmpR, tmpG, tmpB;
	unsigned char average;

	for (y = 0; y < (image->Height); y++) 
	{
		for (x = 0; x < (image->Width); x++) 
		{
			tmpR = GetPixelR(image, x, y);
			tmpG = GetPixelG(image, x, y);
			tmpB = GetPixelB(image, x, y);

			average = (tmpR + tmpG + tmpB)/3;
	
			SetPixelR(image, x, y, average);
			SetPixelG(image, x, y, average);
			SetPixelB(image, x, y, average);
		}
	}
	assert(image);
	return image;
}


/* Flip Image Vertically */
IMAGE *VFlip(IMAGE *image)
{
	assert(image);	

	int x, y;
	unsigned char r, g, b;
    
	for (y = 0; y < (image->Height)/2; y++) 
	{
		for (x = 0; x < (image->Width); x++) 
		{
			r = GetPixelR(image, x, ((image->Height)-1-y));
			g = GetPixelG(image, x, ((image->Height)-1-y));
			b = GetPixelB(image, x, ((image->Height)-1-y));
            
			SetPixelR(image, x, ((image->Height)-1-y), GetPixelR(image, x, y));
			SetPixelG(image, x, ((image->Height)-1-y), GetPixelG(image, x, y));
			SetPixelB(image, x, ((image->Height)-1-y), GetPixelB(image, x, y));
            
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	assert(image);
	return image;
}


/* Mirror Image Horizontally */
IMAGE *HMirror(IMAGE *image)
{
	assert(image);

	int x, y;

	for (y = 0; y < (image->Height); y++) 
	{
		for (x = 0; x < (image->Width) / 2; x++) 
		{
			SetPixelR(image, x, y, GetPixelR(image, (image->Width)-1-x, y));
			SetPixelG(image, x, y, GetPixelG(image, (image->Width)-1-x, y));
			SetPixelB(image, x, y, GetPixelB(image, (image->Width)-1-x, y));
		}
	}
	assert(image);
	return image;
}

/* Color Filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
	assert(image);	

	int x, y; 
	int temp; 		
	for (y=0; y<(image->Height); y++)
	{
		for (x=0; x<(image->Width); x++)
		{
			if ((GetPixelR(image, x, y) < (target_r + threshold)) && (GetPixelR(image, x, y) > (target_r - threshold)) && (GetPixelG(image, x, y) < (target_g + threshold)) && (GetPixelG(image, x, y) > (target_g - threshold)) && (GetPixelB(image, x, y) < (target_b + threshold)) && (GetPixelB(image, x, y) > (target_b - threshold)))
			{
				temp = replace_r * GetPixelR(image, x, y);
				if (temp > 255)
					SetPixelR(image, x, y, 255);
				else if (temp < 0)
					SetPixelR(image, x, y, 0);
				else
					SetPixelR(image, x, y, temp);

				temp = replace_g * GetPixelG(image, x, y);
                                if (temp > 255)
                                        SetPixelG(image, x, y, 255);
                                else if (temp < 0)
                                        SetPixelG(image, x, y, 0);
                                else
                                        SetPixelG(image, x, y, temp);
                                 
				temp = replace_b * GetPixelB(image, x, y);
                                if (temp > 255)
                                        SetPixelB(image, x, y, 255);
                                else if (temp < 0)
                                        SetPixelB(image, x, y, 0);
                                else
                                        SetPixelB(image, x, y, temp);
                                 
			}
		}
	}
	assert(image);
	return image;
}


/* Sketch Edges of the Image */
IMAGE *Edge(IMAGE *image)
{
	assert(image);	

	int x, y, m, n, a, b;
	int tmpR = 0;
	int tmpG = 0;
	int tmpB = 0;

	IMAGE *temp_image = NULL;
	temp_image = CreateImage((image->Width), (image->Height));
	assert(temp_image);	

	for (y = 0; y < (image->Height); y++)
	{
		for (x = 0; x < (image->Width); x++) 
		{
			SetPixelR(temp_image, x, y, GetPixelR(image, x, y));
			SetPixelG(temp_image, x, y, GetPixelG(image, x, y));
			SetPixelB(temp_image, x, y, GetPixelB(image, x, y));
		}
	}

	for (y = 0; y < (image->Height); y++)
	{
		for (x = 0; x < (image->Width); x++) 
		{
			for (n = -1; n <= 1; n++)
			{
				for (m = -1; m <= 1; m++) 
				{
					a = x + m;
					b = y + n;
					if (a > (image->Width) - 1)
						a = (image->Width) - 1;
					if (a < 0)
						a = 0;

					if (b > (image->Height) - 1)
						b = (image->Height) - 1;
			
					if (b < 0)
						b = 0;

					if ((n==0)&&(m==0))
					{
						tmpR += 8*GetPixelR(temp_image, a, b); 
						tmpG += 8*GetPixelG(temp_image, a, b); 
						tmpB += 8*GetPixelB(temp_image, a, b); 
					}
					else
					{
						tmpR -= GetPixelR(temp_image, a, b); 
						tmpG -= GetPixelG(temp_image, a, b); 
						tmpB -= GetPixelB(temp_image, a, b); 
					}
				}
			}

				SetPixelR(image, x, y, ((tmpR>255)? 255: (tmpR<0)? 0: tmpR));
				SetPixelG(image, x, y, ((tmpG>255)? 255: (tmpG<0)? 0: tmpG));
				SetPixelB(image, x, y, ((tmpB>255)? 255: (tmpB<0)? 0: tmpB));
		
				tmpR = tmpG = tmpB = 0; 			
		}
	}
	DeleteImage(temp_image);
	assert(image);
	return image;
}


/*Shuffle the image*/
IMAGE *Shuffle(IMAGE *image)
{
	assert(image);

	int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width = (image->Width)/SHUFF_WIDTH_DIV;
	int block_height = (image->Height)/SHUFF_HEIGHT_DIV;

	int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
	int i, j;
	

	srand(time(NULL));
	/* Initialize block markers to not done (-1) */
	for (i = 0; i < SHUFF_WIDTH_DIV; i++) 
	{
		for (j = 0; j< SHUFF_HEIGHT_DIV; j++) 
		{
			 block[i][j]= -1;
		}
	}

	while (block_cnt > 0) 
	{
		/* Generate a random pair of blocks */
		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width = rand() % SHUFF_WIDTH_DIV;
		int src_height = rand() % SHUFF_HEIGHT_DIV;
		int src_width = rand() % SHUFF_WIDTH_DIV;

		/* Check if these blocks are already swaped, if not swap blocks */
		if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) 
		{
			/* Swap blocks */
			for (i = 0; i < block_height; i++) 
			{
				/* Init src and dest height offset */
				int h_dest = ((dest_height * block_height) + i) % (image->Height);
				int h_src  = ((src_height * block_height) + i) % (image->Height); 
				for (j = 0; j < block_width; j++) 
				{
					int temp;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % (image->Width); 
					int w_dest = ((dest_width * block_width) + j) % (image->Width);

					temp = GetPixelR(image, w_dest, h_dest);
					SetPixelR(image, w_dest, h_dest, GetPixelR(image, w_src, h_src));
					SetPixelR(image, w_src, h_src, temp);
					
					temp = GetPixelG(image, w_dest, h_dest);
                                        SetPixelG(image, w_dest, h_dest, GetPixelG(image, w_src, h_src));
                                        SetPixelG(image, w_src, h_src, temp);

					temp = GetPixelB(image, w_dest, h_dest);
                                        SetPixelB(image, w_dest, h_dest, GetPixelB(image, w_src, h_src));
                                        SetPixelB(image, w_src, h_src, temp);	
				}
			}
			/* Set marker as done */
			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}
		
	}
	assert(image);
	return image;
}


/* EOF DIPs.c */
