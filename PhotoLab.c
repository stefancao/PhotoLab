/* File: PhotoLab (Assignment 4) + Bonus Problem	*/
/* Name: Stefan Cao					*/
/* ID#: 79267250					*/
/* Course: EECS 22					*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Constants.h"
#include "Advanced.h"
#include "Image.h"

/* print a menu */
void PrintMenu();

/* Test all functions */
void AutoTest(IMAGE *image);

/* Main Function */
int main()
{
	IMAGE *image = NULL;		/* Defining and initialize a pointer */

	char sname[SLEN];	/* Defining name of operation file */	
	int choice = 0;		/* Variable for choosing operations */
	int error_return = 1;	/* For operation SaveImage that returns '0' if everything saved correctly */
	int FileNotRead = 1;
	int mandelbrot_done = 0;
	int x = 0;	

	while(x != -1)		/* Continue the loop/ program until user enters 18 which gives x a value of -1 */
	{
		#ifndef DEBUG		/* Print and scan if NOT DEBUG*/
		PrintMenu();		/* Call Print Menu function */
		scanf("%d", &choice);	/* Save input number into variable choice */
		#endif
		
		#ifdef DEBUG		/* Choose operation 17 if DEBUG */
		choice = 17;
		#endif

		if (choice == 1)	/* Loading the Image */
		{
			printf("Please input the file name to load: ");
			scanf("%s", sname);
			image = ReadImage(sname);
			printf("Image Read!\n");
			if (image == NULL)	/* If file not loaded sucessfully then do not change FileNotRead */
			{
			}
			else
			{
				FileNotRead = 0;	/* Value indicating File loaded */
			}
		}
		else if (choice == 2)	/* Saving the Image*/
		{			
			if ((FileNotRead != 0) && (mandelbrot_done != 1))	/* Check if a file is read! or mandelbrot is chosen */
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{
				error_return = SaveImage(sname, image);		/* If saved succesfully, SaveImage should return '0' */
				if (error_return != 0)	/* If not, print a warning message */
				{
					printf("Image could not be saved!\n");
				}
				printf("%s was saved sucessfully.\n", sname);
				printf("%s.jpg was stored for viewing. \n", sname);

				printf("If you want to make another operation, please load image (1) again before doing so. \n");
			}
		}
		else if (choice == 3)	/* Change image to Black and White*/
		{
			if(FileNotRead != 0)	
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{					
				image = BlackNWhite(image);
				strcpy(sname, "bw");	/* copy string to sname */
			
				printf("Black and White operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 4)	/*Flip image vertically */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{		
				image = VFlip(image);
				strcpy(sname,"vflip");
			
				printf("Vflip operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 5)	/* Mirror Image Horizontally */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{	
			
				image = HMirror(image);
				strcpy(sname, "hmirror");
				
				printf("HMirror operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 6)	/* Color Filter the image */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{
				/* defining some varaibles that will be used in function 'ColorFilter' */
				int target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b;
				
				printf("Enter Red component for the target color: ");
				scanf("%d", &target_r);
				printf("Enter Green component for the target color: ");
				scanf("%d", &target_g);
				printf("Enter Blue component for the target color: ");
				scanf("%d", &target_b);
				printf("Enter threshold for the color difference: ");
				scanf("%d", &threshold);
				printf("Enter value for Red component in the target color: ");
				scanf("%d", &replace_r);
				printf("Enter value for Green component in the target color: ");
				scanf("%d", &replace_g);
				printf("Enter value for Blue component in the target color: ");
				scanf("%d", &replace_b);
					
				image = ColorFilter(image, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
				strcpy(sname, "colorfilter");
				
				printf("Color Filter operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 7)	/* Edge Detection */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Reat Yet!\n");
			}
			else
			{			
				image = Edge(image);
				strcpy(sname, "edge");
					
				printf("Edge operation is done!\n");	
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 8)	/* Shuffle */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{		
				image = Shuffle(image);
				strcpy(sname, "shuffle");
					
				printf("Shuffle operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 9)	/* Posterize the image  */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{	
				unsigned int pbits;
				printf("Enter the number of posterization bits (1 to 8): ");
				scanf("%u", &pbits);

				image = Posterize(image, pbits);
				strcpy(sname, "poster");

				printf("Posterize operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);	
			}
		}
		else if (choice == 10)	/* Fille the image with Christmas lights */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{
				int number, lightWidth;
				printf("Please input number of lights: ");
				scanf("%d", &number);
				printf("Please input the width of each light: ");
				scanf("%d", &lightWidth);

				image = FillLight(image, number, lightWidth);
				strcpy(sname, "light");

				printf("FillLight operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
			}
		}
		else if (choice == 11)	/* Image Overlay */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{	
				char image_2[SLEN];
				int x_coord, y_coord;
				printf("Please input the file name for the second image: ");
				scanf("%s", image_2);
				printf("Please input x coordinate of the overlay image: ");
				scanf("%d", &x_coord);
				printf("Please input y coordinate of the overlay image: ");
				scanf("%d", &y_coord);

				image = Overlay(image_2, image, x_coord, y_coord);
				printf("Image Overlay operation is done!\n");

				if(strcmp("Peter", image_2) == 0)
				{
					strcpy(sname, "overlay_peter");
				}
				else if(strcmp("Spider", image_2) == 0)
				{
					strcpy(sname, "overlay_spider");
				}
			
				printf("%s is not saved yet, please press (2) to save it.\n", sname);	
			}
		}
		else if (choice == 12)	/* BONUS: Cut Paste Function */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{	
				unsigned int startX, startY, x_width, y_width, pasteNumber;
				printf("Give the start X coordinate for cutting: ");
				scanf("%u", &startX);
				printf("Give the start Y coordinate for cutting: ");
				scanf("%u", &startY);
				printf("Give the width for cutting: ");
				scanf("%u", &x_width);
				printf("Give the height for cutting: ");
				scanf("%u", &y_width);
				printf("Give the number of paste locations: ");
				scanf("%u", &pasteNumber);
					
				image = CutPaste(image, startX, startY, x_width, y_width, pasteNumber);
				strcpy(sname, "cutPaste");
				
				printf("Cut Paste operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
			}
		}
		else if (choice == 13)	/* Resize the image */
		{
			if(FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{
				unsigned int percentage;
				printf("Please input the resizing percentage (intger between 1~500): ");
				scanf("%u", &percentage);

				image = Resize(percentage, image);

				if (percentage > 100)
				{
					strcpy(sname, "bigresize");
				}
				else if (percentage < 100)
				{
					strcpy(sname, "smallresize");
				}
			
				printf("Resize operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
				
			}
		}
		else if (choice == 14)	/* Rotate 90 degrees clockwise */
		{
			if (FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{
				image = Rotate(image);
				strcpy(sname, "rotate");
				
				printf("Rotate 90 degree clockwise operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
			}
		}
		else if (choice == 15)	/* Generate the Mandelbrot image */
		{
			unsigned int W, H, max_iteration;
			printf("Please input the width of the mandelbrot image: ");
			scanf("%u", &W);
			printf("Please input the height of the mandelbrot image: ");
			scanf("%u", &H);
			printf("Please input the max iteration for the mandelbrot calculation: ");
			scanf("%u", &max_iteration);

			image = Mandelbrot(W, H, max_iteration);
			strcpy(sname, "mandelbrot");
	
			printf("Mandelbrot operation is done!\n");
			printf("%s is not saved yet, please press (2) to save it.\n", sname); 
			mandelbrot_done = 1;	/* To be able to save image */	
		}
		else if (choice == 16)	/* Bonus, Add border outside the image */
		{
			if (FileNotRead != 0)
			{
				printf("No Image Read Yet!!\n");
			}
			else
			{
				int border_width;
				char color[SLEN];
				printf("Enter border width: ");
				scanf("%d", &border_width);
				printf("Available border colors: black, white, red, green, blue, yellow, cyan, pink, orange\n");
				printf("Select border color from the options: ");
				scanf("%s", color);
		
				image = AddOuterBorder(image, color, border_width);
				strcpy(sname, "outerborder");
	
				printf("Outer Border operation is done!\n");
				printf("%s is not saved yet, please press (2) to save it.\n", sname);
			}
		}
		else if (choice == 17)	/* AutoTest */
		{
			AutoTest(image);
			#ifdef DEBUG	/* Exit after running Autotest */
			x = -1;	
			#endif
		}
		else if (choice == 18)	/* Terminate the program */
		{
			x = -1;
		}

	}
	#ifndef DEBUG
	if(image != NULL)	/* Deallocating memory if something is left */
	{
		DeleteImage(image);
	}
	#endif
	return 0;
}

/* Print Menu */
void PrintMenu()
{
	printf("------------------------------------------------------\n");
        printf("1:   Load a PPM image\n");
        printf("2:   Save an image in PPM and JPEG format\n");
        printf("3:   Change a color image to Black & White\n");
        printf("4:   Flip an image vertically\n");
        printf("5:   Mirror an image horizontally\n");
	printf("6:   Color filter an image\n");
  	printf("7:   Sketch the edge of an image\n");
        printf("8:   Shuffle an image\n");
        printf("9:   Posterize the image\n");
	printf("10:  Fill Lights to an image\n");
	printf("11:  Overlay an image\n");
	printf("12:  Bonus, Cut and Paste operation on image\n");
	printf("13:  Resize the image\n");
	printf("14:  Rotate 90 degrees clockwise\n");
	printf("15:  Generate the Mandelbrot image\n");
	printf("16:  Bonus, Add border outside the image\n");	
        printf("17:  Test all functions\n");
        printf("18:  Exit\n");
        printf("Please make your choice: ");
}



/* Auto Test */
void AutoTest(IMAGE *image)
{
	char fname[SLEN] = "RingMall";
	int x;	

	/* BlackNWhite */
	image = ReadImage(fname);
	image = BlackNWhite(image);
	x = SaveImage("bw", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf ("Black & White tested!\n\n");
	#endif
	DeleteImage(image);

	/* Flip Image vertically */
	image = ReadImage(fname);
	image = VFlip(image);
	x = SaveImage("vflip", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf(" Vflip tested! \n\n");
	#endif
	DeleteImage(image);

	/* Mirror Image Horizontally */
	image = ReadImage(fname);
	image = HMirror(image);
	x = SaveImage("hmirror", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Hmirror tested! \n\n");
	#endif
	DeleteImage(image);

	/* Color Filter */
	image = ReadImage(fname);
	image = ColorFilter(image, 180, 180, 50, 70, 0, 255, 0);
	x = SaveImage("colorfilter", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("ColorFilter tested! \n\n");
	#endif
	DeleteImage(image);

	/* Edge Detection */
	image = ReadImage(fname);
	image = Edge(image);
	x = SaveImage("edge", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}	
	printf("Edge tested!\n\n");
	#endif
	DeleteImage(image);

	/* Shuffle */
	image = ReadImage(fname);
	image = Shuffle(image);
	x = SaveImage("shuffle", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Shuffle tested!\n\n");
	#endif
	DeleteImage(image);

	/* Posterize the image */
	image = ReadImage(fname);
	image = Posterize(image, 7);
	x = SaveImage("poster", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Posterize tested!\n\n");
	#endif
	DeleteImage(image);

	/* Fill Christmas lights to image */
	image = ReadImage(fname);
	image = FillLight(image, 200, 20);
	x = SaveImage("light", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("FillLight tested!\n\n");
	#endif
	DeleteImage(image);
		
	/* Image Overlay -- Peter */
	image = ReadImage(fname);
	image = Overlay("Peter", image, 350, 300);
	x = SaveImage("overlay_peter", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Overlay_peter tested!\n\n");
	#endif
	DeleteImage(image);

	/* Image Overlay -- Spider */
	image = ReadImage(fname);
	image = Overlay("Spider", image, 90, -10);
	x = SaveImage("overlay_spider", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Overlay_spider tested!\n\n");
	#endif
	DeleteImage(image);

	/* BONUS: Cut Paste Function */
	image = ReadImage(fname);
	image = CutPaste(image, 370, 20, 27, 57, 3);
	x = SaveImage("cutPaste", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n"); 
	}
	printf("CutPaste tested!\n\n");
	#endif
	DeleteImage(image);

	/* Resize the image -- small */
	image = ReadImage(fname);			
	image = Resize(60, image);				
	x = SaveImage("samllresize", image);			
	#ifdef DEBUG						
        if (x != 0)							
        {							
                printf("Image could not be saved!\n");	
        }							
        printf("Resizing small tested!\n\n");			
        #endif						
	DeleteImage(image);					

	/* Resize the image -- big */				
	image = ReadImage(fname);				
	image = Resize(175, image);				
	x = SaveImage("bigresize", image);			
        #ifdef DEBUG						
        if (x != 0)						
        {							
                printf("Image could not be saved!\n");	
        }							
        printf("Resizing big tested!\n\n");			
        #endif						
	DeleteImage(image);					

	/* Rotate 90 degrees clockwise */
	image = ReadImage(fname);
	image = Rotate(image);
	x = SaveImage("rotate", image);
        #ifdef DEBUG
        if (x != 0)
        {
                printf("Image could not be saved!\n");
        }
        printf("Rotate 90 degrees clockwise tested!\n\n");
        #endif
	DeleteImage(image);

	/* Generate the Mandelbrot image */
	image = Mandelbrot(720, 538, 2000);
	x = SaveImage("mandelbrot", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Generate the mandebrot image tested!\n\n");
	#endif
	DeleteImage(image);

	/* BONUS, Add border outside the image */
	image = ReadImage(fname);
	image = AddOuterBorder(image, "black", 10);
	x = SaveImage("outerborder", image);
	#ifdef DEBUG
	if (x != 0)
	{
		printf("Image could not be saved!\n");
	}
	printf("Bonus : Outer border tested!\n\n");
	/* If running AutoTest it should not DeleteImage, since there is another DeleteImage upon exit*/
	#endif


}


