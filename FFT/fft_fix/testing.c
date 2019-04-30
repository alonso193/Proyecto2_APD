#include <stdio.h>
#include <stdlib.h>
#include "fix_fft.h"

FILE*fp;


int main(int argc, char** argv)
{

	fp = fopen("output_fft.bin", "rb");
	fseek(fp, 0, SEEK_END);
	unsigned int Sz = ftell(fp);
	rewind(fp);
	
	short inBuf[1];


	int i=0;
	while (i < 10) {
		fread(&inBuf, sizeof(short), 1, fp);
		printf("%d\n",inBuf[0]);
		
		i++;
	}

	fclose(fp);


	return 1;
}
