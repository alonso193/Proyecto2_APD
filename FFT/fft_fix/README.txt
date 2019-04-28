**** FORWARD FFT ****

Compile:
cc forward_fix_fft.c fix_fft.c -Wall -o FFT_MAKER

Run:
./FFT_MAKER pcm\ mono\ 16\ bit\ 8kHz.wav output_fft.bin 0

**** FORWARD FFT ****

Compile:
cc inverse_fix_fft.c fix_fft.c -Wall -o IFFT_MAKER

Run:
./IFFT_MAKER output_fft.bin output_ifft.bin 1
