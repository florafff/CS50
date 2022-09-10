#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
  
    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("cannot open\n");
        return 1;
    }
    BYTE bytes[512];
    char Buffer[8];
    int count=0;
    while (fread(bytes, sizeof(BYTE), 512, file) == 512)
    {
        // Check first four bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && bytes[3]>0xdf)
        {
            if(count<10)
            {
            sprintf(Buffer, "00%d.jpg",count);  
            }
            else
            {
            sprintf(Buffer, "0%d.jpg",count);
            }
            FILE *jpgf = fopen(Buffer, "a");
            fwrite(bytes, sizeof(BYTE), 512, jpgf);
            fclose(jpgf);
            count++;
        }
        else
        {
            if(count==0)
            {
                printf("No\n");
            }
            else
            {  
            FILE *jpgf = fopen(Buffer, "a");
            fwrite(bytes, sizeof(BYTE), 512, jpgf);
            fclose(jpgf);              
            }
        }
    }
    // Close file
    fclose(file);

}
