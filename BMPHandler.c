//
// Created by lorenzo on 3/23/23.
//
/**
* Implementation of several functions to manipulate BMP files.
*
* Completion time: ?
*
* @author (Lorenzo Ifarada), Ruben Acuna
* @version 1.0
*/

#include <stdio.h>
#include "Image.h"
#include "BMPHandler.h"
#include <string.h>
#include <math.h>

/**
 * Read BMP header of a BMP file.
 *
 * @param  file: A pointer to the file being read
 * @param  header: Pointer to the destination BMP header
 */
void readBMPHeader(FILE* file, struct BMP_Header* header)
{

    fread((header->Signature), 2, 1, file);
    fread(&(header->FileSize), 4, 1, file);
    fread(&(header->Reserved1), 2, 1, file);
    fread(&(header->Reserved2), 2, 1, file);
    fread(&(header->offset_pixel_array), 4, 1, file)  ;
}

/**
 * Write BMP header of a file. Useful for creating a BMP file.
 *
 * @param  file: A pointer to the file being written
 * @param  header: The header to write to the file
 */
void writeBMPHeader(FILE* file, struct BMP_Header* header)
{

    fwrite((header->Signature), 2, 1, file);
    fwrite(&(header->FileSize), 4, 1, file);
    fwrite(&(header->Reserved1), 2, 1, file);
    fwrite(&(header->Reserved2), 2, 1, file);
    fwrite(&(header->offset_pixel_array), 4, 1, file)  ;
}
/**
 * Read DIB header from a BMP file.
 *
 * @param  file: A pointer to the file being read
 * @param  header: Pointer to the destination DIB header
 */
void readDIBHeader(FILE* file, struct DIB_Header* header)
{
     fread(&(header->DIB_Header_Size), sizeof(int),1,file)    ;                                 // DIB HEADER SIZE    Read
     fread(&(header->Image_Width), sizeof(int),1,file)   ;                                    // IMAGE WIDTH  Read
     fread(&(header->Image_Height), sizeof(int),1,file)            ;                        // IMAGE HEIGHT Read
     fread(&(header->Planes), sizeof(char)*2,1,file)              ;                         // PLANES Read
     fread(&(header->Bits_per_pixel), sizeof(char)*2,1,file)      ;                               // BITS PER PIXEL
     fread(&(header->Compression), sizeof(int),1,file)             ;                          // BITS PER PIXEL
     fread(&(header->Image_Size), sizeof(int),1,file)               ;                        // BITS PER PIXEL
     fread(&(header->X_Pixels_Per_Meter), sizeof(int),1,file)         ;                               // BITS PER PIXEL
     fread(&(header->Y_Pixels_Per_Meter), sizeof(int),1,file)       ;                                // BITS PER PIXEL
     fread(&(header->Colors_In_Color_Table), sizeof(int),1,file)       ;                                // BITS PER PIXEL
     fread(&(header->Important_Color_Count), sizeof(int),1,file) ;

}
/**
 * Write DIB header of a file. Useful for creating a BMP file.
 *
 * @param  file: A pointer to the file being written
 * @param  header: The header to write to the file
 */
void writeDIBHeader(FILE* file, struct DIB_Header* header)
{

        fwrite(&(header->DIB_Header_Size), sizeof(int),1,file)    ;                                 // DIB HEADER SIZE    Read
        fwrite(&(header->Image_Width), sizeof(int),1,file)   ;                                    // IMAGE WIDTH  Read
        fwrite(&(header->Image_Height), sizeof(int),1 ,file)            ;                        // IMAGE HEIGHT Read
        fwrite(&(header->Planes), sizeof(char)*2,1,file)              ;                         // PLANES Read
        fwrite(&(header->Bits_per_pixel), sizeof(char)*2,1,file)  ;                                   // BITS PER PIXEL
        fwrite(&(header->Compression), sizeof(int),1,file)             ;                          // BITS PER PIXEL
        fwrite(&(header->Image_Size), sizeof(int),1,file)               ;                        // BITS PER PIXEL
        fwrite(&(header->X_Pixels_Per_Meter), sizeof(int),1,file)         ;                               // BITS PER PIXEL
        fwrite(&(header->Y_Pixels_Per_Meter), sizeof(int),1,file)       ;                                // BITS PER PIXEL
        fwrite(&(header->Colors_In_Color_Table), sizeof(int),1,file)       ;                                // BITS PER PIXEL
        fwrite(&(header->Important_Color_Count), sizeof(int),1,file) ;

}
/**
 * Make BMP header based on width and height. Useful for creating a BMP file.
 *
 * @param  header: Pointer to the destination DIB header
 * @param  width: Width of the image that this header is for
 * @param  height: Height of the image that this header is for
 */
void makeBMPHeader(struct BMP_Header* header, int width, int height)
{

    int bpp = 8; // Bits Per Pixel
    header->Signature[0]='B';
    header->Signature[1]='M';
    header->FileSize= 54+width*height*3;
    header->Reserved1=0;
    header->Reserved2=0;
    header->offset_pixel_array=(54);







}
/**
* Make new DIB header based on width and height.Useful for creating a BMP file.
*
* @param  header: Pointer to the destination DIB header
* @param  width: Width of the image that this header is for
* @param  height: Height of the image that this header is for
*/
void makeDIBHeader(struct DIB_Header* header, int width, int height)
{



    header->DIB_Header_Size= 54       ;                                 // DIB HEADER SIZE    Read
    header->Image_Width=      width       ;                                    // IMAGE WIDTH  Read
    header->Image_Height=     height      ;                        // IMAGE HEIGHT Read
    header->Planes=    1          ;                         // PLANES Read
    header->Bits_per_pixel=24;                               // BITS PER PIXEL
    header->Compression=    0  ;                          // BITS PER PIXEL
    header->Image_Size = 54*width*height*3;
    header->X_Pixels_Per_Meter= 3780       ;                               // BITS PER PIXEL
    header->Y_Pixels_Per_Meter=   3780   ;                                // BITS PER PIXEL
    header->Colors_In_Color_Table= 0 ;                                // BITS PER PIXEL
    header->Important_Color_Count= 0  ;




}

/**
 * Read Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read
 * @param  pArr: Pixel array to store the pixels being read
 * @param  width: Width of the pixel array of this image
 * @param  height: Height of the pixel array of this image
 */
void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height)
{
    int rowSize = (width*3+3) & ~3 ;
    int pad = rowSize - width *3;
    int i = 0;
    for(int x=0; x < width;x++) {
        for (int y = 0; y < height; y++) {
        fread(&pArr[i][y], sizeof(struct Pixel), 1, file);
    }
        fseek(file,pad,SEEK_CUR);
    }
}
/**
 * Write Pixels from BMP file based on width and height.
 *
 * @param  file: A pointer to the file being read or written

 * @param  pArr: Pixel array of the image to write to the file

 * @param  width: Width of the pixel array of this image

 * @param  height: Height of the pixel array of this image

 */
void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){

    int rowSize = (width*3+3) & ~3;
    int Pad = rowSize - width *3;
    unsigned char intitial[3] = {0,0,0};
        for(int x=0; x < width;x++) {
            for (int y = 0; y < height; y++) {
                fwrite(&pArr[x][y], sizeof(struct Pixel), 1, file);


            }
            fwrite(intitial,1,Pad,file);
        }
    }
