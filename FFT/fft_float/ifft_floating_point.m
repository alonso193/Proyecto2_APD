function Signal = ifft_floating_point(input,block_size)

Signal=complex(zeros(length(input)/2,1));

cnt=1;
    for i = [1:block_size:length(input)-block_size]

        signal_segment = cat(1,input(i:i+block_size),conj(flipud(input(i+1:i+block_size-1))));

        Signal(cnt:cnt+block_size*2-1)=ifft(signal_segment);
        cnt=cnt+64;

    end

end