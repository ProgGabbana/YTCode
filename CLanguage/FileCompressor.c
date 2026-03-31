//FileCompressor.c is a YT Tutorial from https://www.youtube.com/watch?v=bPN4OX_zZCg

/*In this tutorial, we will program a run-length encoding (RLE) compressor in C. 
 *RLE is a simple form of data compression where sequences of the same data value 
 *are stored as a single data value and count.
 *Notes to self (NTS): Learn more about this things */

/*To build the file compressor, we will use the following command in the terminal:
 * Get-Content example.txt | ./FileCompressor mode (vscode terminal)
 * ./FileCompressor compress < example.txt (CMD terminal)
 * where mode is either "compress" or "decompress" 
 * remember to compile with: gcc -o FileCompressor FileCompressor.c */

/*The files we are going to compress are created using the following commands in the terminal:
 *"AAAAABBBBBCCCCCDDDDEEEEEEEEEEE" | Out-File -FilePath example.txt -Encoding ascii 
 *"P3
3 2
255
255 0 0  255 0 0  255 0 0
0 255 0  0 255 0  0 255 0" | Out-File -FilePath image.ppm -Encoding ascii
 */

/* * NOTE ON VISUALIZATION:
 * This program writes RAW BYTES using putchar(). 
 * For a count of 5, it sends the byte 0x05 (not the character '5').
 *
 * WHY IT LOOKS DIFFERENT THAN THE VIDEO:
 * In the tutorial, the author often uses VIM or terminal tricks 
 * to display non-printable characters as readable symbols.
 * A standard terminal will hide these bytes or show "weird" icons.
 *
 * TO VERIFY: Use 'Format-Hex' in PowerShell or 'cat -v' in Bash 
 * to see the hidden values, just like Vim does.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decompress()
{
    printf("Entering decompress\n");
}

void compress()
{  
    int seen = getchar();
    int next;
    int repetitions = 1;

    while ((next = getchar()) != EOF)
    {
        if (next == seen)
        {
            repetitions++;
            if (repetitions >= 255)
            {
                putchar(seen);
                putchar(255);
                repetitions = 0;
            }
        }
        else
        {
            putchar(seen);
            //(repetitions);
            printf("%d", repetitions); //This will print the count as a string, not as a byte.
            repetitions = 1;
            seen = next;    
        }
    }
    putchar(seen);
    //putchar(repetitions);
    printf("%d", repetitions); //This will print the count as a string, not as a byte.
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s [compress|decompress]\n", argv[0]);
        exit(-1);
    }
    if (!strcmp(argv[1], "compress"))
    {
        compress();
    }
    else if (!strcmp(argv[1], "decompress"))
    {
        decompress();
    }
    else
    {
        printf("Usage: %s [compress|decompress]\n", argv[0]);
        exit(-1);
    }
    
    return 0;
}