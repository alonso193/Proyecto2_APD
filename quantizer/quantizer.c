#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../leyMu/compressor.h"
#include "../leyMu/decompressor.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define NEWLINE '\n'

// number of samples to read per loop,
#define SAMPLES 33792



void quantizer()
{
    int lineCounter = 0;
    char character[16];
    FILE *in1 = fopen ("output_fft.bin", "rb");
    FILE *out1 = fopen ("realCoeffsBin.txt", "w");
    FILE *in2 = fopen ("img.csv", "r");
    FILE *out2 = fopen ("imagCoeffsBin.txt", "w");
    if (in1 == NULL)
    {
        printf("\nError de apertura del archivo de coeficientes reales. \n\n");
    }
    if (in2 == NULL)
    {
        printf("\nError de apertura del archivo de coeficientes imaginarios. \n\n");
    }
    //get the number of lines in the file

    fseek(in1, 0, SEEK_END);
    unsigned int Sz = ftell(in1);
    rewind(in1);

    short inBuf[1];


    int i=0;
    char sign;
    char magnitude[15];
    //printf("Variable Sz: %i\n", Sz);
    while (i < Sz/2) {
        fread(inBuf, sizeof(short), 1, in1);
        if (inBuf[0] < 0) {
            sign = '1';
        }
        else{
            sign = '0';
        }
        int c, d, count;

        count = 0;

        for (c = 14 ; c >= 0 ; c--)
        {
           d = (abs(inBuf[0])) >> c;

           if (d & 1)
              magnitude[count] = 1 + '0';
           else
              magnitude[count] = 0 + '0';

           count++;
        }
        magnitude[count] = '\0';
        printf("%c%s\n", sign,magnitude);
        i++;
    }

    fclose(in1);
    fclose(in2);
    fclose(out1);
    fclose(out2);
}

int main(int argc, char const *argv[]) {
    quantizer();
    compressor("outputSignedBinary.txt");
    return 0;
}
