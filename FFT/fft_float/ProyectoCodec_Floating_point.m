clear all;
clc;

[Signal_orig,Fs]= audioread('pcm mono 16 bit 8kHz.wav'); 
info = audioinfo('pcm mono 16 bit 8kHz.wav');

size_of_block=2^6;

Signal_orig=cat(1,Signal_orig,zeros(5536,1));

Fs=info.SampleRate;
L = length(Signal_orig);
t = info.Duration*linspace(0,1,L);
f = Fs/2*linspace(0,1,L/2+1);

[fft_coeff,fft_real_part,fft_img_part]=fft_floating_point(Signal_orig,size_of_block);

cnt=1;
for i=[1:1:length(fft_real_part)]
   full_fft(cnt)=fft_real_part(i);
   full_fft(cnt+1)=fft_img_part(i);
   cnt=cnt+2;
end
format longG;
fileID = fopen('real.csv','w');

fft_real_part_int = round(fft_real_part*10000);

fprintf(fileID,'%i\n',fft_real_part_int);
fclose(fileID);

fileID = fopen('img.csv','w');

fft_img_part_int = round(fft_img_part*10000);

fprintf(fileID,'%i\n',fft_img_part_int);
fclose(fileID);


fileID = fopen('Coeficientes.csv','w');

full_fft_int = round(full_fft*10000);

fprintf(fileID,full_fft_int);
fclose(fileID);

fileID = fopen('Coeficientes.bin','w');

fwrite(fileID,full_fft_int,'integer*2');

fclose(fileID);

Signal_recovered = ifft_floating_point(fft_coeff,33);

% dlmwrite('Coeficientes.csv',full_fft'*1000000);
% dlmwrite('real.csv',fft_real_part*1000000);
% dlmwrite('img.csv',fft_img_part*1000000);

    %figure
    %subplot(2,1,1) 
%     plot(info.Duration*linspace(0,1,length(Signal_orig)-5536),Signal_orig(1:60000),'blue'); 
%     title('Señal original en el tiempo');
%     xlabel('Tiempo (s)');
%     ylabel('Amplitud');
%     xlim([0 info.Duration]);
%     grid on;

%     subplot(2,1,2)
%     plot(info.Duration*linspace(0,1,length(Signal_recovered)),Signal_recovered,'red');
%     title('Señal recuperada en el tiempo');
    xlabel('Tiempo (s)');
    ylabel('Amplitud');
    xlim([0 info.Duration]);
    grid on;


