/* Image.c */

#include "Image.h"

unsigned char GetPixelR(IMAGE *image, unsigned int x, unsigned int y)
{
	return *((image->R)+(x+(y*(image->Width))));
}
 
/* Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y)
{
	return *((image->G)+(x+(y*(image->Width))));
}

/* Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y)
{
	return *((image->B)+(x+(y*(image->Width))));
}
 
/* Set the color intensity of the Red channel of pixel (x, y) in image with value r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	*((image->R)+(x+(y*(image->Width)))) = r; 
}
 
/* Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	*((image->G)+(x+(y*(image->Width)))) = g;
}
 
/* Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
	*((image->B)+(x+(y*(image->Width)))) = b;
}
 
/* allocate the memory space for the image structure         */
/* and the memory spaces for the color intensity values.     */
/* return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image = NULL;
	image = malloc(sizeof(IMAGE));
	if(!image)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	
	image->Width = Width;
	image->Height = Height;
	image->R = (unsigned char *)malloc(Width*Height);
	if (!(image->R))
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	image->G = (unsigned char *)malloc(Width*Height);
	if (!(image->G))
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	image->B = (unsigned char *)malloc(Width*Height);
	if(!(image->B))
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	return image;
}
 
/* release the memory spaces for the pixel color intensity values */
/* deallocate all the memory spaces for the image                 */
void DeleteImage(IMAGE *image)
{
	free(image->R);
	free(image->G);
	free(image->B);
	free(image);
}


