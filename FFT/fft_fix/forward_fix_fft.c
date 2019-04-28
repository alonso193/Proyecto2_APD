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
	
	FILE* fft_signal_real = fopen("fft_real_fxp.csv", "w+");
	FILE* fft_signal_img = fopen("fft_img_fxp.csv", "w+");
	
	int i = 0;

	int h;
	while((i+(1<<FFT_SAMP)*2) < Sz/2) {

		fread(inBuf, sizeof(short), (1<<FFT_SAMP)*2, fp);

		fix_fftr(inBuf, FFT_SAMP, 0);
		if(argv[3][0]=='1')
			fix_fftr(inBuf, FFT_SAMP, 1);
			
		fwrite(inBuf, sizeof(short), (1<<FFT_SAMP)*2, out);
		
			for (h=0; h<(1<<FFT_SAMP)*2 ; h+=2) {
				fprintf(fft_signal_real,"%i\n",inBuf[h]);
				fprintf(fft_signal_img,"%i\n",inBuf[h+1]);
			}

		i+= (1<<FFT_SAMP)*2;

	}
	fclose(fp);
	fclose(out);

	fclose(fft_signal_real);
	fclose(fft_signal_img);

	return 1;
}
