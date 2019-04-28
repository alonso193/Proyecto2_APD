#include <stdio.h>
#include <stdlib.h>
#include "fix_fft.h"

FILE*fp;

#define FFT_SAMP (5)

char help[] = "usage: <in> <out> <inverse? 1 : 0>";
int main(int argc, char** argv)
{
	if(argc < 3){
		printf("%s\n", help);
		return 0;
	}
	/* Try to open the given file */
	fp = fopen(argv[1], "rb");
	if(!fp) {
		printf("File not found!\n");
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	unsigned int Sz = ftell(fp);
	rewind(fp);
	//short* inBuf = (short*)malloc((1<<FFT_SAMP)*2);
	short inBuf[(1<<FFT_SAMP)*2];
	
	/*if(!inBuf){
		fclose(fp);
		return 1;
	}*/

	/* try to create a file */
	FILE* out = fopen(argv[2], "wb");
	if(out==NULL){
		fclose(fp);
		//free(inBuf);
		printf("%s couldn't be created!\n", argv[2]);
	}
	
	FILE* signal = fopen("signal_recovered.csv", "w+");

	int i = 0;

	int h;
	while((i+(1<<FFT_SAMP)*2) < Sz/2) {
		
		fread(inBuf, sizeof(short), (1<<FFT_SAMP)*2, fp);
		
		if(argv[3][0]=='1')
			fix_fftr(inBuf, FFT_SAMP, 1);
			
		fwrite(inBuf, sizeof(short), (1<<FFT_SAMP)*2, out);
		
		for (h=0; h<(1<<FFT_SAMP)*2 ; h++) {
			fprintf(signal,"%i\n",inBuf[h]);
		}

		i+= (1<<FFT_SAMP)*2;

	}
	fclose(fp);
	fclose(out);
	fclose(signal);


	//free(inBuf);
	return 1;
}
