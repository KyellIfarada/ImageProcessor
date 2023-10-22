//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Customer Headers and Implementation Files
#include "BMPHandler.h"
#include "Image.h"
#include "Image.c"
#include <ctype.h>


//Main to  Open Files/Save Files .. Perform Function Calls....
int main() {
    int quit = 0;
    int count = 0; // for ColorShift Prerequisite(GrayShift)
    int snap = 0;
    FILE *fp;
    do {


        FILE *fp2;                  //OutputFilePointer

        char fname[100]="   ";		//Storing File Path/Name of Image to Display
        char fname_copy[100];       //OutputFile
        struct BMP_Header BMP;
        struct DIB_Header DIB;

        makeBMPHeader(&BMP,150,150);
        makeDIBHeader(&DIB,150,150);

        printf("\n\n");
        printf("Welcome to Image Processor \n\n");
        printf("Menu Options \n");
        printf("-------------------------------------------------------------------------\n");
        printf("Press to q to Quit \n\n");
        printf("Please enter your input file of choice : below are your choices \n");
        printf("test2.bmp \n");
        printf("ttt.bmp \n");
        printf("wb.bmp \n");



        printf("\n\nPlease Enter the Full Path of the Image file you want to view: \n");
        scanf("%s",&fname);
        fp=fopen(fname,"rb");

        //File Validation
        if(fp==NULL)
        {
            printf("\n%s\" File NOT FOUND!",fname);
            exit(1);
        }


        //Sets Header
        readBMPHeader(fp, &BMP);
        readDIBHeader(fp, &DIB);

        //BMP VALIDATION
        if(BMP.Signature[0]=='B' && BMP.Signature[1]=='M')
        {
            printf("Correct File Type \n");
        }

        //Creates Mem Space for Image
        struct Pixel** pixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * 152);
        for (int p = 0; p < 152; p++) {
            pixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * 152);
        }
        //Reads Pixels from File
        readPixelsBMP(fp, pixels, 152, 152);
        //Saves Pixels  to Image struct
        Image* img = image_create(pixels, 152, 152);

                    printf("What Operation would you like to try on you file? Enter dash then the letter of choice \n");
                    printf("Note: You must apply Grayscale first or shifts can not be applied \n");
                    printf("-w: Grayscale \n");
                    printf("-r: Red Shift \n");
                    printf("-g: Green Shift  \n");
                    printf("-b: Blue Shift \n");
                    printf("-s:Scale \n");
                    printf("-o: save file \n");
                    printf("enter any other key(s) to exit \n");


                    char pick[100];
                    //Option for OutputFile
                    int num[100];
                    scanf(" %s", &pick);


                    if (strcmp(pick, "-w") == 0 ) {
                        image_apply_bw(img);
                        count++;
                    } else if ((strcmp(pick, "-r") == 0) && count == 1 ) {
                        printf("enter integer for color thank you \n");
                        scanf(" %d", &num);
                        if (isdigit(*num)) {

                            if (snap == 0) {
                            image_apply_colorshift(img, *num, 0, 0);
                            snap++;
                        }
                            else {

                                if (num > 255) {
                                    image_apply_colorshift(img, 255, 0, 0);
                                } else if (num < 0) {
                                    image_apply_colorshift(img, 0, 0, 0);
                                } else {
                                    image_apply_colorshift(img, *num, 0, 0);
                                }
                            }
                        }
                    }
                     else if ((strcmp(pick, "-g")) == 0 && count == 1) {
                        printf("enter integer for color thank you \n");
                        scanf(" %d", &num);
                       if (isdigit(*num)) {

                           if (snap == 0) {
                               image_apply_colorshift(img, *num, 0, 0);
                               snap++;
                           }
                           else  {
                           if (*num > 255) {
                               image_apply_colorshift(img, 0, 255, 0);
                           } else if (*num < 0) {
                               image_apply_colorshift(img, 0, 0, 0);
                           } else {
                               image_apply_colorshift(img, 0, *num, 0);
                           }
                                 }
                       }
                    } else if ((strcmp(pick, "-b")) == 0 && count == 1) {
                        printf("enter integer for color thank you \n");
                        scanf(" %d", &num);
                       if isdigit(*num) {

                           if(snap == 0) {
                               image_apply_colorshift(img, *num, 0, 0);
                               snap++;
                           }
                           else {
                               if (*num > 255) {
                                   image_apply_colorshift(img, 0, 0, 255);
                               } else if (*num < 0) {
                                   image_apply_colorshift(img, 0, 0, 0);
                               } else {
                                   image_apply_colorshift(img, 0, 0, *num);
                               }
                            }
                       }
                    } else if (strcmp(pick, "-s") == 0) {
                        printf("enter integer for resize thank you \n");
                        image_apply_resize(img,*num);
                    } else if (strcmp(pick, "-o") == 0) {
                        printf("enter  'filename' then '_copy' together for naming purposes naming purposes \n");
                        scanf("%s", &fname_copy);
                        fp2 = fopen(fname_copy, "wb");

                        writeBMPHeader(fp2, &BMP);
                        writeDIBHeader(fp2, &DIB);
                        writePixelsBMP(fp2, image_get_pixels(img), image_get_width(img), image_get_height(img));
                        fclose(fp2);

                        //Validation
                        fp2 = fopen(fname_copy, "rb");
                        readBMPHeader(fp2, &BMP);
                        readDIBHeader(fp2, &DIB);
                        if(BMP.Signature[0]=='B' && BMP.Signature[1]=='M')
                        {
                            printf("Correct File Type \n");
                        }
                        fclose(fp2);

                    }
                    else{
                        free(pixels);
                        free(img);
                        free(fp);
                        free(fp2);
                        fp =NULL;

                        quit =1;
                    }








}
    while(quit !=1);

    return 0;
}
