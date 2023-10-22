/**
* Specification for an image ADT.
*
* Completion time: ?
*
* @author (Lorenzo Ifarada), Ruben Acuna
* @version 03/23/2023
*/

////////////////////////////////////////////////////////////////////////////////
// Include Files
#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include "Image.h"
////////////////////////////////////////////////////////////////////////////////
// Type Definitions
typedef struct Image Image;
typedef struct Pixel Pixel;


////////////////////////////////////////////////////////////////////////////////
//Function Declarations

/* Creates a new image and returns it.
*
 * @param  pArr: Pixel array of this image.
 * @param  width: Width of this image.
 * @param  height: Height of this image.
 * @return A pointer to a new image.
*/
Image* image_create(struct Pixel** pArr, int width, int height)
        {
            Image* NewImage =(struct Image*) malloc(sizeof(struct Image));
            NewImage->pArr=*pArr;
            NewImage->width = width;
            NewImage->height=height;
            return NewImage;

}


/* Destroys an image. Does not deallocate internal pixel array.
*
 * @param  img: the image to destroy.
*/
void image_destroy(Image** img)
{
    free(*img);
}

/* Returns a double pointer to the pixel array.
*
 * @param  img: the image.
*/
struct Pixel** image_get_pixels(Image* img)
{

    struct Pixel** Get_Pixels = (struct Pixel **) img->pArr;
    return Get_Pixels;
}

/* Returns the width of the image.
*
 * @param  img: the image.
*/
int image_get_width(Image* img)
{
    int Image_Width = img->width;
    return Image_Width;
}
/* Returns the height of the image.
*
 * @param  img: the image.
*/
int image_get_height(Image* img)

{
     int Get_height = img->height;
     return  Get_height;

}
/* Converts the image to grayscale.
*
 * @param  img: the image.
*/
void image_apply_bw(Image* img)
{
    Image* Img = img;
    unsigned char Rojo = Img->pArr->red;
    unsigned char Azul = Img->pArr->blue;
    unsigned char Verde = Img->pArr->green;

    unsigned char Gris = ((Rojo*.299)+(Azul*.114)+(Verde*.587)) *((Rojo*.299)+(Azul*.114)+(Verde*.587));
    Rojo  =  Gris;
    Azul  =  Gris;
    Verde =  Gris;
}

/**
 * Shift color of the internal Pixel array. The dimension of the array is width * height.
 * The shift value of RGB is rShift, gShift，bShift. Useful for color shift.
 *
 * @param  img: the image.
 * @param  rShift: the shift value of color r shift
 * @param  gShift: the shift value of color g shift
 * @param  bShift: the shift value of color b shift
 */
void image_apply_colorshift(Image* img, int rShift, int gShift, int bShift)
{
    Image* Img= (struct Image*)malloc(sizeof(struct Image));
    Img = img;
    unsigned char Rojo = Img->pArr->red+rShift;
    unsigned char Azul = Img->pArr->blue+gShift;
    unsigned char Verde = Img->pArr->green+bShift;

}
/* Converts the image to grayscale. If the scaling factor is less than 1 the new image will be
 * smaller, if it is larger than 1, the new image will be larger.
 *
 * @param  img: the image.
 * @param  factor: the scaling factor
*/
void image_apply_resize(Image* img, float factor) {
    int i = 0, j = 0;
    Image *tmpptr = (Image *) malloc(sizeof(Image));
    tmpptr->height = img->height * factor;
    tmpptr->width = img->width * factor;

    tmpptr->pArr = (struct Pixel **) malloc(sizeof(Pixel *) * tmpptr->height);
    for (i = 0; i < tmpptr->height; i++) {
        tmpptr->pArr[i] = *(struct Pixel *) malloc(sizeof(Pixel) * tmpptr->width);
        for (j = 0; j < tmpptr->width; j++) {
            int  a = i/factor;
            int  b =  j / factor;
            tmpptr->pArr[a][b] = img->pArr[a][b];
        }
    }

    for (i = 0; i < img->height; i++)
        for (j = 0; j < img->width; j++) {
            free(img->pArr[i][j]);
        }


    free(img->pArr);

    img->width = tmpptr->width;
    img->height = tmpptr->height;
    img->pArr = tmpptr->pArr;
    free(tmpptr);
}

