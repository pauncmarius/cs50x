#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_BUFFER 512

bool is_jpeg(uint8_t *buffer){

    // we are checking for 4-th's first half byte if it's 0xe using
    //AND operation as instructions
    if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff)
    && ((buffer[3] & 0xf0) == 0xe0)){
        return true;
    }else{
        return false;
    }

    return 0;
}
int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if(argc != 2){
        printf("Should be one arg!");
        return 1;
    }

    // Open the memory card
    FILE *file_in = fopen(argv[1], "rb");
    FILE *img_out = NULL;
    if(file_in == NULL){
        printf("File not found");
        return 1;
    }

    uint8_t buffer[MAX_BUFFER];
    int count = 0;
    char name[99];

    // While there's still data left to read from the memory card
    while(fread(buffer, 1, MAX_BUFFER, file_in) == MAX_BUFFER)
    {
        if(is_jpeg(buffer)){

            if (img_out != NULL)
            {
                fclose(img_out);
            }

            sprintf(name, "%03i.jpg", count);
            img_out = fopen(name, "w");
            count++;
        }
        if (img_out != NULL)
        {
            fwrite(buffer, 1, MAX_BUFFER, img_out);
        }

    }

    if (img_out != NULL)
    {
        fclose(img_out);
    }
    fclose(file_in);

        // Create JPEGs from the data
    return 0;
}
