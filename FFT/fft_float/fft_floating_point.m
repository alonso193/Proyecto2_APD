function [fft_coeff,real_part,img_part] = fft_floating_point(input,block_size)

fft_coeff_aux=complex(zeros(length(input),1));
fft_coeff=complex(zeros(length(input)/2,1));
cnt=1;
    for i = [1:block_size:length(input)]

        signal_segment = input(i:i+block_size-1);
        fft_coeff_aux(i:i+block_size-1)=fft(signal_segment);
        
        fft_coeff(cnt:cnt+block_size/2)=fft_coeff_aux(i:i+block_size/2);
        cnt=cnt+33;
        
        real_part=real(fft_coeff);
        img_part=imag(fft_coeff);
    end
end