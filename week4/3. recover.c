#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    // Prepare for writing JPEGs
    FILE *img = NULL;
    char filename[8]; // "000.jpg" + '\0'
    int count = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Check for JPEG header
        bool is_start = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                        (buffer[3] & 0xf0) == 0xe0;

        if (is_start)
        {
            // If already writing a JPEG, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create new filename and open new JPEG
            sprintf(filename, "%03i.jpg", count);
            count++;

            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(card);
                printf("Could not create %s.\n", filename);
                return 1;
            }

            // Write the first block of the new JPEG
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
        else
        {
            // If already found a JPEG, keep writing blocks to it
            if (img != NULL)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
