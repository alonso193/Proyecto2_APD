

ift = dsp.IFFT('ConjugateSymmetricInput',true,'Normalize',true);


full_fft_t=full_fft';

for i = [1:64:length(full_fft_t)]
    signal_segment = full_fft_t(i:i+63);
    
    Signal2(i:i+63)=ift(signal_segment); 
    release(ift);
end

signal_recoverd=Signal2';
figure
ft = dsp.FFT('FFTLengthSource','Auto');
subplot(2,1,1)
plot([1:1:length(Signal)],abs(ft(Signal))); 
subplot(2,1,2)
plot([1:1:length(Signal2)],abs(ft(signal_recoverd))); 

%sound(Signal2,Fs);

