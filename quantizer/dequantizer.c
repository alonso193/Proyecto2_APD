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

short binToIntDeq(char *cadenaBinaria, int longitud) {
  short decimal = 0;
  short multiplicador = 1;
  char caracterActual;
  int i;
  for (i = longitud - 1; i >= 0; i--) {
    caracterActual = cadenaBinaria[i];
    if (caracterActual == '1') {
      decimal += multiplicador;
    }
    multiplicador = multiplicador * 2;
  }
  return decimal;
}

void dequantizer(char *fileName)
{
    int lineCounter = 0;
    char character[17];
    //open file as read only
    FILE *inFile = fopen (fileName, "r");
    FILE *outFile = fopen ("outCoeffDec_float.bin", "wb");
    if (inFile == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    //get the number of lines in the file
    int coeffInt;
    char sign;
    char magnitude[15];
    //get the number of lines in the file
    while (feof(inFile) != 1)
    {
        fgets(character, 100, inFile);
        lineCounter++;
    }
    rewind(inFile);
    int lines = lineCounter - 1;
    int i;
    for (i = 0; i < lines; i++){
        fgets(character, 100, inFile);
        //saving the sign bit
        //step 1
        char sign = character[0];
        int magnitudeLenght = 15;
        char magnitude[magnitudeLenght];
        //getting the magnitude
        int j;
        for (j = 0; j < magnitudeLenght; j++) {
            magnitude[j] = character[j+1];
        }
        //printf("%s\n",magnitude);
        short magDec = binToIntDeq(magnitude, magnitudeLenght);
        if (sign == '1') {
            magDec *= -1;
        }
        printf("%d\n", magDec);
        //fwrite(&magDec, 2, 1, outFile);
    }
    //
    // while (feof(inFile) != 1)
    // {
    //     fgets(character, 17, inFile);
    //     for (int j = 0; j < 16; j++) {
    //         if (j == 0) {
    //             sign = character[j];
    //         }
    //         else{
    //             magnitude[j-1] = character[j];
    //         }
    //     }
    //     magnitude[15]='\0';
    //     printf("%c", sign);
    //     printf("%s", magnitude);
    //     coeffInt = binToInt(magnitude,15);
    //     if (sign == '1') {
    //         coeffInt *= -1;
    //     }
    //     //printf("%d\n", coeffInt);
    //
    //     lineCounter++;
    // }
    // rewind(inFile);
    // int lines = lineCounter - 1;
}

int main(int argc, char const *argv[]) {
    dequantizer("../leyMu/coeffs_float.txt");
    return 0;
}
